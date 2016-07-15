## Interactivity and Dynamic UIs [Back](./../react.md)

After talking about how to display data with React, this document is talking about how to make our UIs interactive.

### A Simple Example

```js
class LikeButton extends React.component {
    constructor() {
        super();
        
        this.state = {
            linked: false
        };
        
        this.handleClick = this.handleClick.bind(this);
    }
    
    handleClick() {
        this.setState({ linked: !this.state.linked });
    }
    
    render() {
        const text = this.state.linked ? 'like' : 'haven\'t liked';
        return (
            <div onClick={this.handleClick}>
                You {text} this. Click to toggle.
            </div>
        );
    }
}

ReactDOM.render(
    <LikeButton />,
    document.getElementById('example')
);
```

### Event Handling and Synthetic(人造) Events

React has implemented **a synthetic event system** to ensure that all events behave similarly in all browsers with knowing how to bubble and capture events.

### Under the Hood(面紗之下): Autobinding and Event Delegation(委託)

#### Autobinding

When creating callbacks in JavaScript, you usually need to explicitly bind a method to its instance such that the value of `this` is correct. With React, every method is automatically bound to its component instance (except when using ES6 class syntax).

Methods follow the same semantics as regular ES6 classes, meaning that they don't automatically bind `this` to the instance. You'll have to explicitly use `.bind(this)` or arrow functions `=>`:

```js
/** .bind(this) */
<div onClick={this.tick.bind(this)} />
/** arrow functions */
<div onClick={() => this.tick()} />
```

It's recommended to bind events in the constructor so that they are only bound once (for better performnce, especially implementing [shouldComponentUpdate()](https://facebook.github.io/react/docs/component-specs.html#updating-shouldcomponentupdate) with a [shallow comparison](https://facebook.github.io/react/docs/shallow-compare.html) in the child components.):

```js
constructor(props) {
    super(props);
    this.state = { count: props.initilCount };
    this.tick = this.tick.bind(this);
}

/** directly use */
<div onClick={this.tick()} />
```

#### Event delegation

React doesn't actually attach event handlers to the nodes themselves. When React starts up, it starts listening for all events at the top level using a single event listener. When a component is mounted or unmounted, the event handlers are simply added or removed from an internal mapping. When an event occurs, React knows how to dispatch it using this mapping. When there are no event handlers left in the mapping, React's event handlers are simple no-ops. To learn more about why this is fast, see [David Walsh's excellent blog post.](http://davidwalsh.name/event-delegate)

### Components are Just State Machines


