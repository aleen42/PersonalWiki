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
