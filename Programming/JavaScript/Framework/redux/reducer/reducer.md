## Reducers [Back](./../redux.md)

Reducers are used to describe how state changes in an application.

`Reducer<S, A> => S`

### Desigining the State Shape

In Redux, all application state is stored as a single object. Therefore, it's recommended by official documents to think of an application's state shape before writing any code.

For our todo App, we are going to store two different things:

- The currently selected visibility filter
- The actual list of todos

### Handling Actions

Now that we've decided what our state object looks like, we're ready to write a reducer for it. The reducer is a pure function that takes the previous state and an action, and returns the next state.

It's very important that the reducer stays pure. Things you should **NEVER** do inside a reducer:

- Mutate its arguments;
- Perform side effects like API calls and routing transitions;
- Call non-pure functions, e.g. `Date.now()` or `Math.random()`.

Just remember that **Given the same arguments, it should calculate the next state and return it. No surprises. No side effects. No API calls. No mutations. Just a calculation.**

```js
import { VisibilityFilters } from './actions.js';

const initialState = {
    visibilityFilter: VisibilityFilters.SHOW_ALL,
    todos: []
};

function todoApp(state, action) {
    if (typeof state === 'undefined') {
        return initialState;
    }
    
    /**
     * For now, don‘t handle any actions
     * and just return the state given to us.
     */
    return state;
}

/** In ES6, we can set default arguments like this */
function todoApp(state = initialState, action) {
    /**
     * For now, don‘t handle any actions
     * and just return the state given to us.
     */
    return state;
}
```

For handling `SET_VISIBILITY_FILTER`, we can just change `visibilityFilter` on the state like this:

```js
function todoApp(state = initialState, action) {
    switch (action.type) {
    case SET_VISIBILITY_FILTER:
        return Object.assign({}, state, { visibilityFilter: action.payload.filter });
    default:
        return state;
    }
}
```

Note that:

1. **Do not mutate the `state`**
2. **Return the previous `state` in the default case**
3. **`Object.assign()` is not well supported and we can use other methods like `_.assign()` from underscore**

For handling `ADD_TODO`, we are going to add item into the todos array in the state:

```js
function todoApp(state = initialState, action) {
    switch (action.type) {
    case SET_VISIBILITY_FILTER:
        return Object.assign({}, state, { visibilityFilter: action.payload.filter });
    case ADD_TODO:
        return Object.assign({}, state, {
            todos: [
                /** store previous todos item */
                ...state.todos,
                {
                    text: action.payload.text,
                    completed: false
                }
            ]
        });
    default:
        return state;
    }
}
```

For handling `TOGGLE_TODO`, we are going to change completed status of this item with its index:

```js
function todoApp(state = initialState, action) {
    switch (action.type) {
    case SET_VISIBILITY_FILTER:
        return Object.assign({}, state, { visibilityFilter: action.payload.filter });
    case ADD_TODO:
        return Object.assign({}, state, {
            todos: [
                /** store previous todos item */
                ...state.todos,
                {
                    text: action.payload.text,
                    completed: false
                }
            ]
        });
    case TOGGLE_TODO:
        return Object.assign({}, state, {
            todos: state.todos.map((item, index) => {
                if (index === action.payload.index) {
                    /**
                     * if toggle index has been matched
                     * change completed attribute and return a new object
                     */
                    return Object.assign({}, item, {
                        completed: !item.completed
                    });
                }
                
                return item;
            })
        });
    default:
        return state;
    }
}
```

### Reducer Composition (分解)

Because both `ADD_TODO` and `TOGGLE_TODO` will update the todos array in the state, we can just split updating `todos` into a separate function like this:

```js
function todos(state = [], action) {
    switch(action.type) {
    case ADD_TODO:
        return [
            /** store previous todos item */
            ...state,
            {
                text: action.payload.text,
                completed: false
            }
        ];
    case TOGGLE_TODO:
        return state.map((item, index) => {
            if (index === action.payload.index) {
                /**
                 * if toggle index has been matched
                 * change completed attribute and return a new object
                 */
                return Object.assign({}, item, {
                    completed: !item.completed
                });
            }
            
            return item;
        });
    }
}

function todoApp(state = initialStat, action) {
    switch (action.type) {
    case SET_VISIBILITY_FILTER:
        return Object.assign({}, state, { visibilityFilter: action.payload.filter });
    case ADD_TODO:
    case TOGGLE_TODO:
        return Object.assign({}, state, {
            todos: todos(state.todos, action)
        });
    default:
        return state;
    }
}
```

Of course, we can also extract `visibilityFilter` like this:

```js
function visibilityFilter(state = SHOW_ALL, action) {
    switch(action.type) {
    case SET_VISIBILITY_FILTER:
        return action.payload.filter;
    default:
        return state;
    }
}

function todos(state = [], action) {
    switch(action.type) {
    case ADD_TODO:
        return [
            /** store previous todos item */
            ...state,
            {
                text: action.payload.text,
                completed: false
            }
        ];
    case TOGGLE_TODO:
        return state.map((item, index) => {
            if (index === action.payload.index) {
                /**
                 * if toggle index has been matched
                 * change completed attribute and return a new object
                 */
                return Object.assign({}, item, {
                    completed: !item.completed
                });
            }
            
            return item;
        });
    }
}

function todoApp(state = initialStat, action) {
    return {
        visibilityFilter: visibilityFilter(state.visibilityFilter, action),
        todos: todos(state.todos, action)
    };
}
```

Finally, Redux provides a utility called `combineReducers()` that does the same logic:

```js
import { combineReducers } from 'redux';

function visibilityFilter(state = SHOW_ALL, action) {
    switch(action.type) {
    case SET_VISIBILITY_FILTER:
        return action.payload.filter;
    default:
        return state;
    }
}

function todos(state = [], action) {
    switch(action.type) {
    case ADD_TODO:
        return [
            /** store previous todos item */
            ...state,
            {
                text: action.payload.text,
                completed: false
            }
        ];
    case TOGGLE_TODO:
        return state.map((item, index) => {
            if (index === action.payload.index) {
                /**
                 * if toggle index has been matched
                 * change completed attribute and return a new object
                 */
                return Object.assign({}, item, {
                    completed: !item.completed
                });
            }
            
            return item;
        });
    }
}

/**
 * How to use combineReducers ?
 *
 * More explicitly, combineReducers will convert an input object into a reducer like this
 * 
 * const reducer = combineRedcers({
 *      a: proccessA,
 *      b: withB,
 *      c
 * });
 * 
 * function reducer(state = {}, action) {
 *      return {
 *          a: processA(state.a, action),
 *          b: withB(state.b, action),
 *          c: c(state.c, action)
 *      };
 * }
 */

const todoApp = combineReducers({
    visibilityFilter,
    todos
});

export default todoApp;
```

### Source Code

```js
/** reducers.js */
import { combineReducers } from 'redux';
import { ADD_TODO, TOGGLE_TODO, SET_VISIBILITY_FILTER, VisibilityFitlers } from './actions.js';

const { SHOW_ALL } = VisibilityFilters;

function visibilityFilter(state = SHOW_ALL, action) {
    switch(action.type) {
    case SET_VISIBILITY_FILTER:
        return action.payload.filter;
    default:
        return state;
    }
}

function todos(state = [], action) {
    switch(action.type) {
    case ADD_TODO:
        return [
            /** store previous todos item */
            ...state,
            {
                text: action.payload.text,
                completed: false
            }
        ];
    case TOGGLE_TODO:
        return state.map((item, index) => {
            if (index === action.payload.index) {
                /**
                 * if toggle index has been matched
                 * change completed attribute and return a new object
                 */
                return Object.assign({}, item, {
                    completed: !item.completed
                });
            }
            
            return item;
        });
    }
}

const todoApp = combineReducers({
    visibilityFilter,
    todos
});

export default todoApp;
```