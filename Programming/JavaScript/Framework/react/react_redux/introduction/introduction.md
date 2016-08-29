## Introduction [Back](./../react_redux.md)

In React Redux, the whole state of your app is stored in an object tree inside a single store.

The only way to change the state tree is to emit an action, which will describe what happens. Like this:

```js
import { createStore } from 'redux';
```