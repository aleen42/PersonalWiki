## Transferring Props [Back](./../react.md)

Sometimes in React, we will wrap a component in an abstraction, which will only expose a simple property to do something that might have more complex implementation details.

Therefore, we can use [JSX spread attributes](./../jsx_spread_attributes/jsx_spread_attributes.md) to pass props from an owner component to the ownee one:

```js
<Component {...this.props} more="value" />
```

Ignoring JSX, you can also use any object helpers such as ES6 `Object.assign` or Underscore `_.extend`:

```js
React.createElement(Component, Object.assign{}, this.props, { more: 'value' });
```

### Manual Transfer

Most of the time you should **explicitly pass** the properties **down**. This ensures that you only expose a subset of the inner API.

```js
function FancyCheckBox(props) {
    var fancyClass = props.checked ? 'FancyChecked' : 'FancyUnchecked';
    
    return (
        <div className={fancyClass} onClick={props.onClick}>
            {props.children}
        </div>
    );
}

ReactDOM.render(
    <FancyCheckBox checked={true} onClick={console.log.bind(console)}>
    </FancyCheckBox>,
    document.getElementById('content')
);
```

But what about the `name`, `title` or `onMouseOver` prop?

### Transferring with `...` in JSX

Sometimes, it's fragile(易碎) and tedious(冗長) to pass every property along. Therefore, we can use [destructuring assignment](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment) to extract.

As followed, you can list out all the properties that you would like to consume(銷毀), followed by `...other`.

```js
var { checked, ...other } = props;
```