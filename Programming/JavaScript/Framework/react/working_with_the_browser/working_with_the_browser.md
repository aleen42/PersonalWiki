## Working With the Browser [Back](./../react.md)

Sometimes, we need to access the underlying API, perhaps to work with a third-party library or existing code.

### The Virtual DOM

React is very fast because it never talks to the DOM directly. React maintains a fast in-memory representation of the DOM. `render()` methods **actually return a description of the DOM**, and React can compare this description with the in-memory representation to compute the fastest way to update the browser.

Additionally, React **implements a full synthetic event system** such that all event objects are guaranteed to conform to the W3C spec despite browser quirks, and everything bubbles consistently and efficiently across browsers.

However, sometimes you simply need to access the underlying API, perhaps to work with a third-party library like a jQuery plugin. React provides escape hatches(門徑) for you to use the underlying DOM API directly.