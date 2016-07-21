## Reusable Components [Back](./../react.md)

Reusable Components with well-designed interfaces mean that the next time you need to build some UIs, and you can write much less code, with **faster development time, fewer bugs, and fewer bytes**.

### Prop Validation

`React.PropTypes` exports a range of validators that can be used to make sure the data you receive is valid. When an invalid value is provided for a prop, a warning will be shown in the JavaScript console. 

*Note that for performance reasons `propTypes` is only checked in development mode.*

```js
React.createClass({
    propTypes: {
        /** 
         * You can declare that a prop is a specific JS primitive.
         * By default, these are all optional.
         */
        optionalArray: React.PropTypes.array,
        optionalBool: React.PropTypes.bool,
        optionalFunc: React.PropTypes.func,
        optionalNumber: React.PropTypes.number,
        optionalObject: React.PropTypes.object,
        optionalString: React.PropTypes.string,
        optionalSymbol: React.PropTypes.symbol,
        
        /** 
         * Anything that can be rendered: numbers, strings, elements or an array
         * (or fragment) containing these types.
         */
        optionalNode: React.PropTypes.node,
        
        /** A React element */
        optionalElement: React.PropTypes.element,
    };
});
```
