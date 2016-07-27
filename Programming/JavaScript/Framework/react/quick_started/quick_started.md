## Quick Started [Back](./../react.md)

### JSFiddle

The easiest way to start hacking on React is using the following JSFiddle Hello World examples:

-  **React JSFiddle**

{%ace edit=false, lang='html', theme='tomorrow' %}
<script src="https://facebook.github.io/react/js/jsfiddle-integration-babel.js"></script>

<div id="container">
    <!-- This element's contents will be replaced with your component. -->
</div>
{%endace%}

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var Hello = React.createClass({
    render: function () {
        return <div>Hello {this.props.name}</div>
    }
});

ReactDOM.render(
    <Hello name="world" />,
    document.getElementById('container')
);
{%endace%}

The XML syntax inside of JavaScript is called **JSX**; check out the [JSX Syntax](./../jsx_syntax/jsx_syntax.md) to learn more about it. In order to translate it to vanilla JavaScript we use `<script type="text/babel">` and include Babel to actually perform the transformation in the browser.

-  React JSFiddle without JSX

{%ace edit=false, lang='html', theme='tomorrow' %}
<div id="container">
    <!-- This element's contents will be replaced with your component. -->
</div>
{%endace%}

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var Hello = React.createClass({
    displayName: 'Hello',
    render: function () {
        return React.createElement('div', null, 'Hello ', this.props.name);
    }
});

ReactDOM.render(
    React.createElement(Hello, {name: 'world'}),
    document.getElementById('container')
);
{%endace%}

### Usage

#### use browser.min.js to transform jsx

{%ace edit=false, lang='html', theme='tomorrow' %}
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello React!</title>
    <script src="build/react.js" charset="utf-8"></script>
    <script src="build/react-dom.js" charset="utf-8"></script>
    <script src="build/browser.min.js" charset="utf-8"></script>
</head>
<body>
    <div id="example"></div>
    <script type="text/babel">
        ReactDOM.render(
            <h1>Hello World</h1>,
            document.getElementById('example')
        );
    </script>
</body>
</html>
{%endace%}

In order to translate it to vanilla JavaScript we use `<script type="text/babel">` and include **Babel** to actually perform the transformation in the browser.

Or we can seperate a file to write jsx:

{%ace edit=false, lang='html', theme='tomorrow' %}
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello React!</title>
    <script src="build/react.js" charset="utf-8"></script>
    <script src="build/react-dom.js" charset="utf-8"></script>
    <script src="build/browser.min.js" charset="utf-8"></script>
    <script src="src/helloworld.js" type="text/babel"></script>
</head>
<body>
    <div id="example"></div>
</body>
</html>
{%endace%}

{%ace edit=false, lang='jsx', theme='tomorrow' %}
ReactDOM.render(
    <h1>Hello World</h1>,
    document.getElementById('example')
);
{%endace%}

*Notice that: some browsers like Chrome can't load this file unless it's through a **HTTP** method.*

#### use npm to build a vanilla JavaScript file

Install the tool first:

{%ace edit=false, lang='sh', theme='tomorrow' %}
$ npm install -g react-tools
{%endace%}

Transform jsx with the following command, `--watch` is used for keeping watching transformation:

{%ace edit=false, lang='sh', theme='tomorrow' %}
$ jsx --watch src/ build/
{%endace%}

The comand will see jsx files in the directory `src/` and build a vanilla JavaScript file into the directory `build/`, and then we can just import this vanilla JavaScript file.

{%ace edit=false, lang='html', theme='tomorrow' %}
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello React!</title>
    <script src="build/react.js" charset="utf-8"></script>
    <script src="build/react-dom.js" charset="utf-8"></script>
    <script src="build/helloworld.js" type="text/javascript"></script>
</head>
<body>
    <div id="example"></div>
</body>
</html>
{%endace%}