## HTTP Response Status Code [Back](./../JavaScript.md)

### 1xx Infomational

This class of status code indicates a provisional(臨時的) response, consisting only of the `Status-Line` and optional headers, and is terminated by an empty line. Since HTTP/1.0 did not define any 1xx status codes, servers **must not** send a 1xx response to an HTTP/1.0 client except under experimental conditions.

#### 100 Continue

The Server has received the request headers and the client should proceed to send the request body (like a POST request). To have a server check the request's headers, a client must send `Expect: 100-continue` as a header in its initial request and receive a `100 Continue` status code in response before sending the body. The response `417 Expectation Failed` indicates the request should not be continued.

#### 101 Switching Protocols

The requester has asked the server to switch protocols and the server has agreed to do so.

#### 102 Processing (WebDAV)

A WebDAV request may contain many sub-requests involving **file operations**, requiring a long time to complete the request. This code indicates that the server has received and is processing the request, but no response is available yet.

### 2xx Success

This class of status codes indicates the action requested by the client was received, understood, accepted, and processed successfully.

#### 200 OK

Standard response for successful HTTP requests.

The actual response will depend on the request method used. In a GET request, the response will contain an entity corresponding to the requested resource. In a POST request, the response will contain an entity describing or containing the result of the action.

#### 201 Created

The request has been fulfilled, resulting in the creation of a new resource.

#### 202 Accepted

The request has been accepted for processing, but the processing has not been completed.

#### 203 Non-Authoritative Information (since HTTP/1.1)

The server is a transforming proxy (e.g. a Web accelerator) that received a 200 OK from its origin, but is returning a modified version of the origin's response.

#### 204 No Content

The server successfully processed the request and is not returning any content.

#### 205 Reset Content

The server successfully processed the request, but is not returning any content. Unlike a 204 response, this response requires that the requester reset the document view.

#### 206 Partial(部分) Content

The server is delivering only part of the resource (byte serving) due to a range header sent by the client. The range header is used by HTTP clients to enable resuming of interrupted downloads, or split a download into multiple simultaneous streams(同步流).

#### 207 Multi-Status(WebDAV)

The message body that follows is an XML message and can contain a number of separate response codes, depending on how many sub-requests were made.

#### 208 Already Reported(WebDAV)

The members of a DAV binding have already been enumerated in a previous reply to this request, and are not being included again.

#### 226 IM Used

The server has fulfilled a request for the resource, and the response is a representation of the result of one or more instance-manipulations applied to the current instance. Many of them are used in **URL Redirection**.

### 3xx Redirection

This class of status code indicates the client must take additional action to complete the request.

#### 300 Multiple Choices

Indicates multiple options for the resource from which the client may choose to redirect into.

#### 301 Moved Permanently

This and all future requests should be directed to the given URI.

#### 302 Found

Indicates that the server require the client to perform a temporary redirect. 

#### 303 See Other

The response to the request can be found under another URI using a GET method. When received in response to a POST (or PUT/DELETE), the client should presume that the server has received the data and should issue a redirect with a separate GET message.

#### 304 Not Modified ([Notes](https://github.com/aleen42/PersonalWiki/issues/29))

Indicates that the resource has not been modified since the version specified by the request headers `If-Modified-Since` or `If-None-Match`. In such case, there is no need to retransmit(重發) the resource since the client still has a previously-downloaded copy.

#### 305 Use Proxy

The requested resource is available only through a proxy, the address for which is provided in the response.

#### 306 Switch Proxy

No longer used.

#### 307 Temporary Redirect (Response to 302)

In this case, the request should be repeated with another URI; however, future requests should still use the original URI. In contrast to how 302 was historically implemented, **the request method is not allowed to be changed** when reissuing the original request.

#### 308 Permanent Redirect (Response to 301)

The request and all future requests should be repeated using another URI.

307 and 308 parallel the behaviors of 302 and 301, but **do not allow the HTTP method to change**.

### 4xx Client Error

The 4xx class of status code is intended for situations in which the client seems to have erred.

#### 400 Bad Request

The server cannot or will not process the request due to an apparent client error (e.g., malformed request syntax, too large size, invalid request message framing, or deceptive request routing)

#### 401 Unauthorized

Similar to `403 Fobidden`, but specifically for use when authentication is required and has failed or has not yet been provided. The response must include a `WWW-Authenticate` header field containing a challenge applicable to the requested resource.

*Notice: some sites issue 401 when an IP is banned from accessing by the server.*

#### 402 Payment Required

Reserved for future use. The original intention was that this code might be used as part of some form of digital cash or micro-payment scheme, but that has not happened, and this code is not usually used.

#### 403 Fobidden

The request was a valid request, but the server is refusing to respond to it. The user might be logged in but does not have the necessary permissions for the resource.

#### 404 Not Found

The requested resource could not be found but may be available in the future

#### 405 Method Not Allowed

A request method is not supported for the requested resource; for example, a GET request on a form which requires data to be presented via POST, or a PUT request on a read-only resource.

#### 406 Not Acceptable

The requested resource is capable of generating only content not acceptable according to the `Accept` headers sent in the request.

#### 407 Proxy Authentication Required

The client must first authenticate itself with the proxy.

#### 408 Request Timeout

The server timed out waiting for the request.

#### 409 Conflict

Indicates that the request could not be processed because of conflict in the request, such as an edit conflict between multiple simultaneous updates.

#### 410 Gone

Indicates that the resource requested is no longer available and will not be available again.

#### 411 Length Required

The request did not specify the length of its content, which is required by the requested resource.

#### 412 Precondition Failed

The server does not meet one of the preconditions that the requester put on the request.

#### 413 Payload Too Large

The request is larger than the server is willing or able to process. Previously called "Request Entity Too Large".

#### 414 URI Too Long

The URI provided was too long for the server to process. Often the result of too much data being encoded as a query-string of a GET request, in which case it should be converted to a POST request.

#### 415 Unsupported Media Type

The request entity has a media type which the server or resource does not support.

#### 416 Range Not Stasfiable

The client has asked for a portion(部分) of the file (byte serving), but the server cannot supply that portion.

#### 417 Expectation Failed

The server cannot meet the requirements of the `Expect` request-header field.

#### 418 I'm a teapot

This code was defined in 1998 as one of the traditional IETF April Fools' jokes, in RFC 2324.

#### 421 Misdirected Request

The request was directed at a server that is not able to produce a response.

#### 422 Unprocessable Entity(WebDAV)

The request was well-formed but was unable to be followed due to semantic errors.

#### 423 Locked(WebDAV)

The resource that is being accessed is locked.

#### 424 Failed Dependency(WebDAV)

The request failed due to failure of a previous request.

#### 426 Upgrade Required

The client should switch to a different protocol such as TLS/1.0, given in the [`Upgrade` header](https://en.wikipedia.org/wiki/Upgrade_header) field.

#### 428 Precondition Required

The origin server requires the request to be conditional.

#### 429 Too Many Requests

The user has sent too many requests in a given amount of time.

#### 431 Request Header Fields Too Large

The server is unwilling to process the request because either an individual header field, or all the header fields collectively, are too large.

#### 451 Unavailable For Legal Reasons

A server operator has received a legal demand to deny access to a resource or to a set of resources that includes the requested resource.

### 5xx Server Error

The server failed to fulfill an apparently valid request.

#### 500 Internal Server Error

A generic error message, given when an unexpected condition was encountered(遭遇) and no more specific message is suitable.

#### 501 Not Implemented

The server either does not recognize the request method, or it lacks the ability to fulfill the request. Usually this implies future availability.

#### 502 Bad Gateway

The server was acting as a gateway or proxy and received an invalid response from the upstream server.

#### 503 Service Unavailable

The server is currently unavailable (because it is overloaded or down for maintenance). Generally, this is a temporary state.

#### 504 Gateway Timeout

The server was acting as a gateway or proxy and did not receive a timely response from the upstream server.

#### 505 HTTP Version Not Supported

The server does not support the HTTP protocol version used in the request.

#### 506 Variant Also Negotiates

Transparent content negotiation for the request results in a circular reference.

#### 507 Insufficient Storage(WebDAV)

The server is unable to store the representation needed to complete the request.

#### 508 Loop Detected(WebDAV)

The server detected an infinite loop while processing the request

#### 510 Not Extended

Further extensions to the request are required for the server to fulfill it.

#### 511 Network Authentication Required

The client needs to authenticate to gain network access. Intended for use by intercepting proxies used to control access to the network (e.g., "captive portals" used to require agreement to Terms of Service before granting full Internet access via a Wi-Fi hotspot).

