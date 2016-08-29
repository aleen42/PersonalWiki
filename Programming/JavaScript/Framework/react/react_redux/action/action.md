## Actions [Back](./../react_redux.md)

Actions are plain JavaScript objects. Actions must have a `type` property that indicates the type of action being performed.

```js
const ADD_TODO = 'ADD_TODO';

let actions = {
    type: ADD_TODO,
    text: 'Add item to the todo list`
};
```

The structure of actions is up to you to define, and as a recommendation, we can see how a Flux Standard Actions is defined:

```js
const ADD_TODO = 'ADD_TODO';

let actions = {
    type: ADD_TODO,
    payload: {
        text: 'Add item to the todo list`
    }
};
```

An action **MUST**:

- be a plain JavaScript object with notation `{}` to define.
- have a `type` property.

An action **MAY**:

- have a `error` property.
- have a `payload` property.
- have a `meta` property.

An action **MUST NOT** include properties other than `type`, `error`, `payload`, and `meta`.