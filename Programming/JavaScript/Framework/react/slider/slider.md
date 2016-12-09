## Slider [Back](./../react.md)

<p align="center">
    <img src="./preview.png" alt="slider" title="slider" />
</p>

<p align="center">
<strong>Multi-level Navigation</strong>, a navigation component with funny animation.
</p>

### Property

Property|Optional|Default|Description
:------:|:-----:|:----------|:------
items|false||an object for defining items, which mainly have two parts: the above and the below.
curIndex|true|0|the first item by default



### Usage

The whole code is contained in the following codepen demo, and what you need to do is to copy the code of JavaScript, and save it as a `jsx` file, which may need a loader to parse like Babel. Then, before the defined class `Slider`, just add a key word `export` so that you can import it elsewhere.

```js
export class Slider extends React.Component {
    /** ... */
}
```

Then, you can use it by importing the component like:

```js
import { Slider } from 'slider.jsx';

/** you can also use <Navigation /> */
ReactDOM.render(
    <Slider items={items}></Slider>,
    document.querySelector('.container')
);
```

Pay more attention to the object `data`, which should be constructed like this:

```js
var data = {
	name: 'ALL',
	children: [
		{ name: 'item1', children: null },
		{ name: 'item2', children: [
			{ name: 'item12', children: null },
			{ name: 'item13', children: null }
		]},
		{ name: 'item3', children: [
			{ name: 'item4', children: null },
			{ name: 'item5', children: [
				{ name: 'item7', children: null },
				{ name: 'item8', children: null }
			]},
			{ name: 'item6', children: [
				{ name: 'item9', children: null }
			]},
			{ name: 'item10', children: [
				{ name: 'item11', children: null }
			]}
		]}
	]
};
```

As we can see, we should hold a `name` for each menu, and if menus have their own sub-menus, they can be constructed with a `children` object, which should be another array.

### Demo

<p>
<p data-height="374" data-theme-id="21735" data-slug-hash="MbodzW" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="MbodzW" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/MbodzW/">MbodzW</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
