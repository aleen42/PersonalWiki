## How to compare the equality of two elements [Back](./../underscore.md)

In underscore, there is a method called `_.isEqual()` to judge whether an element is equal to another. Before analysing this more complicated function, which has been implemented with around hundreds of lines, I would like to discuss when an element is actually equal to another. For example, `1` should be equal to `new Number(1)`, and `[1]` is also equal to `[1]` even if they are two different arrays.

For the expression `a === b`, there are two situations resulting in `true`:

1. both `a` and `b` are primitive types, having the same value at the same time.
2. both `a` and `b` are reference types, having the same target to reference.

If this expression returns `true`, we can say that `a` is 99% likely equal to the element `b`, except a special case. According to the article  http://wiki.ecmascript.org/doku.php?id=harmony:egal, people think that `0` is actually not equal to `-0`, but in JavaScript, `0 === -0` will return unexpected `true`.

```js
// Identical objects are equal. `0 === -0`, but they aren't identical.
// See the [Harmony `egal` proposal](http://wiki.ecmascript.org/doku.php?id=harmony:egal).
if (a === b) {
    return a !== 0 || 1 / a === 1 / b;
}
```

What if one of `a` and `b` is `null` or `undefined`:

```js
// A strict comparison is necessary because `null == undefined`.
if (a == null || b == null) {
    return a === b;
}
```
