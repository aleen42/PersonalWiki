## False in JSX [Back](./../react.md)

In React, `false` renders different things in different situation:

as `id="false"`:

```jsx
ReactDOM.render(
    <div id={false} />,
    document.getElementById('content')
);
```

as string input value:

```jsx
ReactDOM.render(
    <input value={false} />,
    document.getElementById('content')
);
```

as no child:

```jsx
ReactDOM.render(
    <div>{false}</div>,
    document.getElementById('content')
);
```

The reason why this one does not render as the string `"false"` or as a `div` child is to allow the more common use-case: `<div>{x > 1 && 'You have more than one item'}</div>`.