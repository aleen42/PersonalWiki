## \[原創\] Kaleidoscope [Back](./../post.md)

<p align="center"><img src="./preview.png" alt="kaleidoscope" /></p>
<p align="center"><strong>Figure 1</strong> A simple preview of kaleidoscopes</p>

In Chinese, we will name kaleidoscopes as "萬花筒", which is a toy showing colourful shapes of thousands of flowers. Today, inspired by the project, [spring loaders](https://github.com/claudiocalautti/spring-loaders), I have tried to create a similar component with CSS and SVG, rather than Canvas. As Figure 1 shown, that's my **kaleidoscope**.

### 1. Introduction

Without reading the article, I have just created it through several processes. How to create, how to create regular polygons, and how to make it reusable for all kinds of regular polygons.

#### 1.1 How to create?

At the start, I have utilized the feature of `div`, which is an HTML element with a shape of rectangles. By setting the same value for the property `width` and `height` of these elements, I can easily generate a square like the first item from the left side in Figure 1.

Then, to simulate such rotating animation, I would like to use the `transform` and `transform-origin` property to implement it, rather than use Canvas, as Canvas is something complicated, which has always been confusing me.

```css
.item {
    transform: scale(0.5) rotateZ(45deg);
    transform-origin: center;
    
    /** other browsers */
    -webkit-transform: scale(0.5) rotateZ(45deg);
    -webkit-transform-origin: center;
    
    -moz-transform: scale(0.5) rotateZ(45deg);
    -moz-transform-origin: center;
    
    -ms-transform: scale(0.5) rotateZ(45deg);
    -ms-transform-origin: center;
    
    -o-transform: scale(0.5) rotateZ(45deg);
    -o-transform-origin: center;
}
```

The code snippet above has shown us how to use such two properties to animate our elements. With setting `scale(0.5)` and `rotateZ(45deg)`, the element will be scaled by half, and rotate 45 degrees clockwise.

If using JavaScript to change this value dynamically, we can code like this:

```js
/** theta is the rotating degree */
const theta = 45; 
const scaleRatio = 0.5;
const target = document.querySelector('.item');

target.style.transformOrigin = 'center';
target.style.transform = 'scale(' + scaleRatio + ') rotateZ(' + theta + 'deg)';

/** other browsers */
target.style.WebkitTransformOrigin = 'center';
target.style.WebkitTransform = 'scale(' + scaleRatio + ') rotateZ(' + theta + 'deg)';

target.style.MozTransformOrigin = 'center';
target.style.MozTransform = 'scale(' + scaleRatio + ') rotateZ(' + theta + 'deg)';

target.style.MsTransformOrigin = 'center';
target.style.MsTransform = 'scale(' + scaleRatio + ') rotateZ(' + theta + 'deg)';

target.style.OTransformOrigin = 'center';
target.style.OTransform = 'scale(' + scaleRatio + ') rotateZ(' + theta + 'deg)';
```

<p align="center">
  <svg xmlns:svg="http://www.w3.org/2000/svg"
     xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="400px"
     height="300px"
     viewBox="0 0 400 300" enable-background="new 0 0 400 300" xml:space="preserve">
    <g fill="var(--color-text-primary, #24292f)">
      <rect id="svg_2" x="97.603" y="60.878" fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" width="228.13" height="228.13"/>
      <rect id="svg_3" x="121.863" y="83.727" transform="matrix(-0.9552 -0.2961 0.2961 -0.9552 364.3225 404.4773)"
            fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" width="181.851" height="181.851"/>
      <rect id="svg_4" x="97.603" y="60.878" fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" width="14.382" height="14.382"/>
      <foreignObject transform="matrix(1 0 0 1 80.3333 138.8354)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">x</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 256.217 75.2599)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">x</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 80.3334 256.3285)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">y</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 128.9274 75.2599)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">y</div>
      </foreignObject>
      <path id="svg_9" fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" d="M97.603,175.364c0,0,13.108-11.402,16.473,10.62"/>
      <foreignObject transform="matrix(1 0 0 1 105.84 138.8354)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">θ</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 154.4583 107.6511)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">a(x+y)</div>
      </foreignObject>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 2</strong> The relationship between sita and scale</p>

Then as the Figure 2 shown, how to calculate a proper value of `scaleRatio` (***a***) with `theta` (***θ***) as the variable, in order that vertexes of the item can stay on each side of another square? We may just have to solve the following equation:

```math:fontSize=16
\begin{cases}
    y = x\tan\theta \\
    x^2 + y^2 = [a(x + y)] ^ 2
\end{cases}
```

After calculating, we can easily get that:

```math
a = \frac {\sqrt{1 + \tan ^ 2\theta}} {1 + \tan \theta}
```

As we can see, the value of `scale` can be calculated with `sita` as the variable.

<p align="center">
  <svg width="400" height="300" xmlns="http://www.w3.org/2000/svg" xmlns:svg="http://www.w3.org/2000/svg">
    <g fill="var(--color-text-primary, #24292f)" id="svg_1">
      <rect fill="none" height="228.129842" id="svg_2" stroke="var(--color-text-primary, #24292f)"
            stroke-miterlimit="10" stroke-width="2" width="228.129842" x="97.603388" y="60.877886"/>
      <rect fill="none" height="110" id="svg_3" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10"
            transform="matrix(1.57906 0.489487 -0.489487 1.57906 -128.509 -193.599)" width="110" x="207.551271"
            y="97.006531"/>
      <rect fill="none" height="110" id="svg_14" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10"
            transform="rotate(29.0485 211.668 174.943) matrix(1.14978 0.356417 -0.356417 1.14978 -38.2472 -93.6205)"
            width="110" x="209.361539" y="96.628791"/>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 3</strong> Multi-nested squares</p>

Besides, we should also solve the case when a square is embedded with another square, while another square is embedded with another square (Figure 3). To work around this complicated problem of calculation, I have used relative motions instead. For example, I will create this three squares like this:

```html
<div class="rect rect1">
    <div class="rect rect2">
        <div class="rect rect3"></div>
    </div>
</div>
```

Then rotate the second square and the third one with scaling at the same time:

```css
.rect2 {
    transform: scale(0.8155975296668455) rotateZ(15deg);
    transform-origin: center;
}

.rect3 {
    transform: scale(0.8155975296668455) rotateZ(15deg);
    transform-origin: center;
}
```

Then, that's done! Easy right? The following code is implemented for this square item:

```js
/** the difference of degree in each duration */
const stepT = 0.5;

/** the time (ms) to update the sita value */
const dur = 10;

/** the number of multi-nested squares */
const num = 6;

/** the current value of theta */
var theta = 0;

/** direction to change */
var dir = 1;

/** append multi-nested squares */
for (var i = 0; i < num; i++) {
   var div = document.createElement('div');
   div.className = 'rect rect' + (i + 1);
   document.querySelector('.rect' + i).appendChild(div);
}

/** start to animate */
setInterval(function () {
   theta += stepT * dir;

   if (Math.abs(theta) > 90) {
      dir *= -1;
      theta = (Math.abs(theta) - 90) * dir;
   }

    /** calculate the scaleRatio */
   const tan = parseFloat(Math.tan(Math.abs(theta) * Math.PI / 180).toFixed(2));
   const scaleRatio = Math.sqrt(1 + tan * tan) / (1 + tan);

   for (var i = 0; i < num; i++) {
      document.querySelector('.rect' + (i + 1)).style.transform = 'scale(' + scaleRatio + ') rotate(' + theta + 'deg)';
   }
}, dur);
```

#### 1.2 How to create regular polygons?

From the preceding section, we can see that we have just implemented squares, but I wonder how to use them in other regular polygons like equilateral triangles or even pentagons. Before discussing the problem, we should create such regular polygons at first.

Certainly, we can easily generate squares by setting the width and the height with the same value, but what if generating other regular polygons? **SVG** is my choice.

<p align="center">
  <svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="568.5px" height="380.5px" viewBox="0 0 568.5 380.5" enable-background="new 0 0 568.5 380.5" xml:space="preserve">
    <g fill="var(--color-text-primary, #24292f)">
      <g>
        <g>
          <g>
            <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" x1="65.5" y1="14" x2="341.148" y2="14"/>
            <g>
              <polygon points="338.23,23.973 355.5,14 338.23,4.027" fill="var(--color-book-border,rgba(13,17,23,.2))"/>
            </g>
          </g>
        </g>
        <g>
          <g>
            <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" x1="65.5" y1="14" x2="65.5" y2="289.648"/>
            <g>
              <polygon points="55.527,286.73 65.5,304 75.473,286.73" fill="var(--color-book-border,rgba(13,17,23,.2))"/>
            </g>
          </g>
        </g>
      </g>
      <polygon xmlns="http://www.w3.org/2000/svg" fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" points="170.669,189.502 417.872,96.5 341.896,307.821 "/>
      <foreignObject transform="matrix(1 0 0 1 110.8579 169.5138)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">(x<sub>0</sub>, y<sub>0</sub>)</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 423.8579 81.5139)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">(x<sub>1</sub>, y<sub>1</sub>)</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 334.8579 322.5138)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">(x<sub>2</sub>, y<sub>2</sub>)</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 349.8333 23.5)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">x</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 77.1668 295.5)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">y</div>
      </foreignObject>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 4</strong> A triangle</p>

In SVG, we can easily create a polygon by using `polygon` tags, with setting the attribute `points` to set up each vertex. For instance, the triangle in the Figure 4 can be created like this:

```html
<svg>
    <polygon stroke="#000" fill="none" points="x0,y0 x1,y1 x2,y2"></polygon>
</svg>
```

Utilizing this feature, what we should do to generate regular polygons is just to solve the positions of each vertex.

<p align="center">
  <svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" width="400px" height="300px">
    <g fill="var(--color-text-primary, #24292f)">
      <g>
        <circle fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" stroke-dasharray="4.0094,4.0094" cx="199.5" cy="150" r="134"/>
      </g>
      <polygon fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" points="83.599,218.478 199.5,17.732    315.401,218.478 "/>
      <circle cx="199.5" cy="147.5" r="2.5"/>
      <g>
        <g>
          <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" stroke-dasharray="4.057,4.057" x1="199.5" y1="141.443" x2="199.5" y2="21.761"/>
        </g>
      </g>
      <foreignObject transform="matrix(1 0 0 1 209.5 92.5)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">r</div>
      </foreignObject>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 5</strong> An equilateral triangles within a specific circle</p>

Besides, can such polygons be generated within a circle with a specific radius (Figure 5)? The answer is yes.

<p align="center">
  <svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="400px" height="317.5px" viewBox="0 0 400 317.5" enable-background="new 0 0 400 317.5" xml:space="preserve">
    <g fill="var(--color-text-primary, #24292f)">
      <g>
        <g>
          <g>
              <circle fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" stroke-dasharray="4.0094,4.0094" cx="199.5" cy="148" r="134"/>
          </g>
        </g>
        <circle stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-miterlimit="10" cx="199.5" cy="145.5" r="2.5"/>
        <g>
          <g>
            <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" x1="65.5" y1="14" x2="341.148" y2="14"/>
            <g>
              <polygon points="338.23,23.973 355.5,14 338.23,4.027" fill="var(--color-book-border,rgba(13,17,23,.2))"/>
            </g>
          </g>
        </g>
        <g>
          <g>
            <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" x1="65.5" y1="14" x2="65.5" y2="289.648"/>
            <g>
              <polygon points="55.527,286.73 65.5,304 75.473,286.73" fill="var(--color-book-border,rgba(13,17,23,.2))"/>
            </g>
          </g>
        </g>
      </g>
      <line fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" x1="199.5" y1="145.5" x2="199.5" y2="14"/>
      <line fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" x1="199.5" y1="145.5" x2="118.701" y2="41.097"/>
      <foreignObject transform="matrix(1 0 0 1 210.5 65.1667)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">r</div>
      </foreignObject>
      <line fill="none" stroke="var(--color-book-border,rgba(13,17,23,.2))" stroke-width="2" stroke-miterlimit="10" stroke-dasharray="4" x1="118.701" y1="41.097" x2="199.5" y2="41.097"/>
      <path fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" d="M200,93.299c0,0-24.52-22.652-30.562,13.357"/>
      <foreignObject transform="matrix(1 0 0 1 169.4379 68.7498)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">θ</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 349.8333 23.5)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">x</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 77.1668 295.5)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">y</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 77.5 20.25)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">(x<sub>0</sub>, y<sub>0</sub>)</div>
      </foreignObject>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 6</strong> The specific coordinates</p>

Before calculating, to make it more clear, I have drawn Figure 6 which has shown coordinates for us, and in which the relationship between ***θ*** and ***(x,y)*** is what we should solve later.

Then, here is the equation:

```math:fontSize=16
\begin{cases}
    x_0 = r(1 - \sin \theta) \\
    y_0 = r(1 - \cos \theta)
\end{cases}
```

After that, just create regular polygons with ***θ***:

```html
<svg class="svg__container"></svg>
```

```js
function createPolygon(obj, sides, startDeg) {
    /** the degree of the start position */
   startDeg = startDeg || 0;
   
   /** generate group to embed other group */
   var group = document.createElementNS('http://www.w3.org/2000/svg', 'g');
   
   /** the polygon you want to create */
   var polygon = document.createElementNS('http://www.w3.org/2000/svg', 'polygon');

    /** an array for storing points of this regular polygon */
   var pos = [];
   
   /** the radius of the given circle */
   const radius = document.querySelector('.svg__container').clientWidth / 2;

   for (var i = 0; i < sides; i++) {
      const deg = 360 / sides * i + startDeg;
      const x = radius * (1 - Math.sin(deg * Math.PI / 180));
      const y = radius * (1 - Math.cos(deg * Math.PI / 180));

      pos.push(x + ',' + y);
   }

   polygon.setAttribute('points', pos.join(' '));
   group.appendChild(polygon);
   obj.appendChild(group);
   
   /** set up the origin position of your transformation */
   group.style.transformOrigin = radius + 'px ' + radius + 'px';
   
   /** returns the group so that we can create multi nested elements recursively */
   return group;
}

/** equilateral triangles */
const sides = 3;

/** to create 6 nested triangles */
const num = 6;

var parent = document.querySelectorAll('.svg__container')[0];

for (var i = 0; i < num; i++) {
   parent = createPolygon(parent, sides, 45);
   parent.setAttribute('class', 'polygon polygon' + (i + 1));
}
```

#### 1.3 How to make it reusable?

Now we can generate any side of regular polygons (the number of sides should be more than 3), it's time to solve the problem mentioned above? To make it reusable.

<p align="center">
  <svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="400px" height="300px" viewBox="0 0 400 300" enable-background="new 0 0 400 300" xml:space="preserve">
    <g id="svg_1" fill="var(--color-text-primary, #24292f)">
      <foreignObject transform="matrix(1 0 0 1 152.3333 66.8354)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">x</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 235.3334 71.3285)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">y</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 159.84 121.7556)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">θ</div>
      </foreignObject>
      <foreignObject transform="matrix(1 0 0 1 167.4583 152.6511)" width="88" height="24" style="text-align: left;">
        <div xmlns="http://www.w3.org/1999/xhtml" style="line-height: 19px">a(x+y)</div>
      </foreignObject>
      <polygon fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" points="75.87,249.5 200,34.5 324.13,249.5  "/>
      <polygon fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" points="129.265,159.24 250.497,126.756       218.013,247.987  "/>
      <path fill="none" stroke="var(--color-text-primary, #24292f)" stroke-width="2" stroke-miterlimit="10" d="M140.092,138.264c0,0,12.075,0.353,12.242,14.794"/>
    </g>
  </svg>
</p>
<p align="center"><strong>Figure 7</strong> The case of equilateral triangles</p>

Firstly, we should solve the case in which the number of sides is 3 (Figure 7). Based on the Law of Sine, it's easily to get the following equation:

```math
\frac x {\sin(\frac {2 \pi} 3 - \theta)} = \frac y {\sin \theta} = \frac {a (x + y)} {\sin \frac \pi 3}
```

Then solve it:

```math
a = \frac {\sin \frac \pi 3} {\sin \theta + \sin (\frac {2 \pi} 3 - \theta)}
```

What if the number of sides is 4, 5, 6, etc.? You may find that all of them should obey the following rule, where ***n*** stands for the number of sides:

```math
a = \frac {\sin \frac {(n - 2) \pi} n} {\sin \theta + \sin (\frac {2 \pi} n - \theta)}\text{ }\text{ }\text{ }\text{ }\text{ }(n \geqslant 3)
```

Then, just complete it with JavaScript:

```js
const sides = 5;
var parent = document.querySelectorAll('.svg__container')[1];

const stepT = 0.8;
const dur = 10;
const num = 7;

var theta = 0;
var dir = 1;

/** append multi-nested polygons */
for (var i = 0; i < num; i++) {
   parent = createPolygon(parent, sides);
   parent.setAttribute('class', 'polygon polygon' + (i + 1));
}

/** start to animate */
setInterval(function () {
   theta += stepT * dir;
   
   const innerCornerDeg = Math.round(360 / sides);
   
   if (Math.abs(theta) > innerCornerDeg) {
      dir *= -1;
      theta = (Math.abs(theta) - innerCornerDeg) * dir;
   }

   const thetaValue = Math.abs(theta) * Math.PI / 180;
   const scaleRatio = Math.sin((180 - innerCornerDeg) * Math.PI / 180) / (Math.sin(thetaValue) + Math.sin(innerCornerDeg * Math.PI / 180 - thetaValue));

   for (var i = 1; i < num; i++) {
      document.querySelector('.polygon' + (i + 1)).style.transform = 'scale(' + scaleRatio + ') rotate(' + theta + 'deg)';
   }
}, dur);
```

If you want to use it in **React** as a component, you can check the POC [**here**](http://codepen.io/aleen42/pen/JbmBjK).

### 2. Demo

<p>
<p data-height="568" data-theme-id="21735" data-slug-hash="mOzbWW" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="mOzbWW" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/mOzbWW/">mOzbWW</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
