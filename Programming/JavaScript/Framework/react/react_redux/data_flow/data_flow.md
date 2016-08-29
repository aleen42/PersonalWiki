## Data Flow - Data Lifecycle in Redux [Back](./../react_redux.md)

All data in Redux will obey the following 4 steps:

1. First, you will call `store.dispatch(action)`
2. Then, the Store you created will call the reducer what you gae `reducer(state, action)`
