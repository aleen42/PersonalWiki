## Quick Started [Back](./../react.md)

#### JSFiddle

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


-  React JSFiddle without JSX