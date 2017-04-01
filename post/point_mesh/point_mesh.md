## [轉載] Create a Dynamic Point Mesh Animation with HTML5 Canvas [Back](./../post.md)

> - Author: [Dudley Storey](http://dudleystorey.com/)
> - Origin: http://thenewcode.com/1159/Create-a-Dynamic-Point-Mesh-Animation-with-HTML5-Canvas?utm_source=codropscollective
> - Time: Nov, 22nd, 2016

<p>
<p data-height="388" data-theme-id="21735" data-slug-hash="oYeVyd" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Dynamic Point Mesh Animation with HTML5 Canvas" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/oYeVyd/">Dynamic Point Mesh Animation with HTML5 Canvas</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

Perhaps one of the most recognizable visual motifs of the last several years is the animation style you should see above; I'm not sure it has a name, but I call it a *dynamic point mesh animation*. This is my variation on the style, derived from previous work by [Daniel Mayovskiy](https://codepen.io/Godje/pen/zKazNq).

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

To ensure that the [`&lt;canvas&gt;`](http://thenewcode.com/1128/Web-Developer-Reading-List-The-Canvas-API) is always the full height and width of the viewport, the first part of the [JavaScript](http://thenewcode.com/1135/Web-Developer-Reading-List-JavaScript) at the end of the page is a resize function:

```js
let resizeReset = function () {
    w = canvasBody.width = window.innerWidth;
    h = canvasBody.height = window.innerHeight;
};
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
};
```

The variants for speed and radius are used to add [randomness](http://thenewcode.com/82/Recipes-for-Randomness-in-JavaScript) to the size and movement of the mesh points; `linkRadius` is how close the points must come before they are joined with lines.

The `<canvas>` element must be resized so that the particles always meet the edge of the browser window. The `resizeReset()` function is called once on script load, but needs to be throttled or "debounced" so that it doesn't slow down the script during operation of the rest of the page:

```js
let delay = 200, tid;

window.addEventListener("resize", function () {
    deBouncer();
});

let deBouncer = function () {
    clearTimeout(tid);
    
    tid = setTimeout(function () {
        resizeReset();
    }, delay);
};
```

The `Particle` object is a fairly large function that generates each of the "dots":

```js
Particle = function (xPos, yPos) { 
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
    
    this.update = function () { 
        this.border(); 
        this.x += this.vector.x; 
        this.y += this.vector.y; 
    };
    
    this.border = function () { 
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
    
    this.draw = function () { 
        drawArea.beginPath();
        drawArea.arc(this.x, this.y, this.radius, 0, Math.PI*2);
        drawArea.closePath();
        drawArea.fillStyle = this.color;
        drawArea.fill();
    };
};
```

In the context of the script, `this` refers to each [particle](http://thenewcode.com/1133/Animation-Fundamentals-Understanding-Particles), as it is created:

- the initial position, speed and angle of each particle are decided randomly; the particle's color is determined from the associated option setting.
- `this.vector` stores the *direction* of the particle: if `this.vector.x` is `1`, it's moving to the *right*; if `-1`, it's moving to the *left*. Similarly, if `this.vector.y` is *negative*, it's moving *up*, if *positive*, it's moving *down*.
- `this.update` calculates the *next* coordinates for each particle. First, it checks if the particle is touching the border; if the particle goes past the dimensions of the canvas, it's vector is changed, multiplied by `-1` to produce the *opposite* direction
- a window resize may leave a particle further across the perimeter than the `border` function will capture, so a series of `if` statements checks if that's the case, resetting the position of the particle to the current limits of the canvas.
- finally, the dots are drawn in place.

To start it all moving, we need the following:

```js
function setup() { 
    particles = [];
    
    for (let i = 0; i < opts.particleAmount; i++){
        particles.push( new Particle() );
    }
    
    window.requestAnimationFrame(loop);
}
```

The `setup` function creates a `particles` array, and fills it with a series of particle elements before calling the `loop` function, using `requestionAnimationFrame`.

That `loop` function looks like this:

```js
function loop() { 
    window.requestAnimationFrame(loop);
    drawArea.clearRect(0,0,w,h);
    
    for (let i = 0; i < particles.length; i++){
        particles[i].update();
        particles[i].draw();
    }
}
```

The `loop` function clears the canvas area, updates each particle position, and draws it; the constant refreshing with `requestAnimationFrame()` creates the impression of animation.

Everything is started by calling the `setup()` function, after setting a few other constants and variables and initializing the `resizeReset` function:

```js
const canvasBody = document.getElementById("canvas"),
drawArea = canvasBody.getContext("2d");
let delay = 200, tid;
resizeReset();
setup();
```

At this point, the animation will look like a series of dots moving around the canvas:

<p>
<p data-height="373" data-theme-id="21735" data-slug-hash="ObjqBe" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Dynamic Point Animation with HTML5 Canvas" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/ObjqBe/">Dynamic Point Animation with HTML5 Canvas</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

To create the mesh, we must add a little more code.

### Creating the Lines

To draw the lines, the `loop()` function is added to, becoming:

```js
function loop() { 
    window.requestAnimationFrame(loop);
    drawArea.clearRect(0, 0, w, h);
    
    for (let i = 0; i < particles.length; i++){
        particles[i].update();
        particles[i].draw();
    }
    
    for (let i = 0; i < particles.length; i++){
        linkPoints(particles[i], particles);
    }
}
```

The `linkPoints` function is called for every particle. That function also uses a piece of code called `checkDistance`:

```js
let checkDistance = function (x1, y1, x2, y2) { 
    return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
};
```

The `checkDistance` function determines the distance between each point; if that distance is less than `linkDistance`, the calculated [`opacity`](http://thenewcode.com/1081/CSS-alpha) of the line will be greater than 0, and it will be drawn between the matching points.

Before we get there, the [`rgb` color](http://thenewcode.com/1115/Using-RGB-Color-in-CSS) is broken into its components:

```js
let rgb = opts.lineColor.match(/\d+/g);
```

The `linkPoints` function checks each point against the other particles (referred to as "hubs" in the context of the function) and draws the line at the determined level of [opacity](http://thenewcode.com/1081/CSS-alpha), using [template literals](http://thenewcode.com/1156/Better-JavaScript-Concatenation-with-Template-Literals):

```js
let linkPoints = function (point1, hubs) { 
    for (let i = 0; i < hubs.length; i++) {
        let distance = checkDistance(point1.x, point1.y, hubs[i].x, hubs[i].y);
        let opacity = 1 - distance / opts.linkRadius;
        
        if (opacity > 0) { 
            drawArea.lineWidth = 0.5;
            drawArea.strokeStyle = `rgba(${rgb[0]}, ${rgb[1]}, ${rgb[2]}, ${opacity})`;
            drawArea.beginPath();
            drawArea.moveTo(point1.x, point1.y);
            drawArea.lineTo(hubs[i].x, hubs[i].y);
            drawArea.closePath();
            drawArea.stroke();
        }
    }
}
```

### Conclusion

The result (using aspects of ES6) is very efficient, and I encourage you to experiment with the various options in the script.

Note that the animation can be brought to its knees by adding too many points and/or too great a link distance (which creates too many lines). It would also be nice to have the speed of the particles slow down as the viewport narrows: at small sizes, the particles appear to move faster in a more confined space.