## Typer [Back](./../react.md)

<p align="center">
    <img src="./preview.png" alt="typer" title="typer" />
</p>

<p align="center">
<strong>Typer</strong>, a typing component for you to show contents
</p>

### Properties

Property|Optional|Default|Description
:------:|:-----:|:----------|:------
text|false||an array to store texts which you want to show
typeSpeed|true|100|the speed of typing, 100 means to type one character per 100ms
typeBackSpeed|true|25|the speed of typing back, 25 means to type back one character per 25ms
typeDelay|true|2000|the delay time of typing, 2000 means that the text will have hold to show for 2 seconds

### Usage

The whole code is contained in the following codepen demo, and what you need to do is to copy the code of JavaScript, and save it as a `jsx` file, which may need a loader to parse like Babel. Then, before the defined class `Typer`, just add a key word `export` so that you can import it elsewhere.

```js
export class Typer extends React.Component {
    /** ... */
}
```

Then, you can use it by importing the component like:

```js
import { Typer } from 'typer.jsx';

/** you can also use <Typer /> */
ReactDOM.render(
    <Typer text={
        [
            'text1',
            'text2'
        ]
    }></Typer>,
    document.querySelector('.container')
);
```

### Styles

What styles the component needs is as followed:

### Demo

<p>
<p data-height="252" data-theme-id="21735" data-slug-hash="LbjzYE" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="LbjzYE" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/LbjzYE/">LbjzYE</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
