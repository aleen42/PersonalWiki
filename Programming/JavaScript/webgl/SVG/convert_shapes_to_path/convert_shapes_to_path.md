## Convert all shapes/primitives into path elements of SVG [Back](./../SVG.md)

In SVG, shapes/primitives are defined with different elements like `circle`, `ellipse`, `line`, `polygon`, `polyline`, `rect`, and so on. If I want to draw them with [this tutorial](./../../canvas/drawing_a_svg/drawing_a_svg.md), I need to convert all of them into a same element, `path`. How? This is the purpose of this article.

### Circles & Ellipses

`circle` and `ellipse` elements are similar to each other with both attributes as below:

**Circles**|**Ellipses**
:-----:|:------:
CX|CX
CY|CY

Differences between them are the attributes describing radius.

**Circles**|**Ellipses**
:-----:|:------:
R|RX
|RY

Therefore, the calculation of `d` value in a `path` element can be easily completed like this:

```js
function convertCE(cx, cy) {
    function calcOuput(cx, cy, rx, ry) {
        if (cx < 0 || cy < 0 || rx <= 0 || ry <= 0) {
            return '';
        }
    
        var output = 'M' + (cx - rx).toString() + ',' + cy.toString();
        output += 'a' + rx.toString() + ',' + ry.toString() + ' 0 1,0 ' + (2 * rx).toString() + ',0';
		output += 'a' + rx.toString() + ',' + ry.toString() + ' 0 1,0'  + (-2 * rx).toString() + ',0';
		
		return output;
    }
    
    switch (arguments.length) {
    case 3:
        return calcOuput(parseFloat(cx, 10), parseFloat(cy, 10), parseFloat(arguments[2], 10), parseFloat(arguments[2], 10));
    case 4:
        return calcOuput(parseFloat(cx, 10), parseFloat(cy, 10), parseFloat(arguments[2], 10), parseFloat(arguments[3], 10));
        break;
    default:
        return '';
    }
}
```

### Polylines & Polycircles

For these both elements, what you should do is to extract out the attribute `points`. and recompose them into a special format for `d` value of path elements.

```js
/** pass the value of the attribute `points` into this function */
function convertPoly(points, types) {
    types = types || 'polyline';

    var pointsArr = points
        /** clear redundant characters */
        .split(' 	').join('')
        .trim()
        .split(/\s+|,/);
    var x0 = pointsArr.shift();
    var y0 = pointsArr.shift();
    
    var output = 'M' + x0 + ',' + y0 + 'L' + pointsArr.join(' ');
    
    return types === 'polygon' ? output + 'z' : output;
}
```

### Lines

Generally, `line` elements will have some attributes defined for positioning start and end points of a line: `x1`, `y1`, `x2`, and `y2`.

Easily can we calculate like this:

```js
function convertLine(x1, y1, x2, y2) {
    if (parseFloat(x1, 10) < 0 || parseFloat(y1, 10) < 0 || parseFloat(x2, 10) < 0 || parseFloat(y2, 10) < 0) {
        return '';
    }
    
    return 'M' + x1 + ',' + y1 + 'L' + x2 + ',' + y2;
}
```

### Rectangles

Rectangles will also have some attributes defined for positioning itself and deciding how big it's: `x`, `y`, `width`, and `height`.

```js
function convertRectangles(x, y, width, height) {
    var x = parseFloat(x, 10);
    var y = parseFloat(y, 10);
    var width = parseFloat(width, 10);
    var height = parseFloat(height, 10);

    if (x < 0 || y < 0 || width < 0 || height < 0) {
        return '';
    }
    
    return 'M' + x + ',' + y + 'L' + (x + width) + ',' + y + ' ' + (x + width) + ',' + (y + height) + ' ' + x + ',' + (y + height) + 'z';
}
```
