## Animate a progressive drawing of SVG path [Back](./../canvas.md)

### all-SVG solution

Here is an all-SVG solution that involves progressively modifying the `stroke-dasharray` for the shape to draw a longer and longer 'dash' followed by an enormous(大量的) gap.

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/wzrLoA/?height=300&theme-id=21735&default-tab=js,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wzrLoA/'>wzrLoA</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

Relevant code:

```js
var distancePerPoint = 1;
var drawFPS = 60;

var orig = document.querySelector('path');
var length;
var timer;

function startDrawingPath() {
    length = 0;
    orig.style.stroke = '#000';
    timer = setInterval(increaseLength, 1000 / drawFPS);
}

function increaseLength() {
    var pathLength = orig.getTotalLength();
    length += distancePerPoint;
    orig.style.strokeDasharray = [length, pathLength].join(' ');
    
    if (length >= pathLength) {
        clearInterval(timer);
    }
}

function stopDrawingPath() {
    clearInterval(timer);
    orig.style.stroke = '';
    orig.style.strokeDasharray = '';
}

orig.addEventListener('mouseover', startDrawingPath, false);
orig.addEventListener('mouseout', stopDrawingPath, false);
```

### Canvas solution

In this case, you may choose to draw your path to an HTML5 canvas by sampling the SVG path periodically and drawing to the canvas. (Note that the SVG path does not need to be displayed for this to happen; you can build an SVG path element entirely in JavaScript and sample it):

Relevant code:

```js
function startDrawingPath() {
    points = [];
    timer = setInterval(buildPath, 1000 / drawFPS);
}

function redrawCanvas() {
    clearCanvas();
    ctx.beginPath();
    ctx.moveTo(points[0].x, points[0].y);
    
    for (var i = 1; i < points.length; i++) {
        ctx.lineTo(points[i].x, points[i].y);
    }
    
    ctx.stroke();
}

function clearCanvas(){
	ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
}

function stopDrawingPath(){
	clearInterval(timer);
	clearCanvas();
}

/** Assumes that 'orig' is an SVG path */
function buildPath() {
    var nextPoint = points.length * distancePerPoint;
    var pathLength = orig.getTotalLength();

    if (nextPoint <= pathLength){
        points.push(orig.getPointAtLength(nextPoint));
        redrawCanvas();
    } else {
        stopDrawingPath();
    }
}
```