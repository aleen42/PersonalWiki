## Refs to Components [Back](./../react.md)

After building a component, you may want to "reach out" and invoke methods on component instances returned from `render()`. However, remember that with React, in most cases, it should be unnecessary because the data flow always ensures that the most recent props are sent to each instance. Sometimes in a few cases, it's still necessary and beneficial, so React has provided `refs` for you.

### The ref returned from ReactDOM.render

Not to be confused with the `render()` function that you define on your component (and which returns a virtual DOM element), and [ReactDOM.render()](https://facebook.github.io/react/docs/top-level-api.html#reactdom.render) will return a reference to your component's **backing instance(支撐實例)** (or `null` for [stateless components](https://facebook.github.io/react/docs/reusable-components.html#stateless-functions)).

```js
var myComponent = ReactDOM.render(<MyComponent />, myContainer);
```

Keep in mind that the JSX does not return a component instance! What it return is **ReactElement**: a lightweight representation that tells React what the mounted component should look like.

```js
var myComponentElement = <MyComponent />;   /** Just a ReactEement, but not an instance */

var myComponentInstance = ReactDOM.render(myComponentElement, myContainer);
```

> Note:

> This should only ever be used at the top level. This should only ever be used at the top level. Inside components, let your `props` and `state` handle communication with child components, or use one of the other methods of getting a ref (string attribute or callbacks).

### The ref Callback Attribute

React supports a special attribute that you can attach to any component. The `ref` attribute can be a callback function, and **this callback will be executed immediately after the component is mounted**. The referenced component will be passed in as a parameter, and the callback function may use the component immediately, or save the reference for future use (or both).