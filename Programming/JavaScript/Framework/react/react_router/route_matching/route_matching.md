## Route Matching [Back](./../react_router.md)

A route has **three attributes** that determine whether or not it "matches" the URL:

- nesting
- path
- precedence (優先級)

### Nesting

Nested routes are arranged in a tree-like structure.

A route path is a string pattern that is used to match a URL (or a portion of one). Route paths are interpreted literally, except for the following special symbols:

- `:paramName`: matches a URL segment up to the next `/`, `?`, or `#`. We can use `this.props.params.paramName` to access this variable.
    {%ace edit=false, lang='jsx', theme='tomorrow'%}
    <Route path="/hello/:paramName"></Route>    {/** match "/hello/aleen" or "/hello/alien" */}
    {%endace%}
- `()`: Wraps a portion of the URL that is optional
    {%ace edit=false, lang='jsx', theme='tomorrow'%}
    <Route path="/hello(/:paramName)"></Route>    {/** match "/hello", "/hello/aleen" or "/hello/alien" */}
    {%endace%}
- `*`: Matches all character (non-greedy)
    {%ace edit=false, lang='jsx', theme='tomorrow'%}
    <Route path="/hello/*.jpg"></Route>    {/** match "/hello", "/hello/aleen" or "/hello/alien" */}
    {%endace%}
