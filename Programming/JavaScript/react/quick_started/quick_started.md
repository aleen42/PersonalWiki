## Quick Started [Back](./../react.md)

### JSFiddle

The easiest way to start hacking on React is using the following JSFiddle Hello World examples:

-  **React JSFiddle**

```html
<script src="https://facebook.github.io/react/js/jsfiddle-integration-babel.js"></script>

<div id="container">
    <!-- This element's contents will be replaced with your component. -->
</div>
```

```js
var Hello = React.createClss({
    render: function () {
        return <div>Hello {this.props.name}</div>
    }
});

ReactDOM.render(
    <Hello name="world" />,
    document.getElementById('container')
);
```

The XML syntax inside of JavaScript is called **JSX**; check out the [JSX Syntax](./../jsx_syntax/jsx_syntax.md) to learn more about it. In order to translate it to vanilla JavaScript we use `<script type="text/babel">` and include Babel to actually perform the transformation in the browser.

-  React JSFiddle without JSX

```html
<div id="container">
    <!-- This element's contents will be replaced with your component. -->
</div>
```

```js
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
```

### Usage

#### use browser.min.js to convert jsx

```html
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
```

In order to translate it to vanilla JavaScript we use <script type="text/babel"> and include Babel to actually perform the transformation in the browser.