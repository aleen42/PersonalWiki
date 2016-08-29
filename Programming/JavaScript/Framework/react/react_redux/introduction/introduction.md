## Introduction [Back](./../react_redux.md)

In React Redux, the whole state of your app is stored in an object tree inside a single store.

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


```