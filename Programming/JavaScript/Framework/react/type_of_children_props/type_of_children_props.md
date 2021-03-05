## Type of the Children props [Back](./../react.md)

Usually, a component's children (`this.props.children`) is an array of components:

```jsx
var GenericWrapper = React.createClass({
    componentDidMount: function() {
        console.log(Array.isArray(this.props.children));    /** => true */
    },

    render: function() {
        return <div />;
    }
});

ReactDOM.render(
    <GenericWrapper><span/><span/><span/></GenericWrapper>,
    document.getElementById('content')
);
```

However, when there is only a single child, `this.props.children` will be the single child component itself without the **array wrapper**. This saves an array allocation.

```jsx
var GenericWrapper = React.createClass({
    componentDidMount: function() {
        console.log(Array.isArray(this.props.children));    /** => false */
        
        /**
         * warning: yields 5 for length of the string 'hello', not 1 for the
         * length of the non-existent array wrapper!
         */
        console.log(this.props.children.length);
    },
    
    render: function() {
        return <div />;
    }
});

ReactDOM.render(
    <GenericWrapper>hello</GenericWrapper>,
    document.getElementById('content')
);
```

To make `this.props.children` easy to deal with, we've provided the [React.Children utilities](https://facebook.github.io/react/docs/top-level-api.html#react.children).
