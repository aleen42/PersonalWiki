## A simple demo created by Ritter Liu [Back](./../VR.md)

This is a demo created by [Ritter Liu](https://github.com/ritterliu), and the source code has been opened here:

### Source Code

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

    /** Create Light */
    var light = new THREE.PointLight( 0xffffff, 1.2, 0);
    light.position.set(0, 50, 0);
    scene.add(light);

    /** Create Floor */
    var floorTexture = THREE.ImageUtils.loadTexture('img/grass.jpg');
    floorTexture.wrapS = THREE.RepeatWrapping;
    floorTexture.wrapT = THREE.RepeatWrapping;
    floorTexture.repeat = new THREE.Vector2(50, 50);

    var floorMaterial = new THREE.MeshPhongMaterial({
        map: floorTexture
    });

    var floorGeometry = new THREE.PlaneBufferGeometry(1000, 1000);
    var floor = new THREE.Mesh(floorGeometry, floorMaterial);
    floor.rotation.x = -Math.PI / 2;
    scene.add(floor);

    /** Create Box */
    var geometry = new THREE.BoxGeometry(6, 6, 6);
    var material = new THREE.MeshNormalMaterial();
    var cube = new THREE.Mesh(geometry, material);
    cube.position.set(-15, 30, 10);
    scene.add(cube);

    /** Create Text */
    var textGeometry = new THREE.TextGeometry(word, {
        size: 5,
        height: 1
    });

    var text = new THREE.Mesh(textGeometry, new THREE.MeshBasicMaterial({
        color: 0xffffff
    }));

    text.position.set(15, 15, -25);
    text.rotation.set(0, 30, 0);
    scene.add(text);

    animate();
}

/** Our preferred controls via DeviceOrientation */
function setDeviceOrientationControls(e) {  
    controls = new THREE.DeviceOrientationControls(camera, true);
    controls.connect();
    controls.update();
    window.removeEventListener('deviceorientation', setDeviceOrientationControls, true);
}

function animate() {
    requestAnimationFrame(animate);

    var width = window.innerWidth;
    var height = window.innerHeight;

    camera.aspect = width / height;
    camera.updateProjectionMatrix();

    renderer.setSize(width, height);
    effect.setSize(width, height);

    camera.updateProjectionMatrix();

    controls.update();
    effect.render(scene, camera);
}
```

### Demo

<p>
<p data-height="483" data-theme-id="21735" data-slug-hash="PGRWGg" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="PGRWGg" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/PGRWGg/">PGRWGg</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
