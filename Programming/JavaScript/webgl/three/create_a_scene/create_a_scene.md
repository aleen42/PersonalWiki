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

To actually be able to display anything with Three.js, we need three things: A scene, a camera, and a renderer so we can render the scene with the camera.

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

`near` and `far` attributes means that objects further away from the camera than the value of far or closer than near won't be rendered.