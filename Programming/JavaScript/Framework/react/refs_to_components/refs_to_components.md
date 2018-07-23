## Refs to Components [Back](./../react.md)

After building a component, you may want to "reach out" and invoke methods on component instances returned from `render()`. However, remember that with React, in most cases, it should be unnecessary because the data flow always ensures that the most recent props are sent to each instance. Sometimes in a few cases, it's still necessary and beneficial, so React has provided `refs` for you.

### The ref returned from ReactDOM.render

Not to be confused with the `render()` function that you define on your component (and which returns a virtual DOM element), and [ReactDOM.render()](https://facebook.github.io/react/docs/top-level-api.html#reactdom.render) will return a reference to your component's **backing instance(支撐實例)** (or `null` for [stateless components](https://facebook.github.io/react/docs/reusable-components.html#stateless-functions)).

```jsx
var myComponent = ReactDOM.render(<MyComponent />, myContainer);
```

Keep in mind that the JSX does not return a component instance! What it return is **ReactElement**: a lightweight representation that tells React what the mounted component should look like.

```jsx
var myComponentElement = <MyComponent />;   /** Just a ReactEement, but not an instance */

var myComponentInstance = ReactDOM.render(myComponentElement, myContainer);
```

> Note:

> This should only ever be used at the top level. This should only ever be used at the top level. Inside components, let your `props` and `state` handle communication with child components, or use one of the other methods of getting a ref (string attribute or callbacks).

### The ref **Callback** Attribute

React supports a special attribute that you can attach to any component. The `ref` attribute can be a callback function, and **this callback will be executed immediately after the component is mounted**. The referenced component will be passed in as a parameter, and the callback function may use the component immediately, or save the reference for future use (or both).

```jsx
var MyComponent = React.createClass({
    render: function () {
        return (
            <Textarea ref={
                function (input) {
                    if (input !== null ) {
                        input.focus();
                    }
                }
            }}></Textarea>
        );
    }
});
```

or using ES6 Arrow Functions:

```jsx
class MyComponent extends React.Component {
    render: function () {
        return (
            <Textarea ref={(input) => this._input = input}></Textarea>
        );
    }
    
    componentDidMount: function () {
        if (this._input !== null ) {
            this._input.focus();
        }
    }
}
```

*Notice that: when the referenced component is unmounted and whenever the ref changes, the old ref will be called with `null` as an argument. Also when writing refs with inline function expressions as in the examples here, React sees a different function object each time so on every update, ref will be called with `null` immediately before it's called with the component instance.*

### The ref **String** Attribute

> Note:

> Although string refs are not deprecated, but will likely be t smoe point in the future. Therefore, **Callback refs are preferred**.
 
React also supports using a string (instead of a callback) as a ref prop on any component.

1. Assign a `ref` attribute to anything returned from `render`:
    
    ```jsx
<input ref="myInput" />
    ```
2. In some other code, we can access the **backing instance** via `this.refs` as in:
    
    ```jsx
var inputInstance = this.refs.myInput;
var inputValue = inputInstance.value;
    ```

### An example

```jsx

/** ES6 */
class MyComponent extends React.Component {
	constructor(props) {
		super(props);
		this.handleClick = this.handleClick.bind(this);
	}

	handleClick() {
		if (this.myInput !== null) {
			this.myInput.focus();
		}
	}

	render() {
		return (
			<div>
				<input type="text" ref={(ref) => this.myInput = ref} />
				<input type="button" value="focus the input text" onClick={this.handleClick} />
			</div>
		);
	}
}

/** ES5 */
var MyComponent = React.createClass({
	handleClick: function () {
		if (this.myInput !== null) {
			this.myInput.focus();
		}
	},

	render: function () {
		return (
			<div>
				<input type="text" ref={
					function (ref) {
						this.myInput = ref;
					}
				} />
				<input type="text" value="focus the input text" onClick={this.handleClick} />
			</div>
		);
	}
});

ReactDOM.render(
	<MyComponent />,
	document.getElementById('content')
);

```

### Summary

Refs are a great way to send a message to a particular child instance in a way that would be inconvenient to do via streaming Reactive `props` and `state`. They should, however, not be your go-to abstraction for flowing data through your application. By default, use the Reactive data flow and save `ref`s for use cases that are inherently non-reactive.

#### Benefits:

- You can define any public method on your component classes (such as a reset method on a Typeahead) and call those public methods through refs (such as `this.refs.myTypeahead.reset()`).
- Performing DOM measurements almost always requires reaching out to a "native" component such as `<input />` and accessing its underlying DOM node using a ref. Refs are one of the only practical ways of doing this reliably.
- Refs are automatically managed for you! If that child is destroyed, its ref is also destroyed for you. No worrying about memory here (unless you do something crazy to retain a reference yourself).

#### Cautions:

- **Never** access refs inside of any component's render method – or while any component's render method is even running anywhere in the call stack.
- If you want to preserve Google Closure Compiler advanced-mode crushing resilience, make sure to never access as a property what was specified as a string. This means you must access using `this.refs['myRefString']` if your ref was defined as `ref="myRefString"`.
- If you have not programmed several apps with React, your first inclination is usually going to be to try to use refs to "make things happen" in your app. If this is the case, take a moment and think more critically about where state should be owned in the component hierarchy. Often, it becomes clear that the proper place to "own" that state is at a higher level in the hierarchy. Placing the state there often eliminates any desire to use `ref`s to "make things happen" – instead, the data flow will usually accomplish your goal.
- Refs may not be attached to a [stateless function](https://facebook.github.io/react/docs/reusable-components.html#stateless-functions), because the component does not have a backing instance. You can always wrap a stateless component in a standard composite component and attach a ref to the composite component.