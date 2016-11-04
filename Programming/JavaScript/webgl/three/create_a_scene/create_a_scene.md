## Create a scene [Back](./../three.md)

### Before we start

Before you can use Three.js, you need somewhere to display it. Save the following HTML to a file on your computer, along with a copy of [three.js](http://threejs.org/build/three.js) in the js/ directory, and open it in your browser.

```html
<!DOCTYPE html>
<html>
	<head>
		<meta charset=utf-8>
		<title>My first Three.js app</title>
		<style>
			body { margin: 0; }
			canvas { width: 100%; height: 100% }
		</style>
	</head>
	<body>
		<script src="js/three.js"></script>
		<script>
			/** Our Javascript will go here. */
		</script>
	</body>
</html>
```

### Creating a scene

To actually be able to display anything with Three.js, we need three things: **A scene**, **a camera**, and **a renderer** so we can render the scene with the camera.

```js
var scene = new THREE.Scene();

var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);
```

- `PerspectiveCamera(fov, aspect, near, far)`
    - **fov**: Camera frustum vertical field of view.
    - **aspect**: Camera frustum aspect ratio.
    - **near**: Camera frustum near plane.
    - **far**: Camera frustum far plane.

`near` and `far` attributes means that objects further away from the camera than the value of **far** or **closer** than near won't be rendered.

- `WebGLRenderer.setSize(width, height, updateStyle)`
    - **width**: the width of the rendering region.
    - **height**: the height of the rendering region.
    - **updateStyle**: if keep the size with a lower resolution, pass `false`, which is `true` by default

### Creating a cube(立體)

```js
var geometry = new THREE.BoxGeometry(1, 1, 1);
var material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);

camera.position.z = 5;
```

`BoxGeometry` is an object that contains all the points (**vertices**) and fill (**faces**) of the cube, while `MeshBasicMaterial` is for coloring object in three.js. Finally, `Mesh` is an object that takes a **geometry**, and applies a **material** to it, which we then can insert to our scene, and move freely around.

### Rendering the scene we created before

```js
function render() {
    requestAnimationFrame(render);

    /** Animating */
    cube.rotate.x += 0.1;
    cube.rotate.y += 0.1;

    renderer.render(scene, camera);
}

render();
```

This will create a loop that causes the renderer to draw the scene 60 times per second (**60fps**). Using `requestAnimationFrame` has a number of advantages than using `setInterval`, and the most important one is that it pauses when the users navigates to another browser tab, which will save processing power and battery life.

### Demo

<p>
<p data-height="328" data-theme-id="21735" data-slug-hash="XKyKyV" data-default-tab="html,result" data-user="aleen42" data-embed-version="2" data-pen-title="XKyKyV" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/XKyKyV/">XKyKyV</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
