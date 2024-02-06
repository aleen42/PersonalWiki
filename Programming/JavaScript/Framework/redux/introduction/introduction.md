## Introduction [Back](./../redux.md)

In Redux, the whole state of your app is stored in an object tree inside a single store.

The only way to change the state tree is to emit an action, which will describe what happens. Like this:

```js
import { createStore } from 'redux';

/**
 * This is a reducer, a pure function with (state, action) => state signature.
 * It describes how an action transforms the state into the next state.
 *
 * The shape of the state is up to you: it can be a primitive, an array, an object,
 * or even an Immutable.js data structure. The only important part is that you should
 * not mutate the state object, but return a new object if the state changes.
 *
 * In this example, we use a `switch` statement and strings, but you can use a helper that
 * follows a different convention (such as function maps) if it makes sense for your
 * project.
 */
function counter(state = 0, action) {
    switch (action.type) {
    case 'INCREMENT':
        return state + 1;
    case 'DECREMENT':
        return state - 1;
    default:
        return state;
    }
}

/** 
 * Create a Redux store holding the state of your app.
 * Its API is { subscribe, dispatch, getState }.
 */
let store = createStore(counter);

/**
 * You can use subscribe() to update the UI in response to state changes.
 * Normally you'd use a view binding library (e.g. Redux) rather than subscribe() directly.
 * However it can also be handy to persist the current state in the localStorage.
 */
store.subscribe(() =>
    console.log(store.getState())
);

/**
 * The only way to mutate the internal state is to dispatch an action.
 * The actions can be serialized, logged or stored and later replayed.
 */
store.dispatch({ type: 'INCREMENT' });      /** => 1    */
store.dispatch({ type: 'INCREMENT' });      /** => 2    */
store.dispatch({ type: 'DECREMENT' });      /** => 1    */
```

As we can see above, state can be only changed by dispatching an action object to a function, which is called **Reducer** in Redux.

### Three Principles

Redux can be described in three fundamental principles:

- **Single source of truth**
    - The state of your whole application is stored in an object tree **within a single store**.
- **State is read-only**
    - The only way to change the state is to emit an action, an object describing what happened.
- **Changes are made with pure functions**
    - A pure Reducer is to specify how the state tree is transformed by actions.
