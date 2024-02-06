## How to write footer with CSS [Back](./qa.md)

- here is an example of writing footer whose height is **97px**:

```html
<body>
    <div class="container"></div>
    <div id="footer"></div>
</body>
```

```css
* {
	margin: 0;
}

/**
 * html
 */
html {
    height: 100%;
}

/**
 * body
 */
body {
    min-height: 100%;
    height: auto !important;
    height: 100%;
    width: 100%;
    position: relative;
}

/**
 * container
 */
.container {
    padding-bottom: 97px;
}

/**
 * footer
 */
#footer {
    height: 97px;
    width: 100%;
    background-color: #000;
}
```

#### Demo

<p data-height="266" data-theme-id="21735" data-slug-hash="bpbmKd" data-default-tab="result" data-user="aleen42" class='codepen'>See the Pen <a href='http://codepen.io/aleen42/pen/bpbmKd/'>bpbmKd</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>
