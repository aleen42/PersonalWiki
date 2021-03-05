## Paginate [Back](./../react.md)

<p align="center">
    <img src="./preview.png" alt="paginate" title="paginate" />
</p>

<p align="center">
<strong>Paginate</strong>, a reusable component for pagination
</p>

### Introduction

To create a familiar and reusable component for pagination, `Paginate` has arisen. This component is mainly designed with common functions of pagination like stepping buttons and goto.

### Properties

Property|Optional|Default|Description
:------:|:-----:|:----------|:-------
total|false||how many items totally
callback|true||a callback function for grasping the current page and how many items for each page
per|true|10|to point out how many items for each page
defaultCur|true|1|which page is the current page initially
rage|true|2|the range of buttons for pages, shown around the current page
isStep|true|false|show the stepping button or not
isGoto|true|false|show the goto function or not

### Usage

The whole code is contained in the following codepen demo, and what you need to do is to copy the code of JavaScript, and save it as a `jsx` file, which may need a loader to parse like Babel. Then, before the defined class `Paginate`, just add a key word `export` so that you can import it elsewhere.

```js
export class Paginate extends React.Component {
    /** ... */
}
```

Then, you can use it by importing the component like:

```js
import { Paginate } from 'paginate.jsx';

/** you can also use <Paginate total={100} /> */
ReactDOM.render(
    <Paginate total={100} callback={
        function (cur, per) {
            {/** load data from the server */}
        }
    }></Paginate>,
    document.querySelector('.container')
);
```

### Styles

What styles the component needs is as followed:

```css
.paginate__item {
	list-style: none;
	display: inline-block;
	width: 30px;
	height: 30px;
	line-height: 30px;
	text-align: center;
	margin: 0 3px;
	border-radius: 5px;
	background-color: #f7f7f7;

	-webkit-user-select: none;
	-moz-user-select: none;
	-ms-user-select: none;
	-o-user-select: none;
	user-select: none;
}

.paginate__item--cursor {
	cursor: pointer;
}

.paginate__item--acitve {
	background-color: #a10000;
	color: #f7f7f7;
	
	-webkit-transition: all 0.3s;
    -o-transition: all 0.3s;
    transition: all 0.3s;
}

.paginate__step {
	width: 80px;
}

.paginate__step--cursor {
	cursor: pointer;
}

.paginate__number {
	outline: none;
	border-radius: 5px;
	width: 50px;
	height: 28px;
	line-height: 30px;
	padding: 0 3px;
	border: 1px solid #f7f7f7;
	text-align: center;
}

.paginate__goto {
	width: 80px;
}

.goto__wrapper {
	margin-left: 30px;
}
```

### Demo

<p>
<p data-height="574" data-theme-id="21735" data-slug-hash="BQROoW" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="BQROoW" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/BQROoW/">BQROoW</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
