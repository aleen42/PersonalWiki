## Package Management [Back](./../tooling_integration.md)

### CDN-hosted React

We provide CDN-hosted versions of React [on our download page](https://facebook.github.io/react/downloads.html). These pre-built files use the UMD module format. Dropping them in with a simple `<script>` tag will inject the `React` and `ReactDOM` globals into your environment. It should also work out-of-the-box in CommonJS and AMD environments.

### Using React from npm

You can also use React with a CommonJS module system like [browserify](http://browserify.org/) or [webpack](https://webpack.github.io/). Just use `react` and `react-dom` npm packages.

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** main.js */
var React = require('react');
var ReactDOM = require('react-dom');

ReactDOM.render(
    <h1>Hello, world!</h1>,
    document.getElementById('example')
);
{%endace%}

Configure babel with a `.babelrc` file:

{%ace edit=false, lang='json', theme='tomorrow' %}
{
    "presets": ["react"]
}
{%endace%}

> Note:

> If you are using ES2015, you will want to also use the `babel-preset-es2015` package.

To install React DOM and build your bundle with browserify:

{%ace edit=false, lang='sh', theme='tomorrow' %}
$ npm install --save react react-dom babelify babel-preset-react
$ browserify -t [ babelify ] main.js -o bundle.js
{%endace%}

To install React DOM and build your bundle with webpack:

{%ace edit=false, lang='sh', theme='tomorrow' %}
$ npm install --save react react-dom babel-preset-react babel-loader babel-core
$ webpack main.js bundle.js --module-bind 'js=babel-loader'
{%endace%}

**Notice that**: by default, React will be in development mode, which is slower, and not advised for production. To use React in production mode, set the environment variable `NODE_ENV` to `production` (using envify or webpack's DefinePlugin). For example:

{%ace edit=false, lang='javascript', theme='tomorrow' %}
new webpack.DefinePlugin({
    "process.env": {
        NODE_ENV: JSON.stringify("production")
    }
});
{%endace%}

### Using React from Bower

Bower is a package manager optimized for the front-end development. If multiple packages depend on a package - jQuery for example - Bower will download jQuery just once. This is known as a flat dependency graph and it helps reduce page load.

If you'd like to use bower, it's as easy as:

{%ace edit=false, lang='sh', theme='tomorrow' %}
$ bower install --save react
{%endace%}

{%ace edit=false, lang='html', theme='tomorrow' %}
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
        <title>Hello React!</title>
        <script src="bower_components/react/react.js"></script>
        <script src="bower_components/react/react-dom.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/babel-core/5.8.34/browser.min.js"></script>
    </head>
    <body>
        <div id="example"></div>
        <script type="text/babel">
        ReactDOM.render(
            <h1>Hello, world!</h1>,
            document.getElementById('example')
        );
        </script>
    </body>
</html>
{%endace%}
