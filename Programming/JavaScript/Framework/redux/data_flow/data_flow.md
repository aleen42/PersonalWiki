## Data Flow - Data Lifecycle in Redux [Back](./../redux.md)

All data in Redux will obey the following 4 steps:

1. First, you will call `store.dispatch(action)`.
2. Then, the Store you created will call the reducer what you gave `reducer(state, action)`.
3. The root reducer may combine the output of multiple reducers into a single state tree.
4. The Redux Store will finally save the whole state tree returned by the root reducer.
