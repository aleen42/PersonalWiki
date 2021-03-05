## Store [Back](./../redux.md)

The **Store** is the object that bring both **Actions** and **Reducers** together.

Store will be responsible for:

- holding application state
- exposing interface of accessing to state: `getState()`
- exposing interface for getting action dispatching: `dispatch(action)`
- exposing interface for registering listener on the dispatching event: `subscribe(listener)`
- handling unregistering of listeners by calling the function return by `subscribe(listener)`

### Create a store

Remember that there is **only one single store** in a Redux application. To create a producer, what you need is reducer.

```js
import { createStore } from 'redux';
import todoApp from './reducers';

let store = createStore(todoApp);

/** the second argument is optional, which is helpful in matching the state of the client to the state of the server. */
let store = createStore(todoApp, window.STATE_FROM_SERVER);
```

### Dispatching Actions

```js
/** testing todo app's state changments */

import { addTodo, toggleTodo, SetVisibilityFilter, VisibilityFilters } from './actions';

/** log out the initial state */
console.log(store.getState());

/** 
 * Every time the state changes, log it
 * Note that subscribe() returns a function for unregistering the listener
 */
let unsubscribe = store.subscribe(() => {
    console.log(store.getState());
});

/** Dispatching actions */
store.dispatch(addTodo('Learn about actions');
store.dispatch(addTodo('Learn about reducers');
store.dispatch(addTodo('Learn about store');

store.dispatch(toggleTodo(0));
store.dispatch(toggleTodo(1));

store.dispatch(setVisibilityFilter(VisibilityFilters.SHOW_COMPLETED));

/** Unregistering */
unsubscribe();
```

### Source Code

```js
/** index.js */
import { createStore } from 'redux';
import todoApp from './reducers';

let store = createStore(todoApp);
```
