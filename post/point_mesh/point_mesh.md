## [轉載] Create a Dynamic Point Mesh Animation with HTML5 Canvas [Back](./../post.md)

> - Author: [Dudley Storey](http://dudleystorey.com/)
- Origin: http://thenewcode.com/1159/Create-a-Dynamic-Point-Mesh-Animation-with-HTML5-Canvas?utm_source=codropscollective
- Time: Nov, 22nd, 2016

<p>
<p data-height="388" data-theme-id="21735" data-slug-hash="oYeVyd" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Dynamic Point Mesh Animation with HTML5 Canvas" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/oYeVyd/">Dynamic Point Mesh Animation with HTML5 Canvas</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

Perhaps one of the most recognizable visual motifs of the last several years is the animation style you should see above; I’m not sure it has a name, but I call it a *dynamic point mesh animation*. This is my variation on the style, derived from previous work by Daniel Mayovskiy.

Frequently such animations are layered behind other content, so it makes sense to size this example to the same size as the viewport:

```html
<canvas id="canvas"></canvas>
```

The CSS:

```css
body {
    background: #222;
    margin: 0rem;
    min-height: 100vh;
}

#canvas {
    position: absolute;
    display: block;
    top: 0;
    left: 0;
    z-index: -1;
}
```

> The [Codepen version of this code](https://codepen.io/dudleystorey/pen/NbNjjX) has a little more detail, including the CSS and markup for placing the text on top of the animation.

To ensure that the [&lt;canvas&gt;](http://thenewcode.com/1128/Web-Developer-Reading-List-The-Canvas-API) is always the full height and width of the viewport, the first part of the [JavaScript](http://thenewcode.com/1135/Web-Developer-Reading-List-JavaScript) at the end of the page is a resize function:

```js
let resizeReset = function() {
    w = canvasBody.width = window.innerWidth;
    h = canvasBody.height = window.innerHeight;
}
```

### Creating the Dots

`opts` is an [object](http://thenewcode.com/770/JavaScript-Fundamentals-Objects) that contains a series of properties that act as default values for the script:
