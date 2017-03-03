## Ajax [Back](./../high_performance.md)

Ajax is a cornerstone of high performance JavaScript.

This chapter mainly discusses the fastest techniques for sending data to and receiving it from the server, as well as the most efficient formats for encoding data.

### 1. Data Transmission

There are several different ways of communicating with a server, while Ajax is one of them without unloading the current page.

#### 1.1 Requesting Data

There are five general techniques for requesting data from a server:

- XMLHttpRequest (XHR)
- Dynamic script tag insertion
- iframes
- Comet
- Multipart XHR

##### 1.1.1 **XMLHttpRequest**

By far the most common technique used, XMLHttpRequest allows you to asynchronously send and receive data.

```js
var url = './data.php';
var params = [
    'id=934875',
    'limit=20'
];

var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
        /** get the response headers */
        var responseHeaders = xhr.getAllResponseHeaders();

        /** get the data */
        var data = xhr.reponseText;
    }
};

xhr.open('GET', url + '?' + params.join('&'), true);

/** set a request header */
xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');

/** send the request to the server */
xhr.send(null);
```

A `readyState` of 4 indicates that the entire response has been received and is available for manipulation.

It's possible to interact with the server responses as it's still being transferred by listening for `readyState` 3. This is known as streaming, and it's a powerful tool for improving the performance of your data requests:

```js
xhr.onreadystatechange = function () {
        if (xhr.readyState === 3) {
            /** some data has been received */
        } else if (xhr.readyState === 4) {
            /** all data has been received */
        }
};
```

However, there are still some drawbacks about using XMLHttpRequest. Because of the high degree of control the XHR offers, browsers place some restrictions on it. You cannot use XHR to request data from a different domain, and older versions of IE do not give you access to `readyState` 3, which prevents streaming.

Then, when using XHR to request data, what is the best choice between GET and POST. For requests that don't change the server state and only pull back data (this is called an **idempotent action (冪等動作)**), use GET, because GET requests are cached to improve performance.

POST should be used to fetch data only when the length of the URL and the parameters are close to or exceed 2,048 characters, as the limitation of IE.

##### 1.1.2 **Dynamic script tag insertion**

The most power of using this technique is allowing you to fetch data from a crossed domain. Of course, it's just a hack.

```js
var scriptElement = document.createElement('script');
script.src = 'http://any-domain.com/javascript/lib.js';
document.getElementsByTagName('head')[0].appendChild(scriptElement);
```

However, this way offers less control than XHR. You can only use GET, and you don't have access to the response headers or to the entire response as a string. Because it's being used as the source for a script tag, it **must** be a executable JavaScript source. Any data, regardless of the format, must be enclosed in a callback function. For example, how to transfer data with JSON format:

```js
function jsonCallback(jsonString) {
    var str = jsonString;

    if (Object.prototype.toString.call(str) !== '[object String]') {
        /** ensure that the jsonString is a string */
        str = JSON.stringify(str);
    }

    var data = JSON.parse(str);

    /** start to process the data */
    /** ... */
}

var scriptElement = document.createElement('script');
script.src = 'http://any-domain.com/javascript/lib.js';
document.getElementsByTagName('head')[0].appendChild(scriptElement);
```

Then the file of `lib.js` can be coded like this:

```js
jsonCallback('{ "status": 1, "colors": [ "#fff", "#000", "#ff0000" ] }');
```

Despite these limitations, this technique an be extremely fast, even faster than XHR, because it's not treated as a string that must be further processed.

There is another important problem that you should pay more attention to when using this technique. Any code that you incorporate into your page using dynamic script tag insertion will have complete control over the page, like modifying any content, redirecting users to another site, or even track their actions and send the data to a third party. Therefore, **be careful about importing code from an external source**.

##### 1.1.3 **Multipart XHR**

The newest of the techniques mentioned here, multipart XHR (MXHR) allows you to pass multiple resources from the server to the client side using only one HTTP request. The basic of this technique is to packaging up the resources with separating by some agreed-upon strings.

Let's take an example to explain it. First, a request is made to the server for several image resources:

```js
var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
        splitImages(xhr.responseText);
    }
};
```

Next, on the server side, the images are read and converted into strings:

```php
$images = ['kitten.jpg', 'sunset.jpg', 'baby.jpg'];
foreach ($images as $image) {
    $image_fh = fopen($image, 'r');
    $image_data = fread($image_fh, filesize($image));

    fclose($image_fh);
    $payloads[] = base64_encode($image_data);
}

/** combine all these into a string with a character as separator */

echo implode(chr(1), $payloads);
```

Then, come back to the client side, we can split up this images data like this:

```js
function splitImages(imageString) {
    var imageData = imageString.split('\u0001');
    var imageElement;

    for (var i = 0, len = imageData.length; i < len; i++) {
        imageElement = document.createElement('img');
        imageElement.src = 'data:image/jpeg;base64,' + imageData[i];
        document.getElementById('container').appendChild(imageElement);
    }
}
```

Certainly, you can also take strings for JavaScript code, CSS styles, and images and convert them into resources the browser can use:

```js
/** handle images with different mineType */
function handleImageData(data, mineType) {
    var img = document.createElement('img');
    img.src = 'data:' + mineType + ';base64,' + data;

    return img;
}

/** handle CSS styles */
function handleCSS(data) {
    var style = document.createElement('style');
    style.type = 'text/css';

    style.innerText = data;
    document.getElementsByTagName('head')[0].appendChild(style);
}

/** handle JavaScript code */
function handleJavaScript(data) {
    eval(data);
}
```

As MXHR responses grow larger, it becomes necessary to process each resource as it is received, rather than waiting for the entire response:

```js
var xhr = new XMLHttpRequest();
var getLatestPacketInterval;
var lastLength = 0;

xhr.open('GET', 'rollup_images.php', true);
xhr.onreadystatechange = function () {
    if (readyState === 3 && getLatestPacketInterval === null) {
        /** start polling */
        getLatestPacketInterval = setInterval(function () {
            getLatestPacket();
        }, 25);
    }

    if (readyState === 4) {
        /** stop polling */
        clearInterval(getLatestPacketInterval);

        /** get the last packet */
        getLatestPacket();
    }
};

xhr.send(null);

function getLatestPacket() {
    var length = xhr.responseText.length;
    var packet = xhr.reponseText.substring(lastLength, length);

    /** process packet and handle images when hitting the agreed-upon character */
    processPacket(packet);
    lastLength = length;
}
```

There are some drawbacks when using this technique, the biggest one of which is that none of the fetched resources are cached in the browser. Another downside is that older versions of IE do not support `readyState` 3 or base64 data setting for images.

Despite this downsides, MXHR has also significantly improved overall page performance by reducing HTTP requests, which is one of the most extreme bottlenecks in Ajax.

#### 1.2 Sending Data

There are times when you don't care about retrieving data, and instead only want to send it to the server. In such situation, there are two techniques that are widely used: **XHR** and **beacons**.

##### 1.2.1 **XMLHttpRequest**

When sending data to the server side, we can also use `onerror` to catch failures during the process:

```js
var xhr = new XMLHttpRequest();
xhr.onerror = function () {
    /** resend or any other handled operations */
};
```

When it comes to performance, it's faster to use GET to send data back to server with using XHR. This is because, for small amounts of data, a GET request is sent to the server in a single packet. A POST, on the other hand, is sent in a minimum of two packets, one for the headers and another for the POST body.

##### 1.2.2 **Beacons**

This technique is very similar to dynamic script insertion. JavaScript is used to create a new `Image` object, with the `src` property set to the URL of a script on your server. Data we want to send can be set as parameters following this URL.

```js
var url = './status_tracker.php';
var params = [
    'step=2',
    'time=1248027312'
];

(new Image()).src = url + '?' + params.join('&');
```

Note that no `img` element has to be created or inserted into the DOM.

Even though you can catch errors from the server side, it is the most efficient way to send information back to the server. To work around this, you can use a smart way like listening for the `Image` object's `load` event, which will tell you if the server successfully received the data. Furthermore, you can also check the width and height of the image that the server returned for a state. For instance, a width of 1 can be represented for "success", while 2 for "try again".

```js
var beacon = new Image();
beacon.src = url + '?' + params.join('&');

beacon.onload = function () {
    if (this.width === 1) {
        /** successfully */
    } else if (this.width === 2) {
        /** failed and try again */
    }
};

beacon.onerror = function () {
    /** failed and try again */
};
```

If you don't need to return data in your response, you should send a response code of **204 No Content** and no message body. This will prevent the client from waiting for a message body that will never come.

### 2. Data Formats

When considering data transmission, you must take into several factors: feature set, compatibility, performance, and direction (retrieve or send data). When considering data formats, the only scale you need for comparison is speed.

In this section, each of the data formats will be compared based on the file size of the list, the speed of parsing it, and the ease with which it's formed on the server.

#### 2.1 XML

When Ajax first becomes popular, XML was the data format of choice, which had many advantages: extreme interoperability (互用性, with excellent support on both the server side and the client side), strict formatting, and easy validation.

However, compared with other formats, XML is extremely verbose. To create a piece of data, you must require a lot of structure. In general, in order to parse XML, not only must you know the particulars of the structure ahead of time, but you must also know exactly how to pull apart of the structure and reassemble it into a JavaScript object.

To make it easier to parse XML, a more efficient approach is to encode data as an attribute of a tag.

##### 2.1.1 **XPath**

XPath can be much faster than `getElementsByTagName` when parsing an XML document. However, as it is not universally supported, you may have to write fallback code when using the older style of DOM traversal.

##### 2.1.2 **Response sizes and parse times**

Format|Size|Download time|Parse time|Total load time
------|----|-------------|----------|----------
Verbose XML|582,960 bytes|999.4ms|434.1ms|1342.5ms
Simple XML|437,960 bytes|475.1ms|83.1ms|558.2ms

Even though simple XML is faster than the verbose one, it's still slower than any other faster format. What it means is that XML has no place in high-performance Ajax, unless this is the only format of data.

#### 2.2 JSON

JSON is a lightweight and easily-to-parse data format written using JavaScript object and array literal syntax. JSON data is executable JavaScript code, which can be parsed with using `eavl()` or `JSON.parse()`.

> Using `eval()` in your code is dangerous, especially when using it to evaluate third-party JSON data. Whenever possible, use the `JSON.parse()` to parse a JSON string natively.

##### 2.2.1 **JSON-P**

When XHR is used, JSON data is returned as a string, which can be evaluated by using `eval()` or `JSON.parse()`. However, when using dynamic script tag insertion, JSON data is treated as just another JavaScript file and executed as native code. In order to accomplish this, the data must be wrapper in a callback function, a.k.a JSON with padding, or JSON-P.

According to some tests, the fastest JSON format is JSON-P formed using arrays. But what you should take in mind is that do not encode any sensitive data in JSON-P, as it can be called by anyone with using dynamic script tag insertion.

##### 2.2.2 **Should you use JSON?**

JSON is a cornerstone of high-performance Ajax, especially when it's used with dynamic script insertion. Lower size of structure, with lower parse time.

#### 2.3 HTML

Often the data you are requesting will be turned in to HTML for display on the page. One technique is forming all of the HTML on the server and then passing it to the client, where it can be dropped in the place with `innerHTML` by JavaScript.

The problem with this technique is that HTML is a verbose data format, which is even more than XML. Therefore, you should use this technique only when the client-side CPU is more limited than bandwidth.

#### 2.4 Custom Formatting

The ideal data format is one that includes just enough structure to allow you to separate individual fields from each other, like using a separator. One of the most important decisions when using this way is what to use as the separators.

In most cases, los-number ASCII characters work well and are easy to represent in most server-side language.

In JavaScript, we can separate such string like this:

```js
/** Regular Expression Delimiter */
var rows = xhr.responseText.split(/\u0001/);

/** String Delimiter (safer in older version of browsers) */
var rows = xhr.responseText.split('\u0001');
```

If you want to receive huge amounts of data in the client side, this will be your best choice.

### 3. Ajax Performance Guidelines

Once you have selected the most appropriate transmission technique and data format depending on requirements, you can start to consider other optimization techniques.

#### 3.1 Cache Data

To prevent an unnecessary request, there are two main ways:

- On the server side, set HTTP headers that ensure the response will be cached in the browser.
- On the client side, store fetched data locally so that it does not have to be requested again.

##### 3.1.1 **Setting HTTP headers**

The `Expires` header tells the browser how long a response can be cached, the value of which should be a date:

```
Expires:    Mon, 28 Jul 2014 23:30:00 GMT
```

The server side can set up such a header to clearly tell the browser to cache responses for a certain time.

##### 3.1.2 **Storing data locally**

Instead o relying on the browser to handle caching, you can also do it in a more manual fashion by strong the responses locally. For example, store them with URL as key into a JavaScript object, so that you can reuse them without requesting again.

### 4. Limitations

All JavaScript libraries have given us access to an Ajax object, which normalizes the differences between browsers and gives us a consistent interface, so that we can focus more on our projects rather than the details of how XHR works in different browsers. However, it also means that we cannot access the full power of XMLHttpRequest.

To use XMLHttpRequest object without worrying about the problem of compatibility, here we will encapsulate a function to return a more powerful XMLHttpRequest object, which we can then interact with directly:

```js
function createXHR() {
    var msXMLProgId = [
         'MSXML2.XMLHTTP.6.0',        'MSXML3.XMLHTTP',        'Microsoft.XMLHTTP',  /** Doesn't support readyState 3. */    'MSXML2.XMLHTTP.3.0' /** Doesn't support readyState 3. */
    ];

    var xhr;

    try {
        xhr = new XMLHttpRequest(); /** try the standard way at first */
    } catch (e) {
        for (var i = 0, len = msXMLProgId.length; i < len; i++) {
            try {
                xhr = new ActiveXObject(msXMLProgId[i]);
            } catch (e2) {}
        }
    } finally {
        return xhr;
    }
}
```

### 5. Summary

High-performance Ajax consists of knowing the specific requirements of your situation and selecting the correct data format and transmission technique to match.

As data formats, we should consider that:

- Plain text and HTML are highly situational, but they can save CPU cycles on the client side.
- XML is widely available and supported, but it's verbose and slow to parse.
- JSON is lightweight and quick to parse.
- If you want to transfer huge amounts of data, it's best to use custom formats, designed by both the client and the server side.

When requesting data:

- XHR gives you the most control and flexibility, even though it treats data as string, slowing down the parse time.
- Dynamic script tag insertion allows for cross-domain request and native execution of JavaScript and JSON, though you cannot control more.
- Multipart XHR can be used to reduce the number of requests, though it does not cache any received resource.

When sending data:

- image beacons are a simple and efficient approach.
- XHR can also be used to send large amounts of data in POST.

There're several guidelines for improving Ajax:

- Reduce the number of requests you make, either by concatenating files, or by using MXHR.
- Using Ajax to improve the loading time of pages.
