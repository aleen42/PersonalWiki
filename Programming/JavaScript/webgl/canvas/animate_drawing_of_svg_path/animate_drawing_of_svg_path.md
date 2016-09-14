## Animate a progressive drawing of SVG path [Back](./../canvas.md)

### all-SVG solution

Here is an all-SVG solution that involves progressively modifying the `stroke-dasharray` for the shape to draw a longer and longer 'dash' followed by an enormous(大量的) gap.

Relavant code:

```js
var distancePerPoint = 1;
var drawFPS = 60;

var orig = document.querySelector('path');
var length;
var timer;

function startDrawingPath() {
    length = 0;
    orig.style.stroke = '#f60';
    timer = setInterval(increaseLength, 1000 / drawFPS);
}

function increaseLength() {
    var pathLength = orig.getTotalLength();
    length += distancePerPoint;
    orig.style.strokeDasharray = [length,pathLength].join(' ');
    
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
