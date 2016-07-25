## Spread Operators [Back](./../es6.md)

In ES6, Spread Operators `...` is used to spread an array into more than one arguments:

```js
/** method call */
myFunction(...args)
```

```js
/** array literal */
[...iteralObject, 4, 5, 6]
```

So far, in ES5, we will use `Function.prototype.apply` to spread an array into more than one arguments:

```js
function myFunction(x, y, z) {}

var args = [0, 1, 2];
myFunction.apply(null, args);
```
