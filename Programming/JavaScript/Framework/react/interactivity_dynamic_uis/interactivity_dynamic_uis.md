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

**Autobinding**: When creating callbacks in JavaScript, you usually need to explicitly bind a method to its instance such that the value of `this` is correct. 

