## HTTP Response Status Code [Back](./../JavaScript.md)

### 1xx Infomational

#### 100 Continue

The Server has received the request headers and the client should proceed to send the request body (like a POST request). To have a server check the request's headers, a client must send `Expect: 100-continue` as a header in its initial request and receive a `100 Continue` status code in response before sending the body. The response `417 Expectation Failed` indicates the request should not be continued.

#### 101 Switching Protocols

The requester has asked the server to switch protocols and the server has agreed to do so.

#### 102 Processing (WebDAV)

A WebDAV request may contain many sub-requests involving **file operations**, requiring a long time to complete the request. This code indicates that the server has received and is processing the request, but no response is available yet.

### 2xx Success

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

The server is delivering only part of the resource (byte serving) due to a range header sent by the client. The range header is used by HTTP clients to enable resuming of interrupted downloads, or split a download into multiple simultaneous(同步) streams.
