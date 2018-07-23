## Histories [Back](./../react_router.md)

A history knows how to listen to the browser's address bar for changes and parses the URL into a `location` object that the router can use to match routes and render the correct set of components.

In React Router, there are 3 types of histories which are come across most often:

- `browserHistory`
- `hashHistory`
- `createMemoryHistory`

### Usage

Just import them separately and pass them into a `<Router>`:

```jsx
import React from 'react';
import ReactDOM from 'react-dom';
import { browserHistory } from `react-router`;

ReactDOM.render(
    <Router history={browserHistory} routes={routes}></Router>,
    document.getElementById('content')
);
```

### `browserHistory`

Browser history is recommended to used in a **browser application** with React Router.

#### Configuring servers

An express app might look like this;

```js
const express = require('express')
const path = require('path')
const port = process.env.PORT || 8080
const app = express()

// serve static assets normally
app.use(express.static(__dirname + '/public'))

// handle every other route with index.html, which will contain
// a script tag to your application's JavaScript file(s).
app.get('*', function (request, response){
  response.sendFile(path.resolve(__dirname, 'public', 'index.html'))
})

app.listen(port)
console.log("server started on port " + port)
```

If **Nginx**:

```
server {
    ...
    location / {
        try_files $uri /index.html;
    }
}
```

If **Apache**, create a `.htacess` file:

```
RewriteBase /
RewriteRule ^index\.html$ - [L]
RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_FILENAME} !-d
RewriteRule . /index.html [L]
```

### `hashHistory`

Hash history uses the hash (`#`) portion of the URL, creating routes that look like `example.com/#/some/path`.

#### Cons

In general, production web applications should use `browserHistory` for **the cleaner URLs**, and for **support for server-side rendering**, which is impossible with `hashHistory`.

#### Pros

For older version browsers, it may still be in need to be used.

### `createMemoryHistory`

Memory history doesn't manipulate or read from the address bar. It's also useful for testing and other rendering environments (like React Native).

It's a bit different than the other two histories because you have to create one, it is this way to facilitate testing:

```js
const history = createMemoryHistory(location);
```