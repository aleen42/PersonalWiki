## HEAD [Back](./../HTML.md)

This document is based on the article "[What we can put into the HEAD tag](https://github.com/xiaoyu2er/HEAD)", and here we can see a list of head elements.

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

```