## WebSocket [Back](./../web_api.md)

We use **WebSocket** to create a connection between **Client** and **Server**, to send or receive data.

### Client (JavaScript)

#### 1. new a object

```js
/**
 * [WebSocket]
 * @param {[string]} url      [url to connect]
 * @param {[string]} protocol [protocol designed by servers, which will be a empty string by default]
 */
var webSocket = new WebSocket('http://www.example.com/socketserver');
```

#### 2. available methods

```js
/**
 * [close description]
 * @param  {[number]} code   [status code, which is 1000 by default, meaning normal closing]
 * @param  {[string]} reason [description]
 */
webSocket.close('300', 'Personal Reson');
```
