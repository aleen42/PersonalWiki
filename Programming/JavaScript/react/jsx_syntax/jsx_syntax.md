## JSX Syntax [Back](./../react.md)

JSX is a Javascript syntax extension that look similar to XML. You can use a simple JSX syntactic transform with React.

#### Why JSX?

According to the official statement, JSX is concise and familiar syntax for defining tree structures with attributes.

#### HTML Tags vs. React Components

React can either render HTML tags (strings) or React Components(classes).

To render a HTML tags, just use camelCase tag name in JSX:

```js
/** camelCase Naming */
var divElement = <div className="foo" />;
ReactDOM.render(
    divElement,
    document.getElelementById('example')
);
```

To render a React Component, just create a local variable that naming with PascalCase name:

```js
var MyComponent = React.createClass({/** ... */});
var myElement = <MyComponent someProperty={true} />;
ReactDOM.render(
    myElement,
    document.getElementById('example')
);
```

*Note: Since JSX is JavaScript, identifiers such as **class** and **for** are discouraged as XML attribute names. Instead, React DOM components expect DOM property names like **className** and **htmlFor**, respectively.*