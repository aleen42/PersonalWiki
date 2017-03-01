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
