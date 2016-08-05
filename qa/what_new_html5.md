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