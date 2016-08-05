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
var webSocket = new WebSocket('http://www.example.com/socketserver' 'socket');
```

#### 2. available methods

```js
/**
 * [close description]
 * @param  {[number]} code   [status code, which is 1000 by default, meaning normal closing]
 * @param  {[string]} reason [the reason why]
 */
webSocket.close('300', 'Personal Reson');

webSocket.send('data');
```

A list of Close Status Code:

Status|Name|
:----:|:--:|:----------
0–999||**Reserved and not used.**
1000|CLOSE_NORMAL|Normal closure; the connection successfully completed whatever purpose for which it was created.
1001|CLOSE_GOING_AWAY|The endpoint is going away, either because of a server failure or because the browser is navigating away from the page that opened the connection.
1002|CLOSE_PROTOCOL_ERROR|The endpoint is terminating the connection due to a protocol error.
1003|CLOSE_UNSUPPORTED|The connection is being terminated because the endpoint received data of a type it cannot accept (for example, a text-only endpoint received binary data).
1004||**Reserved**. A meaning might be defined in the future.
1005|CLOSE_NO_STATUS|**Reserved**.  Indicates that no status code was provided even though one was expected.
1006|CLOSE_ABNORMAL|**Reserved**. Used to indicate that a connection was closed abnormally (that is, with no close frame being sent) when a status code is expected.
1007|Unsupported Data|The endpoint is terminating the connection because a message was received that contained inconsistent data (e.g., non-UTF-8 data within a text message).
1008|Policy Violation|The endpoint is terminating the connection because it received a message that violates its policy. This is a generic status code, used when codes 1003 and 1009 are not suitable.
1009|CLOSE_TOO_LARGE|The endpoint is terminating the connection because a data frame was received that is too large.
1010|Missing Extension|The client is terminating the connection because it expected the server to negotiate one or more extension, but the server didn't.
1011|Internal Error|The server is terminating the connection because it encountered an unexpected condition that prevented it from fulfilling the request.
1012|Service Restart|The server is terminating the connection because it is restarting. [[Ref](https://www.ietf.org/mail-archive/web/hybi/current/msg09670.html)]
1013|Try Again Later|The server is terminating the connection due to a temporary condition, e.g. it is overloaded and is casting off some of its clients. [[Ref](https://www.ietf.org/mail-archive/web/hybi/current/msg09670.html)]
1014||**Reserved for future use by the WebSocket standard.**
1015|TLS Handshake|**Reserved**. Indicates that the connection was closed due to a failure to perform a TLS handshake (e.g., the server certificate can't be verified).
1016–1999||**Reserved for future use by the WebSocket standard.**
2000–2999||**Reserved for use by WebSocket extensions.**
3000–3999||Available for use by libraries and frameworks. May not be used by applications. Available for registration at the IANA via first-come, first-serve.
4000–4999||Available for use by applications.

#### 3. available attributes

Name|Type|Description
:--:|:--:|:----------
binaryType|String|Type of transferring data, which should be '**blob**' or '**arraybuffer**'
bufferAmount|Number|Number of sendding data (**read-only**)
extensions|String|Extensions the Server chooses
url|String|Constructor url
protocol|String|Constructor protocol
readyState|Number|Connection state
onclose|Event|Close listener
onerror|Event|Error listener
onmessage|Event|Message Listener
onopen|Event|Open listener

A list of Ready State Code

Constant|Value|Description
:------:|:---:|:----------
CONNECTING|0|The connection is setting up
OPEN|1|The connection has been built up
CLOSING|2|The connection is closing
CLOSED|3|The connection has been closed, or failed to build up

#### 4. Compatibility Problems

- Desktop

Features|Chrome|Firefox (Gecko)|Internet Explorer|Opera|Safari
:------:|:-----|:--------------|:----------------|:----|:-----
Basic|(Yes)|4.0 (2.0)|(Yes)|(Yes)|?
Words Protocol|?|6.0 (6.0)|?|?|?

***Notice that: After Gecko 6.0, constructor has been changed to `MozWebSocket`.***

***Notice that: `extensions` attribute is only supported by Gecko 8.0 or more.***


- Mobile

Features|Android|Firefox Mobile (Gecko)|IE Mobile|Opera Mobile|Safari Mobile
:------:|:------|:---------------------|:--------|:----|:----
Basic|?|7.0 (7.0)|?|?|?
Words Protocol|?|7.0 (7.0)|?|?|?

### Server (PHP)

Even though you're building a server, a client still has to start the WebSocket handshake process. So you must know how to interpret the client's request. The client will send a pretty standard HTTP request that looks like this (**the HTTP version must be 1.1 or greater, and the method must be GET**):

```
GET /socketserver HTTP/1.1
Host: www.example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Origin: http://example.com
Sec-WebSocket-Protocol: socket
Sec-WebSocket-Version: 13
```

#### 1. create a class

```php
<?php
class WebSocket
{
    /** the client */
    private $master;
    
    /** sockets with different state */
    private $socket = [];
    
    /** whether has a handShake */
    private $handShake = false;
    
    public function __construct($address, $port = 80)
    {
        $this->master = socket_create(AF_INET, SOCK_STREAM, SOL_TCP) || die('socket_create() failed');
        
        socket_set_option($this->master, SQL_SOCKET, SO_REUSEADR, 1) || die('socket_option() failed');
        
        socket_bind($this->master, $address, $port) || die('socket_bind() failed');
        
        
    }
}
?>
```