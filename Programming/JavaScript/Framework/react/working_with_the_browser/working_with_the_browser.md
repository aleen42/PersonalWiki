## Working With the Browser [Back](./../react.md)

Sometimes, we need to access the underlying API, perhaps to work with a third-party library or existing code.

### The Virtual DOM

React is very fast because it never talks to the DOM directly. React maintains a fast in-memory representation of the DOM. `render()` methods **actually return a description of the DOM**, and React can compare this description with the in-memory representation to compute the fastest way to update the browser.

Additionally, React **implements a full synthetic event system** such that all event objects are guaranteed to conform to the W3C spec despite browser quirks, and everything bubbles consistently and efficiently across browsers.

However, sometimes you simply need to access the underlying API, perhaps to work with a third-party library like a jQuery plugin. React provides escape hatches(門徑) for you to use the underlying DOM API directly.

### Refs and findDOMNode()

To interact with the browser, you'll need a reference to a DOM node. You can attach a `ref` to any element, which allows you to reference the **backing instance** of the component.

React has provided `findDOMNode()` function for you to catch this element like:

```jsx
var MyComponent = React.createClass({
    handleClick: function () {
        React.findDOMNode(this.refs.myTextInput).focus();
    },

    render: function () {
        return (
            <input type="text" ref="myTextInput" />
            <input type="button" value="Focus the text input" onClick={} />
        );
    }
});

ReactDOM.render(
    <MyComponent />,
    document.getElementById('content')
);
```

### Component Lifecycle

Components have **3 parts** of their lifecycle:

- **Mounting**: a component has been inserted into the DOM
- **Updating**: a component is re-rendered to determine if the DOM should be updated
- **Unmounting**: a component has been removed from the DOM

React has provided some methods to hook components' lifecycles. `will` method is called before somethig happens, and `did` method is called right after something happens.

#### Mounting

- `getInitialState(): object` is invoked before a component is mounted. Stateful compoenents should implement this and return the initial state data.
- `componentWillMount()` is invoked immediately before mounting occurs.
- `componentDidMount()` is invoked immediately after mounting occurs.

#### Updating

- `componentWillReceiveProps(object nextProps)` is invoked when a mounted component receives new props. (This method should be used to compare `this.props` and `nextProps` to perform state transitions using `this.setState()`)
- `shouldComponentUpdate(object nextProps, object nextState): boolean` is invoked when a component decides whether any changes render an update to the DOM. (return `false` if React should skip updating.)
- `componentWillUpdate(object nextProps, object nextState)` is invoked immediately before updating occurs. (`this.setState()` is forbidden to use here, or it will fall into a endless loop)
- `componentDidUpdate(object prevProps, object prevState)` is invoked immediately after updating occurs.

#### Unmounting

- `componentWillUnmount()` is invoked immediately before a component is unmounted and destroyed. (Cleanup should go here)

#### Mounted Methods

- `component.forceUpdate()` can be invoked on any mounted component when you know that some depper aspect of the component's state has changed without using `this.setState()`

### Browser Support

React supports most popular browsers, including Internet Explorer 9 and above.

(We don't support older browsers that don't support ES5 methods, but you may find that your apps do work in older browsers if polyfills such as [es5-shim and es5-sham](https://github.com/es-shims/es5-shim) are included in the page. You're on your own if you choose to take this path.)

kriskowal's [es5-shim](https://github.com/kriskowal/es5-shim) `es5-shim.js` has provided following APIs for React:

- `Array.isArray`
- `Array.prototype.every`
- `Array.prototype.forEach`
- `Array.prototype.indexOf`
- `Array.prototype.map`
- `Date.now`
- `Function.prototype.bind`
- `Object.keys`
- `String.prototype.split`
- `String.prototype.trim`

kriskowal's [es5-shim](https://github.com/kriskowal/es5-shim) `es5-sham.js` has also provided some APIs:

- `Object.create`
- `Object.freeze`

Uncompressed React need paulmillr's [console-polyfill](https://github.com/paulmillr/console-polyfill):

- `console.*`

> Note:

> `onScroll` is not allowed for IE8, becuase IE8 doesn't have an API to define handlers to the capturing phase of an event.