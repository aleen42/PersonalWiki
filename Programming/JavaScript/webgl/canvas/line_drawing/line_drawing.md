## Animated Glowing Line Drawing [Back](./../canvas.md)

Before what we talk, we can see a screen shot of it:

![](./canvas_glow.png)

A few random parameters are first set up to determine the colour of the line, as well as it's start and end points, and the control points (it has two because it's a Bezier), then a window interval just calls a function which draws a series of lines in decreasing thicknesses in the highlight colour, followed by one thin white line on top.
