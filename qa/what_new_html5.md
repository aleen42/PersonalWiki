## What's new in HTML5 [Back](./qa.md)

HTML5 has provided a lot of new tags:

- Printing: `<canvas>`
- Multimedia: `<video>` and `<audio>`
- Storage: `localStorage` and `sessionStorage`
- Semantic: `<article>`, `<footer>`, `<header>`, `<nav>` , and `<section>`
- Form: `<input type="calendar">`, `<input type="date">`, `<input type="time">`, `<input type="email">`, `<input type="url">`, and `<input type="search">`
- Technology: `webworker`, `websocket`, and `Geolocation`

HTML5 has removed some old tags:

- Behavior: `<font>`, `<basefont>`, `<big>`, `<center>`, `<s>`, `<strike>`, `<tt>`, and `<u>`
- Side Effect: `<frame>`, `<frameset>` , and `<noframes>`

#### Compatibility Problems

We can use `document.createElement()` to create a new HTML5 tag in IE6/IE7/IE8 (*remember to define the default style of those tags*), or we can also use `html5shim` like this:

```html
<!--[if lt IE 9]>
    <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
<[endif]-->
```

#### How to distinguish HTML5?

Just distinguish it from `<!DOCTYPE>` or tags.

#### HTML5 Offline Storage

- **Theory**: HTML5 Offline Storage is based on the cache of a new file named `.appcache`, which will list resources that should be cached. Those cached resources will be stored into local like Cookie, and extracted when offline.
- **Useage**: 
    1. set `manifest` attribute in the `<html>` tag.
        ```html
        <html manifest="cache.manifest"></html>
        ```
    2. create a file named `cache.manifest`:
        ```manifest
        CACHE MANIFEST
        #v0.11
        
        CACHE:
        
        js/app.js
        css/style.css
        
        NETWORK:
        resourse/logo.png
        
        FALLBACK:
        / /offline.html
        ```
        
        - **CACHE**: a list of resources to be cached. (*pages will be automatically cached, so you don't need to list them*)
        - **NETWORK**: a list of resources which should be read online.
        - **FALLBACK**: resources to replace those failed to access online.