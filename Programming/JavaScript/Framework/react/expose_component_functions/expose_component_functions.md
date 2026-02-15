## Expose Component Functions [Back](./../react.md)

There's another (uncommon) way of [communicating between components](./../communication_between_components/communication_between_components.md): **simply expose a method on the child component for the parent to call**.

Say a list of todos, which upon clicking get removed. If there's only one unfinished todo left, animate it:

```jsx
var Todo = React.createClass({
    render: function () {
        return (
            <div onClick={this.props.onClick}>{this.props.title}</div>
        );
    },
    
    /** expose an animating function for parent to call */
    animate: function () {
        cosole.log('Pretend %s is animating', this.props.title);
    }
});

var Todos = React.createClass({
    getInitialState: function () {
        return { items: ['Apple', 'Banana', 'Cranberry'] };
    },
    
    handleClick: function (index) {
        var items = this.state.items.filter(item, i) {
            return index !== i;
        });
        
        this.setState({ items: items }, function () {
            if (items.length === 1) {
                /** call child function */
                this.refs.item0.animate();
            }
        }.bind(this));
    },
    
    render: function () {
        return (
            <div>
                {this.state.items.map(function (item, i) {
                    var boundClick = this.handleClick.bind(this, i);
                    return (
                        <Todo onClick={boundClick} key={i} title={item} ref={'item' + i}></Todo>
                    );
                }, this);}
            </div>
        );
    }
});

ReactDOM.render(
    <Todos />,
    document.getElementById('content')
);
```

Alternatively, you could have achieved this by passing the `todo` an `isLastUnfinishedItem` prop, let it check this prop in `componentDidUpdate`, then animate itself; however, this quickly gets messy if you pass around different props to control animations.