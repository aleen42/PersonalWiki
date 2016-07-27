## Server-side Environment [Back](./../tooling_integration.md)

One of the great things about React is that it doesn't require the DOM as a dependency, which means it is possible to render a React application on the server and send the HTML markup down to the client. 

### Node.js

[Node.js](http://nodejs.org/) is a popular JavaScript runtime that comes with an extensive core library and support for installing packages from npm to expand on the basic functionality.

If you use JSX, you may want to pre-compile your components. Alternatively you may want to consider using [Babel's require hook](https://babeljs.io/docs/usage/require/) or [`babel-node`](https://babeljs.io/docs/usage/cli/#babel-node).
