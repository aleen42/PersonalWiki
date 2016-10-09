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

function init() {
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(90, window.innerWidth / window.innerHeight, 0.001, 700);
    camera.position.set(0, 15, 0);
    
    /** initiate the camera */
    scene.add(camera);
    
    renderer = new THREE.WebGLRenderer();
    element = renderer.domElement;
    document.body.appendChild(renderer.domElement);
    
    effect = new THREE.StereoEffect(renderer);
    
    /** Handle Mouse Control */
    controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.target.set(
        camera.position.x + 0.01,
        camera.position.y,
        camera.position.z
    );
    window.addEventListener('deviceorientation', setDeviceOrientationControls, true);  
    
}

```