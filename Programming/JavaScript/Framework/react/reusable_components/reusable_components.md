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
        
        /** 
         * You can also declare that a prop is an instance of a class. This uses
         * JS's instanceof operator.
         */
        optionalMessage: React.PropTypes.instanceOf(Message),
        
        /**
         * You can ensure that your prop is limited to specific values by treating
         * it as an enum.
         */
        optionalEnum: React.PropTypes.oneOf(['News', 'Photos']),
        
        /** An object that could be one of many types */
        optionalUnion: React.PropTypes.oneOfType([
            React.PropTypes.string,
            React.PropTypes.number,
            React.PropTypes.instanceOf(Message)
        ]),
        
        /** An array of a certain type */
        optionalArrayOf: React.PropTypes.arrayOf(React.PropTypes.number),
        
        /** An object with property values of a certain type */
        optionalObjectOf: React.PropTypes.objectOf(React.PropTypes.number),
        
        /** An object taking on a particular shape */
        optionalObjectWithShape: React.PropTypes.shape({
            color: React.PropTypes.string,
            fontSize: React.PropTypes.number
        }),
        
        /**
         * You can chain any of the above with `isRequired` to make sure a warning
         * is shown if the prop isn't provided.
         */
        requiredFunc: React.PropTypes.func.isRequired,
        
        /** A value of any data type */
        requiredAny: React.PropTypes.any.isRequired,
        
        /**
         * You can also specify a custom validator. It should return an Error
         * object if the validation fails. Don't `console.warn` or throw, as this
         * won't work inside `oneOfType`.
         */
        customProp: function (props, propName, componentName) {
        }
            
        ,
    };
});
```
