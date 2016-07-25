## Rest Parameters [Back](./../es6.md)

Rest Parameters is similar to Spread Operators, which will also use `...`.

It allows functions to receive uncertained length of arguments:

```js
function (a, b, ...args) {
    /** ... */
}
```

By far, in ES5, we will code like this:

```js
function f(a, b) {
    var args = Array.prototype.slice.all(arguments, f.length);
}
```

With Rest Parameters, we can easily use an array to store rest arguments.

```js
function fLength(...args) {
    console.log(args.length);
}

fLength();          /** => 0    */
fLength(1, 2);      /** => 2    */
fLength(1, 2, 3);   /** => 3    */
```