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
    text: 'Add item to the todo list`
};
```

