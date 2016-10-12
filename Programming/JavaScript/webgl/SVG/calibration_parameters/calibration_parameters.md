## Calibration parameters for drawing a SVG file [Back](./../SVG.md)

Here what I wrote is all about recording the calculation of the calibration parameters when drawing a SVG file. Before that, you're supposed to know [how to draw](./../../canvas/drawing_a_svg/drawing_a_svg.md) a SVG file with canvas in JavaScript.

### Why need calibration parameters?

In the last step of drawing, we will find that there exists a problem. As shown below, there is a canvas area, which I call **a panel**.

![](./panel.png)

When I drop a SVG file into this panel, and start to draw it,

![](./example.svg)

I find that only data of points is not enough, because the data should always depend on some attributes of a SVG element, including `width`, `height`, and `viewBox`. Besides, what if I can drag and resize this SVG like below:

![](./resize_svg1.png)

![](./resize_svg2.png)

As I change the size of this SVG, data of points in paths won't change at the same time. What that means is that what I have drawn should be always in the same position.

Attributes like `width`, `height`, and `viewBox` of this SVG element will also affect data of points like dragging.

```html
<svg xmlns="http://www.w3.org/2000/svg" width="400" height="200" viewBox="0 0 200 200">
    <!-- paths -->
</svg>
```

That's why I need a calibration parameter for updating data of points in paths.

### Calculation

So I have defined some parameters: `dx`, `dy`, `ratioX`, and `ratioY`. Before calculation, there are some aspects needed to be explained.

- Group: a group for storing image and 4 respective circles, which is used for dragging to resize.
- Image: the image stored in a group

    ![](./group.png)


#### Positions

`dx` and `dy` represent the 

```js

```
