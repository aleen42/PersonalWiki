## Props in getInitialState Is an Anti-Pattern [Back](./../react.md)

Using props to generate state in `getInitialState` often leads to duplication of "source of truth", i.e. where the real data is. This is because `getInitialState` is only invoked when the component is first created.

**Bad example:**

```jsx
var MessageBox = React.createClass({
    getInitialState: function () {
        return { nameWithQualifier: 'Mr.' + this.props.name };
    },
    
    render: function () {
        return (
            <div>
                {this.state.nameWithQualifier}
            </div>
        );
    }
});

ReactDOM.render(
    <MessageBox name="aleen42" />,
    document.getElementById('content')
);
```

**Better:**

```jsx
var MessageBox = React.createClass({
    render: function () {
        return (
            <div>
                {'Mr.' + this.props.name}
            </div>
        );
    }
});

ReactDOM.render(
    <MessageBox name="aleen42" />,
    document.getElementById('content')
);
```

However, it's **not** an anti-pattern if you make it clear that the prop is only seed data for the component's internally-controlled state:

```jsx
var Counter = React.createClass({
    getInitialState: function () {
        return { count: this.props.initialCount };
    },
    
    handleClick: function () {
        this.setState({ count: this.state.count + 1 });
    },
    
    render: function () {
        return (
            <div onClick={this.handeClick}>
                Click me: {this.state.count} times!
            </div>
        );
    }
});

ReactDOM.render(
    <Count initialCount={7} />,
    document.getElementById('content')
);
```