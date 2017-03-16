## Building and Deploying [Back](./../high_performance.md)

While part of work is done during the design and development cycles, the build and deployment phase is also essential and often overlooked, which will always result in performance problems.

This chapter mainly discusses how to efficiently assemble and deploy a JavaScript-based web application.

### 1. JavaScript Minification

JavaScript minification is the process by which a JavaScript file is stripped of everything that does not affect its execution, such as comments or unnecessary whitespace. With reducing such things in the process, a JavaScript file can be smaller to download faster.

Despite of comments and unnecessary whitespace, [the YUI Compressor](http://developer.yahoo.com/yui/compressor/), as a higher level of compaction, has also offered some features for reducing sizes of JavaScript files:

- Replace local variable names with shorter one
- Replace bracket notation with dot notation whenever possible (eg. **foo['bar'] => foo.bar**)
- Replace quoted literal property names whenever possible (eg. **{ 'foo': 'bar'} => { foo: 'bar' }**)
- Replace escaped quotes (eg. **'aaa\'bbb' => "aaa'bbb"**)
- Constant folding (eg. **'foo' + 'bar' => 'foobar'**)

#### 1.1. Buildtime

Runtime build processes are always useful during development, but it's not recommended in a production environment for scalability reasons. As a general rule, everything that can be done at buildtime should not be done at runtime.

#### 1.2. JavaScript Compression

When a web browser requests a resource, it usually sends an `Accept-Encoding` HTTP header (starting with HTTP/1.1) to let the web server know what kinds of encoding transformations it supports. This information is primarily used to allow a document to be compressed, enabling faster downloads and therefore a better user experience. Possible values for this header includes: `gzip`, `compress`, `deflate`, and `identity`. If the web server has seen this header in the request, it will choose the most appropriate encoding method and notify the client side with setting `Content-Encoding` HTTP header.

### 2. Caching JavaScript Files

Web servers use the `Expires` HTTP response header to let clients know how long a resource can be cached. Despite of this header, web servers can also use `Cache-Control` header to do the same thing.

If available, developers can also consider using client-side storage mechanisms, like `cookie`, `sessionStorage`, and `localStorage`.

Offline application cache offered by HTML 5 can be another alternative for caching files, with adding a `manifest` attribute to the `<html>` tag:

```html
<!DOCTYPE html>
<html manifest="test.manifest">
</html>
```

The manifest file uses a special syntax to list offline resources and must be served using the `text/cache-manifest` mime type at the same time.

### 3. Using a Content Delivery Network (CDN)

A content delivery network (CDN) is a network of computers distributed geographically across the Internet that is responsible for delivering content to end users. With serving closer to the user, CDNs are able to decrease network latency to improve performance of loading sources.

### 4. Summary

The build and deployment process can have an impact on the performance of a JavaScript-based application. The most important steps of this process are:

- Combining JavaScript files to reduce the number of HTTP requests
- Minifying JavaScript files using the YUI Compressor
- Serving JavaScript file compressed (gzip encoding)
- Setting appropriate HTTP headers to cache resources
- Using a CDN to serve JavaScipt files.
