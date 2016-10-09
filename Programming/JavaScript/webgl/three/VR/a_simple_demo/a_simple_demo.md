## A simple demo created by Ritter Liu [Back](./../VR.md)

This is a demo created by [Ritter Liu](https://github.com/ritterliu), and the source code has been opened here:

Firstly, we can see that the author has loaded some script files:

```html
<script type="text/javascript" src="js/three.min.js"></script>
<script type="text/javascript" src="js/StereoEffect.js"></script>
<script type="text/javascript" src="js/OrbitControls.js"></script>
<script type="text/javascript" src="js/DeviceOrientationControls.js"></script>
<script type="text/javascript" src="js/helvetiker_regular.typeface.js"></script>
```

Then here is the main code:

```js
var scene;
var camera;
var renderer;
var effect;
var element;
var controls;
var word = 'Ritter\'s VR World';

init();

```