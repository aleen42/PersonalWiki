## JSX Spread Attributes [Back](./../react.md)

If you know all the properties that you want to place on a component ahead of time, it is easy to use JSX:

```js
var component = <Component foo={x} bar={y} />
```

It's bad to mutate props like this:

```js
var component = <Component />
component.props.foo = x;    /** bad */
component.props.bar = y;    /** also bad */
```

**Spread Attributes** has used a new operator, `...` notation, in ES6.
