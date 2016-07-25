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

