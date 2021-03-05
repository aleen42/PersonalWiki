## HTTP Request Methods [Back](../JavaScript.md)

<table>
    <thead>
        <th>Methods</th>
        <th>Description</th>
    </thead>
    <tbody>
        <tr>
            <td><a href="#1-get-method">GET</a></td>
            <td>Retrieve information from servers with a given URL with only one requests.</td>
        </tr>
        <tr>
            <td><a href="#2-head-method">HEAD</a></td>
            <td>Retrieve header information only, and request like GET.</td>
        </tr>
        <tr>
            <td><a href="#3-post-method">POST</a></td>
            <td>Used to send data to servers, with two requests. (One for identification, and the other for data transferring)</td>
        </tr>
        <tr>
            <td><a href="#4-put-method">PUT</a></td>
            <td>Replace target data on servers from uploaded data.</td>
        </tr>
        <tr>
            <td><a href="#5-delete-method">DELETE</a></td>
            <td>Delete target data on servers with a given URL.</td>
        </tr>
        <tr>
            <td><a href="#6-connect-method">CONNECT</a></td>
            <td>Establish a identified tunnel to servers with a given URL.</td>
        </tr>
        <tr>
            <td><a href="#7-options-method">OPTIONS</a></td>
            <td>Describe the communication options for the target resource, like performances information of servers.</td>
        </tr>
        <tr>
            <td><a href="#8-trace-method">TRACE</a></td>
            <td>Performs a message loop-back test along the path to the target resource.</td>
        </tr>
    </tbody>
</table>

### 1. GET Method

With specific URL in the portion of the request, a GET request retrieves data from a web server. It is mainly used for retrieving documents like HTML files:

```
GET /hello.html HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
```

And the response header performs like this:

```
HTTP/1.1 200 OK
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Last-Modified: Wed, 22 Jul 2019 19:15:56 GMT
ETag: "34aa387-d-1568eb00"
Vary: Authorization,Accept
Accept-Ranges: bytes
Content-Length: 88
Content-Type: text/html
Connection: Closed
```

Response data is:

```html
<!DOCTYPE HTML>
<html lang="" >
<!-- ... -->
</html>
```

### 2. HEAD Method

Similar to GET, the HEAD method can also retrieve data from a web server with given URL, but the data is header section only:

```
HEAD /hello.htm HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
```

With similar response header:

```
HTTP/1.1 200 OK
ETag: "34aa387-d-1568eb00"
Vary: Authorization,Accept
Accept-Ranges: bytes
Content-Length: 88
Content-Type: text/html
Connection: Closed
```

But no returned data.

### 3. POST Method

When sending data to servers like uploading a file, the POST method is the way we commonly choose.

```
POST /upload HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
Content-Type: text/xml; charset=utf-8
Content-Length: 88
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
```

```xml
<?xml version="1.0" encoding="utf-8"?>
<!-- data -->
```

Then we can check the process from the response header and data:

```
HTTP/1.1 200 OK
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Last-Modified: Wed, 22 Jul 2019 19:15:56 GMT
ETag: "34aa387-d-1568eb00"
Vary: Authorization,Accept
Accept-Ranges: bytes
Content-Length: 88
Content-Type: text/html
Connection: Closed
```

```json
{
  "code": 200,
  "message": "Processed Successfully"
}
```

### 4. PUT Method

The PUT method is used to request the server to store data with a given URL:

```
PUT /hello.html HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
Accept-Language: en-us
Connection: Keep-Alive
Content-type: text/html
Content-Length: 182
```

```html
<html>
<body>
<h1>Hello, World!</h1>
</body>
</html>
```

Then, the server will store the given entity-body in **hello.html** file at the root path, and response with:

```
HTTP/1.1 201 Created
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Content-type: text/html
Content-length: 30
Connection: Closed
```

### 5. DELETE Method

Now that we can replace target resources with PUT method, we can also delete it by using DELETE method:

```
DELETE /hello.html HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
Accept-Language: en-us
Connection: Keep-Alive
```

And then get responses like that:

```
HTTP/1.1 200 OK
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Content-type: text/html
Content-length: 30
Connection: Closed
```

### 6. CONNECT Method

When needing to establish a network connection to a web server over HTTP, you can use CONNECT method:

```
CONNECT aleen42.github.io HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
```

And when established, the response will be sent back to the client:

```
HTTP/1.1 200 Connection established
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
```

### 7. OPTIONS Method

The OPTIONS method is used by the client to find out the HTTP methods and other options supported by a web server. The following example requests a list of methods supported by a web server running on *aleen42.github.io*:

```
OPTIONS * HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
```

The server will send an information based on the current configuration of the server, for example:

```
HTTP/1.1 200 OK
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Allow: GET,HEAD,POST,OPTIONS,TRACE
Content-Type: httpd/unix-directory
```

### 8. TRACE Method

The TRACE method is used to echo the contents of an HTTP Request back to the requester which can be used for debugging purpose at the time of development. The following example shows the usage of TRACE method:

```
TRACE / HTTP/1.1
Host: aleen42.github.io
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
```

The server will send the following message in response to the above request:

```
HTTP/1.1 200 OK
Date: Wed, 27 Feb 2019 03:44:32 GMT
Server: nginx
Connection: close
Content-Type: message/http
Content-Length: 39

TRACE / HTTP/1.1
Host: aleen42.github.io
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36
```
