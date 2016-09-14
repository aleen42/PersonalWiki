## Animated Glowing Line Drawing [Back](./../canvas.md)

Before what we talk, we can see a screen shot of it:

![](./canvas_glow.png)

A few random parameters are first set up to determine the color of the line, as well as it's start and end points, and the control points, then a window interval just calls a function which draws a series of lines in decreasing thicknesses in the highlight color, followed by one thin white line on top.

```html
<canvas id="glow" width="1200" height="700">
    Your browser does not support HTML5 Canvas.
</canvas>
```

```js
/**
 * update the position and direction of movement for an end point on the line or one of the control points
 */
function get_bounce_coord(coord_array) {
	coord_array[0] += step * coord_array[1];

	if( (coord_array[0] > (canv.height - 2 * step) && coord_array[2] === 'y') 
	    || (coord_array[0] > (canv.width - 2 * step) && coord_array[2] === 'x')
		|| coord_array[0] < 2 * step)	{
		coord_array[1] *= -1;
	}
}

function draw_line() {
	/** paint over the existing canvas */
	context.fillStyle = '#000';
	context.fillRect(0, 0, canv.width, canv.height);

	/** get the new coords based on each ones current trajectory */
	get_bounce_coord(x1);
	get_bounce_coord(y1);
	get_bounce_coord(x2);
	get_bounce_coord(y2);

	get_bounce_coord(cx1);
	get_bounce_coord(cy1);
	get_bounce_coord(cx2);
	get_bounce_coord(cy2);

	for (i = 5; i >= 0; i--) {
		context.beginPath();

		/** draw each line, the last line in each is always white */
		context.lineWidth = (i + 1) * 4 - 2;
		
		if (i === 0) {
			context.strokeStyle = '#fff';
		} else {
			context.strokeStyle = 'rgba(' + highlight[0] + ',' + highlight[1] + ',' + highlight[2] + ',0.2)';
		}
		
		context.moveTo(x1[0], y1[0]);
		context.bezierCurveTo(cx1[0],cy1[0],cx2[0],cy2[0],x2[0],y2[0]);
		context.stroke();
		context.closePath();
	}
}

/**
 * get a random x or y coordinate
 */
function random_coord(type) {
	dimension = (type === 'x') ? canv.width : canv.height;
	return Math.random() * (dimension - 2 * step) + step;
}

(function() {
    canv = document.getElementById('glow');
    
    if (!canv || !canv.getContext) {
        return;
    }
    
    context = canv.getContext('2d');
    
    /** the glow color */
    highlight = new Array(Math.round(Math.random() * 255), Math.round(Math.random() * 255), Math.round(Math.random() * 255));
	step = 7;   /** amount each movement of coord is in canvas pixels */
	
	/** start and end coordinates for the line */
	x1 = new Array(random_coord('x'), -1, 'x');
	y1 = new Array(random_coord('y'), 1, 'y');
	x2 = new Array(random_coord('x'), -1.5, 'x');
	y2 = new Array(random_coord('y'), -1.5, 'y');
	
	/** coordinates for the control points of the bezier curve */
	cx1 = new Array(random_coord('x'), 1, 'x');
	cy1 = new Array(random_coord('y'), -1, 'y');
	cx2 = new Array(random_coord('x'), -1, 'x');
	cy2 = new Array(random_coord('y'), 1, 'y');
	
	timer = window.setInterval(draw_line, 30);
})();
```
