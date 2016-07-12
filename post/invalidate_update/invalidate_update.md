## [轉載] Invalidating(失效) and updating cached responses [Back](./../post.md)

> - Author: Google Documents - [Ilya Grigorik](http://igvita.com/)
- Origin: https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#defining-optimal-cache-control-policy

<br />

> TL;DR

> Locally cached responses are used until the resource 'expires'

> Embedding a file content fingerprint in the URL enables us to force the client(the browser) to update to a new version of the response

> Each application needs to define its own cache hierarchy for optimal performance

