## Different versions of HTTP [Back](../JavaScript.md)

Since the HTTP (Hypertext Transfer Protocol) released in 1991 with version 0.9, it has been developed into different versions like HTTP/1.0, HTTP/1.1, HTTP/2.0 or even HTTP/3.0 recently. And this note has marked down how it developed, and for what.

### 1. Basic Optimizations

There are two main factors which have affected the performance of HTTP requests: **Bandwidth** and **Latency (延迟)**.

- **Bandwidth**: this factor has usually been optimized physically like using an advanced netting twine for transferring, so the HTTP protocol won't pay more attention to it.
- **Latency**:
    - HOL Blocking (a.k.a blocking from browsers): it depends on how many connections browsers have used to complete requests.
    - DNS Lookup: the time for looking up IP from DNS servers, and it depends on caching or the distance from the client to DNS servers.
    - Initial Connection: HTTP is based on TCP, which means that it has to use three-packet handshake to confirm connections, and this initialization can be a delayed processes according to browsers.

### 2. From HTTP/1.0 to HTTP/1.1

#### 2.1 Cache

In HTTP/1.0, the main headers for caching ([**304**, *Not Modified*](../http_reponse_status_code/http_reponse_status_code.md#304-not-modified-notes)) are `If-Modified-Since / Last Modified` and `Expires`, while HTTP/1.1 has brought `Etag / If-None-Match` (Entity tag) for more flexible cache controlling.

#### 2.2 Connection Enhancement

In HTTP/1.0, most responses are quite huge for client to receive, and the transferring can not resume. For enhancement, HTTP/1.1 has used `Range` header to support receiving parts of responses ([**206**, *Partial Contents*](../http_reponse_status_code/http_reponse_status_code.md#206-partial部分-content)).

#### 2.3 New Status Code

HTTP/1.1 has added 24 status code for errors, like [**409** (Conflict)](../http_reponse_status_code/http_reponse_status_code.md#409-conflict), or [**410** (Gone)](../http_reponse_status_code/http_reponse_status_code.md#410-gone).

#### 2.4 Hosting

In HTTP/1.0, there should be only one IP for one client, but it has been recognized unreal soon. Without so many IPs, multiple clients can share one IP at the same time, which means that the protocol need to change to distinguish from those clients. HTTP/1.1 has released `Host` header to do so. If the header has not transferred, it should throw an error [**400** (Bad Request)](../http_reponse_status_code/http_reponse_status_code.md#400-bad-request)

#### 2.5 Persistent Connections (长连接)

HTTP/1.1 has supported persistent connections and pipe lining (流水线) with setting the header `Connection` with `keep-alive`. In such a TCP pipeline, it can transfer multiple requests rather than one before.

### 3. HTTPS and HTTP

In short word, **HTTPS** (HTTP over TLS, or HTTP over SSL) is another encrypted protocol for protecting contents during transferring, to avoid exposition among agents, and the encryption layer is so-called **SSL/TLS**.

```mind:height=100,title=HTTP
# TCP
## HTTP
```

```mind:height=100,title=HTTPS
# TCP
## SSL/TLS
### HTTP
```

The certification of encryption need to be requested from CA, and it is always paid.

The default port of HTTP is 80, while which of HTTPS is 443.

### 4. SPDY

**SPDY** is a layer developed based on TCP by Google, and it has improved performance of latency, and solved vulnerabilities at the same time.

1. SPDY has used so-called *multiplexing* (多路复用) to share a same TCP connection with multiple requests, which has solved HOL Blocking.
2. SPDY has also applied different priorities for each requests, so that the major one won't be blocked by others in multiplexing. For instance, the requested document should be answered first for showing, before loading static resources, like scripts, and stylesheets.
3. Headers can be compressed well with proper algorithms in SPDY.
4. SPDY is based on SSL.
5. SPDY has also tried to cache some script resources when requesting a stylsheet with same name, like `sample.js` to `sample.css`.

The following diagram has shown the structure of SPDY:

```mind:height=100,title=SPDY
# TCP
## SSL
### SPDY
#### HTTP
```

### 5. HSTS (Http Strict Transport Security)

**HSTS** is a web security policy mechanism that enforce clients to interact with HTTPS connections by sending a response header set with `Strict-Transport-Security` as specified in [MDN](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Strict-Transport-Security).

This feature has the following compatibilities of different browsers:

| Browsers |  Chrome   | Firefox | Safari | IE | Edge |
|:---------|:---------:|:-------:|:------:|:--:|:----:|
| Versions | 4.0.211.0 |   17    |  10.9  | 11 |  √   |
