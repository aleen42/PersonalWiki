## HEAD [Back](./../HTML.md)

This document is based on the article "[What we can put into the HEAD tag](https://github.com/joshbuchea/HEAD)", and here we can see a list of head elements.

#### Normal Elements

```html
<!-- title of the document -->
<title>Page Title</title>

<!-- base url for relative path of sources -->
<!-- in HTML, base tag can be without closed tag -->
<base href="http://aleen42.github.io">
<!-- in XHTML, the closed tag should be here -->
<base href="http://aleen42.github.io" />

<!-- style sheets -->
<style>
body {
    margin: 0; 
    padding: 0;
}
</style>

<!-- script -->
<script type="text/javascript" src="./main.js"></script>
```

#### Meta Elements

This kind of elements will provide meta data about HTML documents, and they won't be shown on the page. However, they can be read by machines, used for browsers, search engine and other web servers.

```html
<!-- content-type(setting fonts set) -->
<!-- HTML old version -->
<meta http-equiv="content-Type" content="text/html;charset=utf-8">
<!-- HTML5 -->
<meta charset="utf-8">

<!-- use the newest IE version and Chrome -->
<meta http-equiv="x-ua-compatible" content="ie=edge">

<!-- kernel control -->
<!-- 
    most browsers in China will use one of these kernels: Webkit for Chrome or Trident for IE.
    Webkit: used for fast rendering
    Trident: used for compatibility of old sites
-->
<meta name="renderer" content="webkit|ie-comp|ie_stand">

<!-- viewport for mobile website -->
<!--
    viewport is used to optimize presentation of mobile website, 
    and if the website is not reponsive, it's not recommended that 
    use `initial-scale=1` and `user-scalable=no`
-->
<meta name="viewport" content="width=device-width, initial-scale=1">

<!-- keywords -->
<!--
    keywords is used for easily searching in a search engine. When you
    set up your keywords, people can search your website with the keywords
    you set.
    It's suggested to set more keywords and not more than 874 characters.
-->
<meta name="keywords" content="aleen42,personalwiki">

<!-- description -->
<!--
    each site should have a description itself which should not be
    more than 150 characters.
-->
<meta name="description" content="not more than 150 characters">

<!-- subjects -->
<meta name="subject" content="your subjects of your site">

<!-- search engines -->
<!-- 
    content value:
    "all": file will get index, and all the links of this site can be searched.
    "none": file won't get index, and all the links of this site cannot be searched.
    "index": file will get index.
    "follow": all the links of this site can be searched.
    "noindex": file won't get index.
    "nofollow": all the links of this site cannot be searched.
-->
<meta name="googlebot" content="index,follow">

<!-- other elements -->
<meta name="google" content="nositelinkssearchbox">
<meta name="google-site-verification" content="verification_token">
<meta name="abstract" content="">
<meta name="topic" content="">
<meta name="summary" content="">
<meta name="classification" content="business">
<meta name="url" content="https://example.com/">
<meta name="identifier-URL" content="https://example.com/">
<meta name="directory" content="submission">
<meta name="category" content="">
<meta name="coverage" content="Worldwide">
<meta name="distribution" content="Global">
<meta name="rating" content="General">
<meta name="referrer" content="never">
<meta http-equiv="Content-Security-Policy" content="default-src 'self'">
```

###### Deprecated/Legacy

Here I have listed some meta elments which are either deprecated or not supported in browsers anymore.

```html
<!-- language -->
<!-- 
    this meta elements is deprecated and better use <html lang=""> instead.
-->
<!-- HTML old version -->
<meta name="language" content="zh-CN">
<!-- HTML5 -->
<meta http-equiv="content-language" content="zh-CN" />

<!-- search engines -->
<!-- Deprecated because: Ignored by search engines. Better use robots.txt or modify .htaccess -->
<meta name="robots" content="index,follow">

<!-- Deprecated because: No evidence of use in any search engines -->
<meta name="revised" content="Monday, May 9th, 2016, 11:27 am">

<!-- 
    Deprecated because: Telling the search bots to revisit the page after a period.
    This is not supported because most of the Search Engines nowadays have random 
    intervals for recrawling a webpage.
-->
<meta name="revisit-after" content="7 days">

<!-- personal info -->
<!-- Deprecated because: Provides a easy way for bots to get emails from websites -->
<meta name="reply-to" content="email@example.com">

<!-- Deprecated because: Better to use <link rel="author"> or humans.txt file -->
<meta name="author" content="name, email@example.com">

<!-- Deprecated because: Better to use <link rel="author"> or humans.txt file -->
<meta name="designer" content="aleen42">

<!-- Deprecated because: Better to use <link rel="author"> or humans.txt file -->
<meta name="owner" content="aleen42">

<!-- redirect -->
<!-- Google strongly advises not to use this. Better to set up Apache redirects instead -->
<meta http-equiv="refresh" content="300;url=https://example.com/">

<!-- cache -->
<!--
    Deprecated because: There's no point in doing cache control on client side.
    It is better to configure it on server side than in meta data
-->
<meta http-equiv="Expires" content="0">
<meta http-equiv="Pragma" content="no-cache">
<meta http-equiv="Cache-Control" content="no-cache">
```

#### Link Elements

This kind of elements is used to define a relationship between the document and other outdoor resources.

```html
<link rel="copyright" href="copyright.html">
<link rel="stylesheet" href="https://example.com/styles.css">
<link rel="alternate" href="https://feeds.feedburner.com/martini" type="application/rss+xml" title="RSS">
<link rel="alternate" href="https://example.com/feed.atom" type="application/atom+xml" title="Atom 0.3">
<link rel="alternate" href="https://es.example.com/" hreflang="es">
<link rel="me" href="https://google.com/profiles/thenextweb" type="text/html">
<link rel="archives" href="https://example.com/2003/05/" title="May 2003">
<link rel="index" href="https://example.com/" title="DeWitt Clinton">
<link rel="start" href="https://example.com/photos/pattern_recognition_1_about/" title="Pattern Recognition 1">
<link rel="prev" href="https://example.com/opensearch/opensearch-and-openid-a-sure-way-to-get-my-attention/" title="OpenSearch and OpenID? A sure way to get my attention.">
<link rel="search" href="/search.xml" type="application/opensearchdescription+xml" title="Viatropos">
<link rel="self" type="application/atom+xml" href="https://example.com/atomFeed.php?page=3">
<link rel="first" href="https://example.com/atomFeed.php">
<link rel="next" href="https://example.com/atomFeed.php?page=4">
<link rel="previous" href="https://example.com/atomFeed.php?page=2">
<link rel="last" href="https://example.com/atomFeed.php?page=147">
<link rel="shortlink" href="https://example.com/?p=43625">
<link rel="canonical" href="https://example.com/2010/06/9-things-to-do-before-entering-social-media.html">
<link rel="amphtml" href="https://www.example.com/url/to/amp-version.html">
<link rel="EditURI" href="https://example.com/xmlrpc.php?rsd" type="application/rsd+xml" title="RSD">
<link rel="pingback" href="https://example.com/xmlrpc.php">
<link rel="webmention" href="https://example.com/webmention">
<link rel="manifest" href="manifest.json">
<link rel="author" href="humans.txt">
<link rel="import" href="component.html">

<!-- Prefetching, preloading, prebrowsing -->
<link rel="dns-prefetch" href="//example.com/">
<link rel="preconnect" href="https://www.example.com/">
<link rel="prefetch" href="https://www.example.com/">
<link rel="prerender" href="https://example.com/">
<link rel="subresource" href="styles.css">
<link rel="preload" href="image.png">
<!-- More info: https://css-tricks.com/prefetching-preloading-prebrowsing/ -->

<!-- Favicons -->
<link rel="icon" href="path/to/favicon-16.png" sizes="16x16" type="image/png">
<link rel="icon" href="path/to/favicon-32.png" sizes="32x32" type="image/png">
<link rel="icon" href="path/to/favicon-48.png" sizes="48x48" type="image/png">
<link rel="icon" href="path/to/favicon-62.png" sizes="62x62" type="image/png">
<!-- More info: https://bitsofco.de/all-about-favicons-and-touch-icons/ -->
```

###### Deprecated/Legacy

Here I have listed some meta elments which are either deprecated or not supported in browsers anymore.

```html

```