## Index [Back](./../react_router.md)

### Index Routes

A component for adding default components in a `<Route>`, so that `this.props.children` is not `undefined`.

{%ace edit=false, lang='jsx', theme='tomorrow'%}
<Router>
    <Route path="/" component={App}>
        <IndexRoute component={Home}></IndexRoute>
        <Route path="accounts" component={Accounts}></Route>
        <Route path="statements" component={Statements}></Route>
    </Route>
</Router>
{%endace%}

### Index Redirects

A component for redirecting `/` to one component:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
<Router>
    <Route path="/" component={App}>
        <IndexRedirect to={Accounts}></IndexRoute>
        <Route path="accounts" component={Accounts}></Route>
        <Route path="statements" component={Statements}></Route>
    </Route>
</Router>
{%endace%}

### Index Links


