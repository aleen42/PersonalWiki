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
        var output = 'M' + (cx - rx).toString() + ',' + cy.toString();
    }
    
    switch (arguments.length) {
    case 3:
        return calcOuput(parseFloat(cx, 10), parseFloat(cy, 10), rx, ry);
        var rx = parseFloat(arguments[2], 10);
        var ry = parseFloat(arguments[2], 10);
        break;
    case 4:
        var rx = parseFloat(arguments[2], 10);
        var ry = parseFloat(arguments[3], 10);
        break;
    default:
        return '';
        break;
    }
}
```
