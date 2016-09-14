## Animated Glowing Line Drawing [Back](./../canvas.md)

Before what we talk, we can see a screen shot of it:

![](./canvas_glow.png)

A few random parameters are first set up to determine the color of the line, as well as it's start and end points, and the control points, then a window interval just calls a function which draws a series of lines in decreasing thicknesses in the highlight color, followed by one thin white line on top.

```html
<canvas id="glow" width="1200" height="700">
    Your browser does not support HTML5 Canvas.
</canvas>
```
