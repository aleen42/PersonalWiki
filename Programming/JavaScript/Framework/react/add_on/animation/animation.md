## Animation [Back](./../add_on.md)

React provides a `ReactTransitionGroup` add-on component as a low-level API for animation, and a `ReactCSSTransitionGroup` for easily implementing basic CSS animations and transitions.

### High-level API: `ReactCSSTransitionGroup`

`ReactCSSTransitionGroup` is based on `ReactTransitionGroup` and is an easy way to perform CSS transitions and animations when a React component enters or leaves the DOM. It's inspired by the excellent [ng-animate](http://www.nganimate.org/) library.

#### Getting Started

`ReactCSSTransitionGroup` is the interface to ReactTransitions. This is a simple element that wraps all of the components you are interested in animating. Here's an example where we fade list items in and out.

{%ace edit=false, lang='jsx', theme='tomomrrow'%}
var ReactCSSTransitionGroup = require('react-addons-css-transition-group');

var TodoList = React.createClass({
    getInitialState: function () {
        return { items: ['hello', 'world', 'click', 'me'] };
    },
    
    handleAdd: function () {
        var newItems = this.state.items.concat([prompt('Enter some text')]);
        this.setState({ items: newItems });
    },
    
    handleRemove: function (i) {
        var newItems = this.state.items.slice();
        newItems = newItems.splice(i, 1);
        
        this.setState({ items: newItems });
    },
    
    render: function () {
        var items = this.state.items.map(function (item, i) {
            return (
                <div key={item} onClick={this.handleRemove.bind(this, i)}>
                    {item}
                </div>
            );
        });
    
        return (
            <div>
                <button onClick={this.handleAdd}>Add Item</button>
                <ReactCSSTransitionGroup transitionName="example" transitionEnterTimeout={500} transitionLeaveTimeout={300}>
                    {items}
                </ReactCSSTransitionGroup>
            </div>
        );
    }
});
{%endace%}

> **Note:**

> You must provide [the `key` attribute](https://facebook.github.io/react/docs/multiple-components.html#dynamic-children) for all children of `ReactCSSTransitionGroup`, even when only rendering a single item. This is how React will determine which children have entered, left, or stayed.

In this component, when a new item is added to `ReactCSSTransitionGroup` it will get the `example-enter` CSS class and the `example-enter-active` CSS class added in the next tick. This is a convention based on the `transitionName` prop.

Therefore, we can use these classes:

{%ace edit=false, lang='css', theme='tomomrrow'%}
.example-enter {
    opacity: 0.01;
}

.example-enter.example-enter-active {
    opacity: 1;
    transition: opacity 500ms ease-in;
}

.example-leave {
    opacity: 1;
}

.example-leave.example-leave-active {
    opacity: 0.01;
    transition: opacity 300ms ease-in;
}
{%endace%}
