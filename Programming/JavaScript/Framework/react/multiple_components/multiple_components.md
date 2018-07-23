## Multiple Components [Back](./../react.md)

The aim of building modular components is to reuse, to separate different concerns like divide and conquer.

Let's create a simple Avatar component which shows a Facebook page picture and name using the Facebook Graph API.

```jsx
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

```jsx
<Parent><Children /></Parent>
```

In React, `Parent` can read its children by accessing the special `this.props.children` prop. **This is an opaque data structure(不透明數據結構)**: use the [React.Children utilities](https://facebook.github.io/react/docs/top-level-api.html#react.children) to manipulate them.

#### Children Reconciliation(孩子協調)

**Reconciliation is the process by which React updates the DOM with each new render pass**. 

For example, suppose two render passes generate respective markup:

```jsx
/** render 1 */
<Card>
    <p>Paragraph 1</p>
    <p>Paragraph 2</p>
</Card>
```

```jsx
/** render 2 */
<Card>
    <p>Paragraph 2</p>
</Card>
```

We can see that render 2 has removed `<p>Paragraph 1 </p>`, and actually React will reconcile the DOM by changing the text content of the first child to **Paragraph 2**, and destroying the last child.

#### Stateful Children

For children which maintains data in `this.state`, they're not going to be destroied in React. In most case, React will just hide elements:

```jsx
<Card>
    <p style={ { display: 'none' } }>Paragraph 1</p>
    <p>Paragraph 2</p>
</Card>
```

#### Dynamic Chidlren

If the identity and state of each child must be maintained across render passes, you can uniquely identify each child by assigning it a `key`:

```jsx
var OrderList = React.createClass({
    render: function () {
        var results = this.props.results;
        return (
            <ol>
                {
                    results.map(function (result) {
                        return <li key={result.id}>{result.text}</li>;
                    });
                }
            </ol>
        );
    }
});
```

***Notice that: the `key` should always be supplied directly to the components in the array, not to the container HTML child of each component in the array:***

```jsx
/** WRONG !! */
var ListItemWrapper = React.createClass({
    render: function() {
        return <li key={this.props.data.id}>{this.props.data.text}</li>;
    }
});

var MyComponent = React.createClass({
    render: function() {
        return (
            <ul>
                {
                    this.props.results.map(function(result) {
                        return <ListItemWrapper data={result}/>;
                    });
                }
            </ul>
        );
    }
});
```

```jsx
/** Correct */
var ListItemWrapper = React.createClass({
    render: function() {
        return <li>{this.props.data.text}</li>;
    }
});

var MyComponent = React.createClass({
    render: function() {
        return (
            <ul>
                {
                    this.props.results.map(function(result) {
                        return <ListItemWrapper key={result.id} data={result}/>;
                    });
                }
            </ul>
        );
    }
});
```

### Data Flow

In React, data flows from owner to owned component through `props` as discussed above. This is an **one-way data binding**: owners bind their owned component's `props` to some value the owner has computed based on its `props` or `state`.

#### A Note on Performance

Whether it's expensive to change data if there are a large number of nodes under an owner? No, because JavaScript is fast and `render()` tends to be quite simple. The real bottleneck is always the **DOM mutation**, which React will optimize. - **Batching(併發) and Change Detection(增量檢測)**

If you want to have control over performance, you can override `shouldComponentUpdate()` to return false when you want React to skip processing of a subtree.

> ### **Note**:

> If `shouldComponentUpdate()` returns false when data has actually changed, React can't keep your UI in sync. Be sure you know what you're doing while using it, and only use this function when you have a noticeable performance problem. Don't underestimate(低估) how fast JavaScript is relative to the DOM.