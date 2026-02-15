## Spread Operator [Back](./../es6.md)

In ES6, Spread Operator `...` is used to spread an array into more than one arguments:

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

But in ES6, you can code like this:

```js
function myFunction(v, w, x, y, z) {}

var args = [0, 1];
myFunction(-a, ...args, 2, ...[3]);
```

### Powerful Array Literal

With Spread Operator, we can code less to add attributes to an array:

```js
var parts = ['shoulder', 'knee'];
var body = ['head', ...parts, 'legs'];  /** => ['head', 'shoulder', 'knee', legs'] */
```