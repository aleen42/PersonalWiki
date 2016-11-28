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

```js
const opts = { 
    particleColor: "rgb(200,200,200)",
    lineColor: "rgb(200,200,200)",
    particleAmount: 40,
    defaultSpeed: 1,
    variantSpeed: 1,
    defaultRadius: 2,
    variantRadius: 2,
    linkRadius: 200,
}
```

The variants for speed and radius are used to add [randomness](http://thenewcode.com/82/Recipes-for-Randomness-in-JavaScript) to the size and movement of the mesh points; linkRadius is how close the points must come before they are joined with lines.

The &lt;canvas&gt; element must be resized so that the particles always meet the edge of the browser window. The `resizeReset()` function is called once on script load, but needs to be throttled or “debounced” so that it doesn’t slow down the script during operation of the rest of the page:

```js
let delay = 200, tid;

window.addEventListener("resize", function(){
        deBouncer();
});

let deBouncer = function() {
    clearTimeout(tid);
    tid = setTimeout(function() {
        resizeReset();
    }, delay);
};
```

The Particle object is a fairly large function that generates each of the “dots”:

```js
Particle = function(xPos, yPos){ 
    this.x = Math.random() * w; 
    this.y = Math.random() * h;
    this.speed = opts.defaultSpeed + Math.random() * opts.variantSpeed; 
    this.directionAngle = Math.floor(Math.random() * 360); 
    this.color = opts.particleColor;
    this.radius = opts.defaultRadius + Math.random() * opts. variantRadius; 
    this.vector = {
        x: Math.cos(this.directionAngle) * this.speed,
        y: Math.sin(this.directionAngle) * this.speed
    };
    this.update = function(){ 
        this.border(); 
        this.x += this.vector.x; 
        this.y += this.vector.y; 
    };
    this.border = function(){ 
        if (this.x >= w || this.x <= 0) { 
            this.vector.x *= -1;
        }
        if (this.y >= h || this.y <= 0) {
            this.vector.y *= -1;
        }
        if (this.x > w) this.x = w;
        if (this.y > h) this.y = h;
        if (this.x < 0) this.x = 0;
        if (this.y < 0) this.y = 0; 
    };
    this.draw = function(){ 
        drawArea.beginPath();
        drawArea.arc(this.x, this.y, this.radius, 0, Math.PI*2);
        drawArea.closePath();
        drawArea.fillStyle = this.color;
        drawArea.fill();
    };
};
```

In the context of the script, this refers to each [particle](http://thenewcode.com/1133/Animation-Fundamentals-Understanding-Particles), as it is created:

- the initial position, speed and angle of each particle are decided randomly; the particle’s color is determined from the associated option setting.
- this.vector stores the direction of the particle: if this.vector.x is 1, it’s moving to the right; if -1, it’s moving to the left. Similarly, if this.vector.y is negative, it’s moving up, if positive, it’s moving down.
- this.update calculates the next coordinates for each particle. First, it checks if the particle is touching the border; if the particle goes past the dimensions of the canvas, it’s vector is changed, multiplied by -1 to produce the opposite direction
- a window resize may leave a particle further across the perimeter than the border function will capture, so a series of if statements checks if that’s the case, resetting the position of the particle to the current limits of the canvas.
- finally, the dots are drawn in place.
