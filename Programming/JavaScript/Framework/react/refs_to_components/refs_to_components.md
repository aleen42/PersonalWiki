## Refs to Components [Back](./../react.md)

After building a component, you may want to "reach out" and invoke methods on component instances returned from `render()`. However, remember that with React, in most cases, it should be unnecessary because the data flow always ensures that the most recent props are sent to each instance. Sometimes in a few cases, it's still necessary and beneficial, so React has provided `refs` for you.

### ref returned from ReactDOM.render

Not to be confused with the `render()` function that you define on your component (and which returns a virtual DOM element), and [ReactDOM.render()](https://facebook.github.io/react/docs/top-level-api.html#reactdom.render) will return a reference to your component's **backing instance(支撐實例)** (or `null` for [stateless components](https://facebook.github.io/react/docs/reusable-components.html#stateless-functions)).

```js
var myComponent = ReactDOM.render(<MyComponent />, myContainer);
```