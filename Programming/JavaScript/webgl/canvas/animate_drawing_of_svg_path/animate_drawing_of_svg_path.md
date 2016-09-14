## Animate a progressive drawing of SVG path [Back](./../canvas.md)

### all-SVG solution

Here is an all-SVG solution that involves progressively modifying the `stroke-dasharray` for the shape to draw a longer and longer 'dash' followed by an enormous(大量的) gap.

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/wzrLoA/?height=300&theme-id=21735&default-tab=js,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wzrLoA/'>wzrLoA</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

Relavant code:

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

