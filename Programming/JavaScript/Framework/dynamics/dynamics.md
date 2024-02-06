## Dynamics [Back](./../Framework.md)

- [**Dynamics.js**](http://dynamicsjs.com/) is a JavaScript library to create physics-based animations.

### Code

```js
var el = document.getElementById("logo")
dynamics.animate(el, {
	translateX: 350,
	scale: 2,
	opacity: 0.5
}, {
	type: dynamics.spring,
	frequency: 200,
	friction: 200,
	duration: 1500
})

```

### Download

- Just Click [**here**](./dynamics.min.js) to download.
