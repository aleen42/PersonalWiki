## Transferring Props [Back](./../react.md)

Sometimes in React, we will wrap a component in an abstraction, which will only expose a simple property to do something that might have more complex implementation details.

Therefore, we can use [JSX spread attributes](./../jsx_spread_attributes/jsx_spread_attributes.md) to pass props from an owner component to the ownee one:

```jsx
<Component {...this.props} more="value" />
```

Ignoring JSX, you can also use any object helpers such as ES6 `Object.assign` or Underscore `_.extend`:

```js
React.createElement(Component, Object.assign{}, this.props, { more: 'value' });
```

### Manual Transfer

Most of the time you should **explicitly pass** the properties **down**. This ensures that you only expose a subset of the inner API.

```jsx
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

That ensures that you pass down all the props **EXCEPT** the consumed prop `checked`:

```jsx
function FancyCheckBox(props) {
    var { checked, ...other} = props;
    var fancyClass = checked ? 'FancyChecked' : 'FancyUnchecked';
    
    /** other contains { onClick: console.log } but not the checked property */
    
    return (
        <div {...other} className={fancyClass} />
    );
}

ReactDOM.render(
    <FancyCheckBox checked={true} onClick={console.log.bind(console)} >
    </FancyCheckBox>,
    document.getElementById('content');
);
```

### Consuming and Transferring Again

If you want to consume a property but also want to pass it along, you can repass it explicitly. Rather than passing the full `props`, this way is easier to refactor and lint(語法檢查).

```jsx
function FancyCheckbox(props) {
    var { checked, title, ...other } = props;
    var fancyClass = checked ? 'FancyChecked' : 'FancyUnchecked';
    var fancyTitle = checked ? 'X ' + title : 'O ' + title;
    
    return (
        <label>
            <input {...other} checked={checked} className={fancyClass} type="checkbox" />
            {fancyTitle}
        </label>
    );
}
```

> **NOTE:**

> Order matters. By putting the `{...other}` before your JSX props you ensure that the consumer of your component can't override them.

### Rest and Spread Properties `...`

Rest properties allow you to **extract the remaining properties** from an object into a new object. It excludes every other property listed in the destructuring pattern.

```js
var { x, y, ...z } = { x: 1, y: 2, a: 1, b: 2 };

console.log(x);     /** => 1              */
console.log(y);     /** => 2              */
console.log(z);     /** => { a: 1, b: 2 } */
```

> **NOTE:**

> To transform rest and spread properties using Babel 6, you need to install the [`es2015`](https://babeljs.io/docs/plugins/preset-es2015/) preset, the [`transform-object-rest-spread`](https://babeljs.io/docs/plugins/transform-object-rest-spread/) plugin and configure them in the `.babelrc` file.

### Transferring with Underscore

If you don't use JSX, you can use a library to achieve the same pattern. Underscore supports `_.omit` to filter out properties and `_.extend` to copy properties onto a new object.

```js
function FancyCheckBox(props) {
    var checked = props.checked;
    var other = _.omit(props, 'checked');
    var fancyClass = checked ? 'fancyChecked' : 'fancyUnchecked';
    
    return (
        React.DOM.div(_.extend({}, other, { className: fancyClass }))
    );
}
```
