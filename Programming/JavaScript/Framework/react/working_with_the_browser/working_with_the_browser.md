## Working With the Browser [Back](./../react.md)

Sometimes, we need to access the underlying API, perhaps to work with a third-party library or existing code.

### The Virtual DOM

React is very fast because it never talks to the DOM directly. React maintains a fast in-memory representation of the DOM. `render()` methods **actually return a description of the DOM**, and React can compare this description with the in-memory representation to compute the fastest way to update the browser.
