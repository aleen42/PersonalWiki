## [轉載] Caching checklist [Back](./../leverage_browser_caching.md)

> - Author: Google Documents - [Ilya Grigorik](http://igvita.com/)
- Origin: https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#caching-checklist

There is no one best cache policy. Depending on your traffic patterns, type of data served, and application-specific requirements for data freshness, you will have to define and configure the appropriate per-resource settings, as well as the overall "caching hierarchy".

Some tips and techniques to keep in mind as you work on caching strategy:

1. **Use consistent URLs**: if you serve the same content on different URLs, then that content will be fetched and stored multiple times. Tip: note that [URLs are case sensitive](http://www.w3.org/TR/WD-html40-970708/htmlweb.html)!
2. **Ensure the server provides a validation token (ETag)**: validation tokens eliminate(消除) the need to transfer the same bytes when a resource has not changed on the server.
3. **Identify which resources can be cached by intermediaries(媒介)**: those with responses that are identical(完全相同的) for all users are great candidates to be cached by a CDN and other intermediaries.
4. **Determine the optimal cache lifetime for each resource**: different resources may have different freshness requirements. Audit and determine the appropriate max-age for each one.
5. **Determine the best cache hierarchy for your site**: the combination of resource URLs with content fingerprints, and short or no-cache lifetimes for HTML documents allows you to control how quickly updates are picked up by the client.
6. **Minimize churn(攪拌動作)**: some resources are updated more frequently than others. If there is a particular part of resource (e.g. JavaScript function, or set of CSS styles) that are often updated, consider delivering that code as a separate file. Doing so allows the remainder of the content (e.g. library code that does not change very often), to be fetched from cache and minimizes the amount of downloaded content whenever an update is fetched.