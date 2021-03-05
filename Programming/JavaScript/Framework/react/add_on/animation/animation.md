## Animation [Back](./../add_on.md)

React provides a `ReactTransitionGroup` add-on component as a low-level API for animation, and a `ReactCSSTransitionGroup` for easily implementing basic CSS animations and transitions.

### High-level API: `ReactCSSTransitionGroup`

`ReactCSSTransitionGroup` is based on `ReactTransitionGroup` and is an easy way to perform CSS transitions and animations when a React component enters or leaves the DOM. It's inspired by the excellent [ng-animate](http://www.nganimate.org/) library.

#### Getting Started

`ReactCSSTransitionGroup` is the interface to ReactTransitions. This is a simple element that wraps all of the components you are interested in animating. Here's an example where we fade list items in and out.

```jsx
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
```

> **Note:**

> You must provide [the `key` attribute](https://facebook.github.io/react/docs/multiple-components.html#dynamic-children) for all children of `ReactCSSTransitionGroup`, even when only rendering a single item. This is how React will determine which children have entered, left, or stayed.

In this component, when a new item is added to `ReactCSSTransitionGroup` it will get the `example-enter` CSS class and the `example-enter-active` CSS class added in the next tick. This is a convention based on the `transitionName` prop.

Therefore, we can use these classes:

```css
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
```

You may notice that animation durations need to be specified in both the CSS and the render. That's to tell React **when to remove the animation classes from the element** and **when to remove element from the DOM**.

#### Animate Initial Mounting 

`ReactCSSTranitionGroup` has provided an optional prop `transitionAppear`, to add an extra transition phase at the intial mount of the component.

```jsx
var MyComponent = React.createClass({
    render: function () {
        return (
            <ReactCSSTransitionGroup transtionName="example" transitionAppear={true} transitionAppearTimeout={500}>
                <h3>Fading at Inital Mount</h3>
            </ReactCSSTransitionGroup>
        );
    }
});
```

```css
.example-appear {
    opacity: 0.01;
}

.example-appear.example-appear-active {
    opacity: 1;
    transition: opacity 0.5s ease-in;
}
```

At the initial mount, all children of the `ReactCSSTransitionGroup` will `appear` but not `enter`. However, all children later added to an existing `ReactCSSTransitionGroup` will `enter` but not `appear`.

#### Custom Classes

It is also possible to use custom class names for each of the steps in your transitions. Instead of passing a string into transitionName you can pass an object containing either the `enter` and `leave` class names, or an object containing the `enter`, `enter-active`, `leave-active`, and `leave` class names. If only the `enter` and `leave` classes are provided, the `enter-active` and `leave-active` classes will be determined by appending '-active' to the end of the class name.

```jsx
<ReactCSSTransitionGroup transitionName={ {
        'enter': 'enter',
        'enterActive': 'enterActive',
        'leave': 'leave',
        'leaveActive': 'leaveActive',
        'appear': 'appear',
        'appearActive': 'appearActive'
    }
}></ReatCSSTransitionGroup>
```

#### Disabling Animations

You can disable animating `enter` or `leave` animations if you want. Just add `transitionEnter={false}` or `transitionLeave={false}` props to `ReactCSSTransitionGroup` to disable these animations.
