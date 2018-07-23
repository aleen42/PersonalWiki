## Route Matching [Back](./../react_router.md)

A route has **three attributes** that determine whether or not it "matches" the URL:

- nesting
- path
- precedence (優先級)

### Nesting

Nested routes are arranged in a tree-like structure.

### Path Syntax

A route path is a string pattern that is used to match a URL (or a portion of one). Route paths are interpreted literally, except for the following special symbols:

- `:paramName`: matches a URL segment up to the next `/`, `?`, or `#`. We can use `this.props.params.paramName` to access this variable.
    ```jsx
    <Route path="/hello/:paramName"></Route>    {/** match "/hello/aleen" or "/hello/alien" */}
    ```
- `()`: Wraps a portion of the URL that is optional
    ```jsx
    <Route path="/hello(/:paramName)"></Route>    {/** match "/hello", "/hello/aleen" or "/hello/alien" */}
    ```
- `*`: Matches all character (non-greedy)
    ```jsx
    <Route path="/hello/*.jpg"></Route>    {/** match "/hello/a.jpg", "/hello/b.jpg" or "/hello/test.jpg" */}
    ```
- `**`: Matches all character (greedy)
    ```jsx
    <Route path="/hello/**.jpg"></Route>    {/** match "/hello/a.jpg" or "/hello/b/c.jpg" */}
    ```

### Precendence

Finally, the routing algorithm attempts to match routes in the order they are defined, top to bottom. So, when you have two sibling routes you should be sure the first doesn't match all possible `path`s that can be matched by the later sibling. For example, don't do this:

```jsx
<Route path="/comments" ...></Route>
<Redirect from="/comments" ...></Route>
```