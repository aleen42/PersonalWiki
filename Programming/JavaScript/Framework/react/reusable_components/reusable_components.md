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
            if (!/matchme/.test(props[propName]) {
                return new Error('Invalid prop ' + propName + ' supplied to ' + componentName + '. Validation failed.');
            }
        },
        
        /**
         * You can also supply a custom validator to `arrayOf` and `objectOf`.
         * It should return an Error object if the validation fails. The validator
         * will be called for each key in the array or object. The first two
         * arguments of the validator are the array or object itself, and the
         * current item's key.
         */
        customArrayProp: function(propValue, key, componentName, location, propFullName) {
            if (!/matchme/.test(propValue[key])) {
                return new Error('Invalid prop ' + propFullName + ' supplied to ' + componentName + '. Validation failed.');
            }
        }
    };
});
```

#### Single Child

In React, with `React.PropTypes.element`, you can specify that only a single child can be passed to a component as children:

```js
var MyComponent = React.createClass({
    propTypes: {
        children: React.PropTypes.element.isRequired
    },
    
    render: function () {
        return (
            <div>
                /** This must be exactly one element or it will warn. */
                {this.props.children}
            </div>
        );
    }
});
```

### Default Prop Values

In React, you can also define defualt values for your `prop`:

```js
var ComponentWithDefaultProps = React.createClass({
    getDefaultProps: function () {
        return {
            value: 'default value'  
        };
    }
});
```

The result of `getDefaultProps()` will be cached and used to ensure that `this.props.value` will have a value if it was not specified by the parent component.

### Transferring Props: A Shortcut

Using spread operations to directly pass any props from owner componen to the ownee one.

```js
var CheckLink = React.createClass({
    render: function () {
        return (
            /** This takes any props passed to CheckLink and copies them to <a> */
            <a {...this.props}>{'√ '}{this.props.children}</a>
        );
    }
});

ReactDOM.render(
    <CheckList href="/checked.html">
        Clicked here!
    </CheckList>,
    document.getElementById('content')
);
```

### Mixins

Sometimes, different components will share some common functionality, which is called [cross-cutting concerns](https://en.wikipedia.org/wiki/Cross-cutting_concern). React proviedes `mixins` to handle this situation:

```js
var SetIntervalMixins = {
    componentWillMount: funciton () {
        this.intervals = [];
    },
    
    setInterval: function () {
        this.intervals.push(setInterval.apply(null, arguments));
    },
    
    componentWillUnmount: function () {
        this.interval.forEach(clearInterval);
    }
};

var TickTock = React.createClass({
    /** use the mixins */
    mixins: [setIntervalMixins],
    
    getInitialState: function () {
        return { seconds: 0 };
    },
    
    componentDidMount: function () {
        /** call a method on the mixins */
        this.setInterval(this.tick, 1000);
    },
    
    tick: function () {
        this.setState({ seconds: this.state.seconds + 1 });
    },
    
    render: function () {
        return (
            <p>
                React has been running for {this.state.seconds} seconds.
            </p>
        );
    }
});

ReactDOM.render(
    <TickTock />,
    document.getElementById('content')
);
```

React provides [lifecycle methods](https://facebook.github.io/react/docs/working-with-the-browser.html#component-lifecycle) that let you know when a component is about to be created or destroyed. `componentWillMount` will be called when being created, while `componentWillUnmount` will be called when being destroyed.