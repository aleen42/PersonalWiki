## Forms [Back](./../react.md)

Form components such as `<input>`, `<textarea>` and `<option>` differ from other native components because of their **mutation via use interactions**.

### Interactive Props

Form components support a few props that can be changed via user interacitons:

- `value`: `<input>` or `<textarea>` components.
- `checked`: `<input>` components of type `checkbox` or `radio`.
- `selected`: `<option>` components.

Form components allow listening for changes by setting a callback to the `onChange` prop.

> Note:

> For `<input>` and `<textarea>`, `onChange` supersedes(替代) the DOM's built-in `oninput` event handler.

### Controlled Components

**A Controlled** `<input>` has a `value` prop. Rendering a controlled `<input>` will reflect the value of the `value` prop.

```js
render: function () {
    return <input type="text" value="Hello!" />;
}
```

User input will have no effect on the rendered element because React has declared the value to be `Hello!`. To update the value in response to user input, you could use the `onChange` event:

```js
getInitialState: function () {
    return { value: 'Hello!' };
},

handleChanged: function(event) {
    this.setState({ value: event.target.value });
},

render: function () {
    return (
        <input type="text" value={this.state.value} onChange={this.handleChanged} />
    );
}
```

*Notice that: A **Controlled** component does not maintain its own internal state; the component renders purely based on props.*

#### Potential Problems with checkbox or radio buttons

