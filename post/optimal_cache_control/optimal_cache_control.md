## [轉載] Defining optimal Cache-Control policy [Back](./../post.md)

> - Author: Google Documents - [Ilya Grigorik](http://igvita.com/)
- Origin: https://developers.google.com/web/fundamentals/performance/optimizing-content-efficiency/http-caching#defining-optimal-cache-control-policy

![](./1.png)

Follow the decision tree above to determine the optimal caching policy for a particular resource, or a set of resources used by your application. Ideally, you should aim to cache as many responses as possible on the client for the longest possible period, and provide validation tokens for each response to enable efficient revalidation.

