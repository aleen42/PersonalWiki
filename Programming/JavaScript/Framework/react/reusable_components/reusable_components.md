## Reusable Components [Back](./../react.md)

Reusable Components with well-designed interfaces mean that the next time you need to build some UIs, and you can write much less code, with **faster development time, fewer bugs, and fewer bytes**.

### Prop Validation

`React.PropTypes` exports a range of validators that can be used to make sure the data you receive is valid. When an invalid value is provided for a prop, a warning will be shown in the JavaScript console. 

*Note that for performance reasons `propTypes` is only checked in development mode.*

```jsx
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

```jsx
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

```jsx
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

Using [JSX spread attributes](./../jsx_spread_attributes/jsx_spread_attributes.md) to directly pass any props from owner componen to the ownee one.

```jsx
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

```jsx
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

### ES6 Classes

```jsx
class HelloMessage extends React.Component {
    render() {
        return (
            <div>Hello, {this.props.name}</div>
        );
    }
}
```

This API is similar to `React.createClass` with the exception of `getInitialState`. Without providing a `getInitialState` method, you can just set up your state in the constructor within ES6.

```jsx
export class Counter extends React.Component {
    constructor(props) {
        super(props);
        
        this.state = { count: props.initialCount };
        this.tick = this.tick.bind(this);
    }
    
    tick() {
        this.setState({ count: this.state.count +1 });
    }
    
    render() {
        return (
            <div onClick={this.tick}>
                Clicks: {this.state.count}
            </div>
        );
    }
}

Counter.propTypes = { initialCount: React.PropTypes.number};
Counter.defaultProps = { initialCount: 0 };
```

Another difference is that `propTypes` and `defaultProps` are defined as properties on the constructor instead of in the class body.

#### No Autobinding 

Methods follow the same semantics as regular ES6 classes, meaning that they don't automatically bind `this` to the instance. You'll have to explicitly use `.bind(this)` or arrow functions `=>`:

```jsx
<div onClick={this.tick.bind(this)}></div>
<div onClick={() => this.tick()}></div>
```

*It's recommended that binding in the constructor method, so tht you can only bind once. This is better for performance of your application, especially if you implement [shouldComponentUpdate()](https://facebook.github.io/react/docs/component-specs.html#updating-shouldcomponentupdate) with a [shallow comparison](https://facebook.github.io/react/docs/shallow-compare.html) in the child components.*

#### No Mixins

Unfortunately ES6 launched without any mixin support. Therefore, there is no support for mixins when you use React with ES6 classes. Instead, we're working on making it easier to support such use cases without resorting to mixins.

### Stateless Functions

Using Function to define a React class:

```jsx
function HelloMessage(props) {
    return <div>Hello, {props.name}</div>;
}
ReactDOM.render(<HelloMessage name="aleen" />, document.getElementById('content'));
```

Using Arrow Function to define a React class:

```jsx
var HelloMessage = (props) => <div>Hello, {props.name}</div>;
ReactDOM.render(<HelloMessage name="aleen" />, document.getElementById('content'));
```

*Notice that: remember to set `propTypes` and `defaultProps`*

```jsx
HelloMessage.propTypes = { name: React.PropTypes.string };
HelloMessage.defaultProps = { name: 'aleen' };
```

> #### Note:

> Because stateless functions don't have a backing instance, you can't attach a ref to a stateless function component. Normally this isn't an issue, since stateless functions do not provide an imperative API. Without an imperative API, there isn't much you could do with an instance anyway. However, if a user wants to find the DOM node of a stateless function component, they must wrap the component in a stateful component (eg. ES6 class component) and attach the ref to the stateful wrapper component.

> NOTE:

> In React v0.14, stateless functional components were not permitted to return `null` or `false` (a workaround is to return a `<noscript />` instead). This was fixed in React v15, and stateless functional components are now permitted to return `null`.

In an ideal world, most of your components would be stateless functions because in the future we'll also be able to make performance optimizations specific to these components by avoiding unnecessary checks and memory allocations.