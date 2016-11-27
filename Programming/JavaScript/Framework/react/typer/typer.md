## Typer [Back](./../react.md)

<p align="center">
    <img alt="rectangle loading" title="rectangle loading" src="./preview.png"></img>
</p>

<p align="center">
<strong>Rectangle Loading</strong>, just a reusable component for loading animation
</p>

### Property

Property|Optional|Default|Description
:------:|:-----:|:----------|:------
typeSpeed|true|50|the height of your loading area
rectNumber|false|5|the number of rectangles
rectDelay|false|0.12|the delay time of each retangles
rectColor|false|#000|the color of rectangles
isHide|false|false|to point out whether show the loading when rendering

typeSpeed: 100,
	typeBackSpeed: 25,
	typeDelay: 2000

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

### Demo

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="ENXXbo" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="ENXXbo" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/ENXXbo/">ENXXbo</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
