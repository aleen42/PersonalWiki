## [轉載] Invalidating(失效) and updating cached responses [Back](./../post.md)

> - Author: Google Documents - [Ilya Grigorik](http://igvita.com/)
- Origin: https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#defining-optimal-cache-control-policy

<br />

> TL;DR

> Locally cached responses are used until the resource 'expires'

> Embedding a file content fingerprint in the URL enables us to force the client to update to a new version of the response

> Each application needs to define its own cache hierarchy for optimal performance

All HTTP requests made by the browser are first routed to the browser cache to check if there is a valid cached response that can be used to fulfill the request. If there is a match, the response is read from the cache and we eliminate both the network latency and the data costs incurred by the transfer. **However, what if we want to update or invalidate a cached response?**

For example, let’s say we’ve told our visitors to cache a CSS stylesheet for up to 24 hours (max-age=86400), but our designer has just committed an update that we would like to make available to all users. How do we notify all the visitors with what is now a “stale” cached copy of our CSS to update their caches? It’s a trick question - we can’t, at least not without changing the URL of the resource.

Once the response is cached by the browser, the cached version will be used until it is no longer fresh, as determined by max-age or expires, or until it is evicted from cache for some other reason - e.g. the user clearing their browser cache. As a result, different users might end up using different versions of the file when the page is constructed; users who just fetched the resource will use the new version, while users who cached an earlier (but still valid) copy will use an older version of its response.

**So, how do we get the best of both worlds: client-side caching and quick updates?** Simple, we can change the URL of the resource and force the user to download the new response whenever its content changes. Typically, this is done by embedding a fingerprint of the file, or a version number, in its filename - e.g. style.x234dff.css.