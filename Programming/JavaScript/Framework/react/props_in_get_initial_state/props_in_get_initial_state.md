## Props in getInitialState Is an Anti-Pattern [Back](./../react.md)

Using props to generate state in `getInitialState` often leads to duplication of "source of truth", i.e. where the real data is. This is because `getInitialState` is only invoked when the component is first created.