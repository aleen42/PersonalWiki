## If-Else in JSX [Back](./../react.md)

In React, `if-else` is not work inside JSX.

```jsx
ReactDOM.render(
    <div id={if (condition) { 'msg' } }></div>,
    document.getElementById('content')
)
```

If we code a JSX like the below one, you will find that the converted JavaScript will have something wrong.

```js
ReactDOM.render(
    React.createElement('div', { id: condition ?  'msg' : null }),
    document.getElementById('content')
)
```

A ternary expression (三角表達式) will be a good choice to solve this problem:

```jsx
ReactDOM.render(
    <div id={condition ? 'msg' : null}></div>,
    document.getElementById('content')
)
```

If we code a JSX like the below one, you will find that the converted JavaScript will have something wrong.

```js
ReactDOM.render(
    React.createElement('div', { id: condition ? 'msg' : null }),
    document.getElementById('content')
)
```

Nevertheless, if a ternary expression still cannot fit your case, you can use `if-else` like this:

```jsx
var divElem;

if (condition) {
    divElem = <div id="msg"></div>;
} else {
    divElem = <div></div>;
}

ReactDOM.render(
    divElem,
    document.getElementById('content')
)
```

Prefer to more "inline" aesthetic (美感)? Try to use arrow function of ES6.

```jsx
ReactDOM.render(
    <div id={
        (() => {
            switch (condition) {
                case true:
                    return 'msg';
                default:
                    return null;
            }
        })();
    }></div>,
    document.getElementById('content')
)
```