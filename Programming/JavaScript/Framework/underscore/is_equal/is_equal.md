## How to compare the equality of two elements [Back](./../underscore.md)

In underscore, there is a method called `_.isEqual()` to judge whether an element is equal to another. Before analyzing this more complicated function, which has been implemented with around hundreds of lines, I would like to discuss when an element is actually equal to another. For example, `1` should be equal to `new Number(1)`, and `[1]` is also equal to `[1]` even if they are two different arrays.

For the expression `a === b`, there are two situations resulting in `true`:

1. both `a` and `b` are primitive types, having the same value at the same time.
2. both `a` and `b` are reference types, having the same target to reference.

If this expression returns `true`, we can say that `a` is 99% likely equal to the element `b`, except a special case. According to the article  http://wiki.ecmascript.org/doku.php?id=harmony:egal, people think that `0` is actually not equal to `-0`, but in JavaScript, `0 === -0` will return unexpected `true`.

```js
/**
 * Identical objects are equal. `0 === -0`, but they aren't identical.
 * See the [Harmony `egal` proposal](http://wiki.ecmascript.org/doku.php?id=harmony:egal).
 */
if (a === b) {
    return a !== 0 || 1 / a === 1 / b;
}
```

What if one of `a` and `b` is `null` or `undefined`:

```js
/** A strict comparison is necessary because `null == undefined`. */
if (a == null || b == null) {
    return a === b;
}
```

If `a` is a `RegExp` object, while `b` is a `String`, then undercore will convert them into both `String` to judge whether they are equal:

```js
var a = /a/;
var b = new RegExp("a");

var _a = '' + a; // => /a/
var _b = '' + b; // => /a/

return _a === _b; // => true
```

In the case when `a` and `b` are both `Number` objects, underscore will handle a special case in which `NaN` is only equal to `NaN` but not any other `Number` objects:

```js
/**
 * `NaN`s are equivalent, but non-reflexive.
 * Object(NaN) is equivalent to NaN
 * If `+a !== +a` returns true, it means that
 * a is NaN, and then just check whether b is
 * also NaN.
 */
if (+a !== +a) {
    return +b !== +b;
}

/**
 * An `egal` comparison is performed for other numeric values.
 * If a is zero, then check `1 / +a === 1 / b` to make sure b is not `-0`
 * If a is not zero, thenjust check `+a === +b`
 */
return +a === 0 ? 1 / +a === 1 / b : +a === +b;
```

How about `Date` and `Boolean` objects?

```js
return +a === +b;
```

For the `Array` and `Object`, underscore has adopted a recursive comparison to judge. When there is a various key-value pair, then return `false`.