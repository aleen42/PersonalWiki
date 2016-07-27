## Package Management [Back](./../tooling_integration.md)

### CDN-hosted React

We provide CDN-hosted versions of React [on our download page](https://facebook.github.io/react/downloads.html). These pre-built files use the UMD module format. Dropping them in with a simple `<script>` tag will inject the `React` and `ReactDOM` globals into your environment. It should also work out-of-the-box in CommonJS and AMD environments.

### Using React from npm

You can also use React with a CommonJS module system like [browserify](http://browserify.org/) or [webpack](https://webpack.github.io/). Just use `react` and `react-dom` npm packages.

{%ace edit=false lang='jsx' %}
/** main.js */
var React = require('react');
var ReactDOM = require('react-dom');

ReactDOM.render(
    <h1>Hello, world!</h1>,
    document.getElementById('example')
);
{%endace%}

Configure babel with a `.babelrc` file:

{%ace edit=false lang='json' %}
{
    "presets": ["react"]
}
{%endace%}


