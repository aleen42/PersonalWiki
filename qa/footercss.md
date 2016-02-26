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
    position: absolute;
	bottom: 0;
	z-index: -1;
}
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
