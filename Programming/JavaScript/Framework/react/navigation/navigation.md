## Multi-level Navigation [Back](./../react.md)

<p align="center">
    <img src="./preview.png" width="100%" alt="multi-level navigation" title="multi-level navigation" />
</p>

<p align="center">
<strong>Multi-level Navigation</strong>, a navigation component with funny animation.
</p>

### Property

Property|Optional|Default|Description
:------:|:-----:|:----------|:------
data|false||an object for defining the structure of your navigation, which structure will be explained later.


### Usage

The whole code is contained in the following codepen demo, and what you need to do is to copy the code of JavaScript, and save it as a `jsx` file, which may need a loader to parse like Babel. Then, before the defined class `Navigation`, just add a key word `export` so that you can import it elsewhere.

```js
export class Navigation extends React.Component {
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

### Demo

<p>
<p data-height="252" data-theme-id="21735" data-slug-hash="LbjzYE" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="LbjzYE" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/LbjzYE/">LbjzYE</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
