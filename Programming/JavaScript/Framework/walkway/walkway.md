## Walkway [Back](./../Framework.md)

**Walkway.js** is a light weight js framework for drawing svg.
- [**Example**](http://aleen42.github.io/example/Walkway/example.html)

### Code

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

### Download

- Just Click [**here**](./walkway.min.js) to download.
