## Dynamics [Back](./../Framework.md)

- [**Dynamics.js**](http://dynamicsjs.com/) is a JavaScript library to create physics-based animations.

###Code

```js
var svg = new Walkway({
	selector: '#path',
	duration: '2000',
	easing: function(t){
		return t * t;	//Easing Function
	}
});

svg.draw();

```
###Download
- Just Click [**here**](./dynamics.min.js) to download.
