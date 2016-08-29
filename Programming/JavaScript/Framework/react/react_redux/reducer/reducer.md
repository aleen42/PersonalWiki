## Reducers [Back](./../react_redux.md)

Reducers are used to describe how state changes in an application.

`Reducer<S, A> => S`

### Desigining the State Shape

In Redux, all application state is stored as a single object. Therefore, it's recommended by official documents to think of an application's state shape before writing any code.

For our todo App, we are going to store two different things:

- The currently selected visibility filter
- The actual list of todos
