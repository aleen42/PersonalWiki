## Communicate Between Components [Back](./../react.md)

- **parent-child**: just pass props
- **child-parent**: use `bind(this, arguments)`

```jsx
var handleClick = function (i, props) {
    console.log('clicked: ' + props.items[i]);
};

function List(props) {
    return (
        <div>
            {
                props.items.map(function (item, i) {
                    return (
                        <div onClick={handleClick.bind(this, i, props)} key={i}>{item}</div>
                    );
                });
            }
        </div>
    );
}

ReactDOM.render(
    <List items={['Apple', 'Banana', 'Cranberry']} />,
    document.getElementById('content')
);
```

For communication between two components that don't have a parent-child relationship, you can set up your own global event system. Subscribe to events in `componentDidMount()`, unsubscribe in `componentWillUnmount()`, and call `setState()` when you receive an event.