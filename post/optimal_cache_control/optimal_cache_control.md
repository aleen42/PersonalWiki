## [轉載] Defining optimal Cache-Control policy [Back](./../post.md)

> - Author: Google Documents - [Ilya Grigorik](http://igvita.com/)
- Origin: https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#defining-optimal-cache-control-policy

![](./1.png)

Follow the decision tree above to determine the optimal caching policy for a particular resource, or a set of resources used by your application. Ideally, you should aim to cache as many responses as possible on the client for the longest possible period, and provide validation tokens for each response to enable efficient revalidation.

Cache-Control directives|Explanation
:----------------------:|:----------
max-age=86400|Response can be cached by browser and any intermediary caches (i.e. it is "public") for up to 1 day (60 seconds x 60 minutes x 24 hours)
private, max-age=600|Response can be cached by the client’s browser only for up to 10 minutes (60 seconds x 10 minutes)
no-store|Response is not allowed to be cached and must be fetched in full on every request.