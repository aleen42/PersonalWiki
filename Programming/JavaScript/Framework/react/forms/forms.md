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

```jsx
var InputComponent = React.creteClass({
    render: function () {
        return <input type="text" value="Hello!" />;
    }
});
```

User input will have no effect on the rendered element because React has declared the value to be `Hello!`. To update the value in response to user input, you could use the `onChange` event:

```jsx
var InputComponent = React.creteClass({
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
});
```

*Notice that: A **Controlled** component does not maintain its own internal state; the component renders purely based on props.*

#### Potential Problems with checkbox or radio buttons

Be aware that, in an attempt to normalize change handling for checkbox and radio inputs, React uses a `click` event in place of a `change` event. That's because when calling `preventDefault` in a `change` handler. `preventDefault` stops the browser from visually updating the input, even if `checked` gets toggled. (Solved by removing the call to `preventDefault`, or putting the toggle of `checked` in a `setTimeout`.

### Uncontrolled Components

An `<input>` without a `value` property is an *uncontrolled* component:

```jsx
var InputComponent = React.creteClass({
    render: function () {
        return <input type="text" />;
    }
});
```

If you want to listen to updates to the value, you can also use `onChange` like handling controlled components.

*Notiec that: An **uncontrolled** component maintains its own internal state.*

#### Default Value

If you want to initialize the component with a non-empty value, you can supply a `defaultValue` prop.

```jsx
var InputComponent = React.creteClass({
    render: function () {
        return <input type="text" defaultValue="Hello!" />;
    }
});
```

Likewise, `<input type="checkbox">` and `<input type="radio">` support `defaultChecked`, and `<select>` supports `defaultValue`.

> Note:

> The `defaultValue` and `defaultChecked` props are only used during initial render. If you need to update the value in a subsequent render, you will need to use a **controlled component**.

### Discussions

#### Why Controlled Components?

In HTML, we suppose that we have a `<input>` tag:

```jsx
<input type="text" name="title" value="Untitled" />
```

When the user updates the input, the node's `vaule` *property* will change. However, `node.getAtribute('value')` should still return the value used at initialization time, `Untitled`.

```jsx
var InputComponent = React.creteClass({
    render: function () {
        return <input type="text" name="title" value="Untitled" />;
    }
});
```

However, in React, the value should always be `Untitled`, no matter what the user has changed. Therefore, the state of the view has kept in consistent.

#### Why Textarea Value?

In HTML, the value of `<textarea>` is usually set using its children:

```jsx
<!-- antipattern: DO NOT DO THIS! -->
<textarea name="description">This is the description.</textarea>
```

For HTML, this easily allows developers to supply multiline values. However, since React is JavaScript, we do not have string limitations and can use `\n` if we want newlines. In a world where we have `value` and `defaultValue`, it is ambiguous what role children play. For this reason, you should not use children when setting `<textarea>` values:

```jsx
<textarea name="description" value="This is a description." />
```

#### Why Select Value?

In HTML, The selected `<option>` in an HTML `<select>` is normally specified through that option's `selected` attribute.

However in React, in order to make components easier to manipulate, the following format is adopted instead:

```jsx
<select value="B">
    <option value="A">Apple</option>
    <option value="B">Banana</option>
    <option value="C">Cranberry</option>
</select>
```

To make an uncontrolled component, `defaultValue` is used instead.

> Note:

> You can pass an array into the `value` attribute, allowing you to `select` multiple options in a select tag: `<select multiple={true} value={['B', 'C']}>`.

#### Imperative operations(緊急操作)

If you need to imperatively perform an operation, you have to obtain a reference to the DOM node. For instance, if you want to imperatively submit a form, one approach would be to attach a `ref` to the `form` element and manually call `form.submit()`.