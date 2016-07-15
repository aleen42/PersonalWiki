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
                
            </div>
        );
    }
}
```
