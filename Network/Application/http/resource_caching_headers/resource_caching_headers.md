## Headers around resource caching [Back](../http.md)

### 1. [`Last-Modified`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Last-Modified) (RESPONSE)

The last modification date of the resource, used to compare several versions of the same resource. It is less accurate than [`ETag`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/ETag), but easier to calculate in some environments. Conditional requests using [`If-Modified-Since`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Modified-Since) and [`If-Unmodified-Since`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Unmodified-Since) use this value to change the behavior of the request.

### 2. [`If-Modified-Since`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Modified-Since) (REQUEST)

Makes the request conditional, and expects the resource to be transmitted only if it has been modified after the given date. This is used to transmit data only when the cache is out of date.

### 3. [`ETag`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/ETag) (RESPONSE)

A unique string identifying the version of the resource. Conditional requests using [`If-Match`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Match) and [`If-None-Match`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-None-Match) use this value to change the behavior of the request.

### 4. [`If-None-Match`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-None-Match) (REQUEST)

Makes the request conditional, and applies the method only if the stored resource *doesn't* match any of the given ETags. This is used to update caches (for safe requests), or to prevent to upload a new resource when one already exists.

### 5. [`Cache-Control`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control) (REQUEST / RESPONSE)

Directives for caching mechanisms in both requests and responses.

### 6. [`Expires`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Expires) (RESPONSE)

> If there is a [`Cache-Control`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control) header with the `max-age` or `s-maxage` directive in the response, the `Expires` header is ignored.

The date/time after which the response is considered expired.
