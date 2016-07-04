## JSX Syntax [Back](./../react.md)

JSX is a Javascript syntax extension that look similar to XML. You can use a simple JSX syntactic transform with React.

#### Why JSX?

According to the official statement, JSX is concise and familiar syntax for defining tree structures with attributes.

#### HTML Tags vs. React Components

React can either render HTML tags (strings) or React Components(classes).

To render a HTML tags, just use camelCase tag name in JSX:

```jsx
/** camelCase Naming */
var divElement = <div className="foo" />;
ReactDOM.render(
    divElement,
    document.getElelementById('example')
);
```

To render a React Component, just create a local variable that naming with PascalCase name:

```jsx
var MyComponent = React.createClass({/** ... */});
var myElement = <MyComponent someProperty={true} />;
ReactDOM.render(
    myElement,
    document.getElementById('example')
);
```

*Note: Since JSX is JavaScript, identifiers such as **class** and **for** are discouraged as XML attribute names. Instead, React DOM components expect DOM property names like **className** and **htmlFor**, respectively.*

#### JSX Transforms

React JSX transforms from an XML-like syntax into native JavaScript. XML **elements**, **attributes** and **children** will be transformed into arguments that are passed to the moethod `React.createElement`.

```jsx
var Nav;

/** input JSX syntx */
var app = <Nav color="blue">;
```

```js
var Nav;

/** output JavaScript syntax */
var app = React.createElement(Nav, {color: 'blue'});
```

JSX also allows specifying children using XML syntax:

```jsx
var Nav;
var Profile;

/** input JSX syntx */
var app = <Nav color="blue"><Profile>click</Profile></Nav>;
```

```js
var Nav;
var Profile;

/** output JavaScript syntax */
var app = React.creatElement(
    Nav,
    { color: 'blue' },
    React.createElement(
        Profile,
        null,
        'click'
    )
);
```

JSX will infer(推斷出) the class's displayName