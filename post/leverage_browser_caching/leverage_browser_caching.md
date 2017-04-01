## [轉載] Leverage Browser Caching [Back](./../post.md)

> - Author: Google Documents
> - Origin: https://developers.google.com/speed/docs/insights/LeverageBrowserCaching
> - Time: Apr, 8th, 2015


This rule triggers when **PageSpeed Insights** detects that the response from your server **does not include caching headers** or if the resources are specified to be **cached for only a short time**.

### Overview

Fetching resources over the network is both slow and expensive: the download may require multiple roundtrips(來回往返的傳遞) between the client and server, which delays processing and may block rendering of page content, and also incurs(招致) data costs for the visitor. All server responses should specify a caching policy to help the client determine if and when it can reuse a previously fetched response.

### Recommendations

Each resource should specify an explicit caching policy that answers the following questions: **whether** the resource **can** be cached and **by whom**, for **how long**, and if applicable(適用), how it can be efficiently revalidated(重新驗證) when the caching policy expires. When the server returns a response it must provide the `Cache-Control` and `ETag` headers:

- `Cache-Control` defines how, and for how long the individual response can be cached by the browser and other intermediate caches. To learn more, see [caching with Cache-Control](https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#cache-control).
- `ETag` provides a revalidation token that is automatically sent by the browser to check if the resource has changed since the last time it was requested. To learn more, see [validating cached responses with ETags](https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#validating-cached-responses-with-etags).

To determine the optimal caching policy for your site, please use the following guides:

- [Defining optimal Cache-Control policy](./optimal_cache_control/optimal_cache_control.md)
- [Invalidating and updating cached responses](./invalidate_update/invalidate_update.md)
- [Caching checklist](./caching_checklist/caching_checklist.md)

We recommend **a minimum cache time of one week** and preferably(最好) up to one year for static assets, or assets that change infrequently. If you need precise control over when resources are invalidated we recommend using a **URL fingerprinting(URL 指紋)** or versioning technique - see invalidating and updating cached responses link above.
