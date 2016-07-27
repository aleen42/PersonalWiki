## Server-side Environment [Back](./../tooling_integration.md)

One of the great things about React is that it doesn't require the DOM as a dependency, which means it is possible to render a React application on the server and send the HTML markup down to the client. 

### Node.js

[Node.js](http://nodejs.org/) is a popular JavaScript runtime that comes with an extensive core library and support for installing packages from npm to expand on the basic functionality.

If you use JSX, you may want to pre-compile your components. Alternatively you may want to consider using [Babel's require hook](https://babeljs.io/docs/usage/require/) or [`babel-node`](https://babeljs.io/docs/usage/cli/#babel-node).

> Note:

> Some versions of Node.js have an `Object.assign` implementation that does not preserve key order. This can cause errors when validating the markup, creating a warning that says "React attempted to reuse markup in a container but the checksum was invalid". If you run into this issue, you can override `Object.assign` to use a polyfill that preserves key order. For more details, see [Issue #6451](https://github.com/facebook/react/issues/6451).

### C\#


