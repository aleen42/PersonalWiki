## Multiple Components [Back](./../react.md)

The aim of building modular components is to reuse, to separate different concerns like divide and conquer.

Let's create a simple Avatar component which shows a Facebook page picture and name using the Facebook Graph API.

```js
var Avatar = React.createClass({
    render: function () {
        return (
            <div>
                <PagePic pagename={this.props.pagename} />
                <PageLink pagename={this.props.pagename} />
            </div>
        );
    }
});

var PagePic = React.createClass({
    render: function() {
        return (
            <img src={'https://graph.facebook.com/' + this.props.pagename + '/picture'} />
        );
    }
});

var PageLink = React.createClass({
    render: function() {
        return (
            <a href={'https://www.facebook.com/' + this.props.pagename}>
                {this.props.pagename}
            </a>
        );
    }
});

ReactDOM.render(
    <Avatar pagename="Engineering" />,
    document.getElementById('example')
);
```

### Ownership

In React, **an owner is the component that sets the `prop` of other components**. More formally, if a component `X` is created in component `Y`'s `render()` method, it is said that `X` is owned by `Y`. 

It's important to draw a distinction between the **owner-ownee** relationship and the **parent-child** relationship. The owner-ownee relationship is specific to React, while the parent-child relationship is simply the one you know and love from the DOM.

### Children

```js
<Parent><Children /></Parent>
```

In React, `Parent` can read its children by accessing the special `this.props.children` prop. **This is an opaque data structure(不透明數據結構)**: use the [React.Children utilities](https://facebook.github.io/react/docs/top-level-api.html#react.children) to manipulate them.

#### Children Reconciliation(孩子協調)

**Reconciliation is the process by which React updates the DOM with each new render pass**. 

For example, suppose two render passes generate respective markup:

```js

```