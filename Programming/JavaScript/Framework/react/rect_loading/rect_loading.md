## Rectangle Loading [Back](./../react.md)

<p align="center">
    <img src="./preview.png" alt="rectangle loading" title="rectangle loading" />
</p>

<p align="center">
<strong>Rectangle Loading</strong>, just a reusable component for loading animation
</p>

### Properties

Property|Optional|Default|Description
:------:|:-----:|:----------|:------
height|true|50|the height of your loading area
rectNumber|true|5|the number of rectangles
rectDelay|true|0.12|the delay time of each retangles
rectColor|true|#000|the color of rectangles
isHide|true|false|to point out whether show the loading when rendering

### Usage

The whole code is contained in the following codepen demo, and what you need to do is to copy the code of JavaScript, and save it as a `jsx` file, which may need a loader to parse like Babel. Then, before the defined class `Loading`, just add a key word `export` so that you can import it elsewhere.

```js
export class Loading extends React.Component {
    /** ... */
}
```

Then, you can use it by importing the component like:

```js
import { Loading } from 'loading.jsx';

/** you can also use <Loading /> */
ReactDOM.render(
    <Loading></Loading>,
    document.querySelector('.container')
);
```

### Styles

What styles the component needs is as followed:

```css
.loading {
	font-size: 10px;
	text-align: center;
	position: absolute;
	top: 50%;
	left: 50%;

	-webkit-transition: all 0.5s;
	-o-transition: all 0.5s;
	transition: all 0.5s;

	box-sizing: border-box;
}

.loading > div:nth-child(1) {
	/** IE shoule be greater than 2px to render */
	margin-left: 2px;
}

.loading > div {
	height: 100%;
	width: 3px;
	/** IE shoule be greater than 2px to render */
	margin-right: 2px;
	display: inline-block;
	-webkit-animation: stretchdelay 1.2s infinite ease-in-out;
	animation: stretchdelay 1.2s infinite ease-in-out;
}

.loading__hide {
	display: none;
	/*opacity: 0;*/
}

@-webkit-keyframes stretchdelay {
	0%,
	40%,
	100% {
		-webkit-transform: scaleY(0.4)
	}
	20% {
		-webkit-transform: scaleY(1.0)
	}
}

@keyframes stretchdelay {
	0%,
	40%,
	100% {
		transform: scaleY(0.4);
		-webkit-transform: scaleY(0.4);
	}
	20% {
		transform: scaleY(1.0);
		-webkit-transform: scaleY(1.0);
	}
}
```

### Demo

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="ENXXbo" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="ENXXbo" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/ENXXbo/">ENXXbo</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
