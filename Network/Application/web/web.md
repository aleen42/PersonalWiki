## Web Communication [Back](../Application.md)

In practices of web programming, we often need to communicate between the client and the server and provide immediate notifications from servers' push. There are three main ways to achieve it on the web: HTTP polling, Server-Sent Events (SSE), and web sockets.

HTTP polling means creating a fixed-time running task to poll messages from the server.

```js
setInterval(() => fetch(url), 100); // polling things each 100 ms
```

The Server-Sent Events means creating a single-simplex channel to grasp notifications from servers:

```js
(new EventSource(url)).onmessage = event => {
    // handle the notication
    console.log('Message from server', event.data);
};
```

Web sockets means creating a duplex channel to communicate with servers:

```js
const socket = new WebSocket(url);
socket.addEventListener('open', event => {
    socket.send('hello');
});

socket.addEventListener('message', event => {
    console.log('Message from server', event.data);
});
```
