## Transferring Props [Back](./../react.md)

Sometimes in React, we will wrap a component in an abstraction, which will only expose a simple property to do something that might have more complex implementation details.

Therefore, we can use [JSX spread attributes](./../jsx_spread_attributes/jsx_spread_attributes.md) to pass props from an owner component to the ownee one:

```js
<Component {...this.props} more="value" />
```
