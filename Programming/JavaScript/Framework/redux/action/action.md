## Actions [Back](./../redux.md)

### Definition

Actions are plain JavaScript objects. Actions must have a `type` property that indicates the type of action being performed.

```js
const ADD_TODO = 'ADD_TODO';

let actions = {
    type: ADD_TODO,
    text: 'Add item to the todo list'
};
```

The structure of actions is up to you to define, and as a recommendation, we can see how a Flux Standard Actions is defined:

```js
const ADD_TODO = 'ADD_TODO';

let actions = {
    type: ADD_TODO,
    payload: {
        text: 'Add item to the todo list'
    }
};
```

An action **MUST**:

- be a plain JavaScript object with notation `{}` to define.
- have a `type` property.

    > The `type` of an action identifies to the consumer the nature of the action that has occurred. Two actions with the same type **MUST** be strictly equivalent (using `===`). By convention, `type` is usually string constant or a Symbol.

An action **MAY**:

- have a `error` property.

    > The optional `error` property **MAY** be set to `true` if the action represents an error.

    > An action whose `error` is `true` is analogous to a rejected Promise. By convention, the payload **SHOULD** be an error object.

    > If `error` has any other value besides `true`, including `undefined` and `null`, the action **MUST NOT** be interpreted as an error.

- have a `payload` property.

    > The optional `payload` property **MAY** be any type of value. It represents the payload of the action. Any information about the action that is not the `type` or status of the action should be part of the payload field.

    > By convention, if `error` is `true`, the `payload` **SHOULD** be an error object. This is akin to rejecting a promise with an error object.
    
- have a `meta` property.

    > The optional `meta` property **MAY** be any type of value. It is intended for any extra information that is not part of the payload.

An action **MUST NOT** include properties other than `type`, `error`, `payload`, or `meta`.

### Creators

**Action Creators** are exactly that functions that create actions.

In Redux, Action Creators simply return an action:

```js
const ADD_TODO = 'ADD_TODO';

function addTodo(text) {
    return {
        type: ADD_TODO,
        payload: {
            text
        }
    };
}
```

And to actually initiate a dispatch by passing the result to the `dispatch()` function:

```js
dispatch(addTodo(text));
```

The `dispatch()` function can be accessed directly from the `store` as `store.dispatch()`, but more likely you'll access it using a helper like react-redux's `connect()`. You can use `bindActionCreators()` to automatically bind many action creators to a `dispatch()` function:

```js
const ADD_TODO = 'ADD_TODO';
const TOGGLE_TODO = 'TOGGLE_TODO'; 

function addTodo(text) {
    return {
        type: ADD_TODO,
        payload: {
            text
        }
    };
}

function toggleTodo(index) {
    return {
        type: TOGGLE_TODO,
        payload: {
            index
        }
    };
}

bindActionCreators({
    addTodo,
    toggleTodo
}, dispatch);
```

Note: Action Creators can also be asynchronous and have side-effects. You can read about [async actions](./../async_action/async_action.md) in the advanced tutorial to learn how to handle AJAX responses and compose action creators into async control flow. **Don't skip ahead to async actions until you've completed the basics tutorial**, as it covers other important concepts that are prerequisite for the advanced tutorial and async actions.

### Sourc Code

```js
/** action js */
export const ADD_TODO = 'ADD_TODO';
export const TOGGLE_TODO = 'TOGGLE_TODO';
export const SET_VISIBILITY_FILTER = 'SET_VISIBILITY_FILTER';

export const VisibilityFilters = {
    SHOW_ALL: 'SHOW_ALL',
    SHOW_COMPLETED: 'SHOW_COMPLETED',
    SHOW_ACTIVE: 'SHOW_ACTIVE'
};

/** Action Creators */
export function addTodo(text) {
    return {
        type: ADD_TODO,
        payload: {
            text
        }
    };
};

export function toggleTodo(index) {
    return {
        type: TOGGLE_TODO,
        payload: {
            index
        }
    };
};

export function setVisibilityFilter(filter) {
    return {
        type: SET_VISIBILITY_FILTER,
        payload: {
            filter
        }
    };
};
```
