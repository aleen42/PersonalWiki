## Array-like Objects [Back](./../underscore.md)

In JavaScript, we will always know that all the things are constructed as objects, and so-called array-like objects means the kind of objects which is like an array, of which `arguments` is an example.

For this kind of objects, we can access items within them through using operators `[]`, and we can also get the length of this objects by accessing the property of `length`. However, they are always not supported for using operations of an array like `Array.prototype.push()`. So how does array-like objects defined in underscore?

```js
var MAX_SAFE_INTEGER = Math.pow(2, 53) - 1;
var getLength = property('length');

var isArrayLike = function (collection) {
    var length = getLength(collection);
    return typeof length === 'number' && length >= 0 && length <= MAX_SAFE_INTEGER;
};
```

The answer is so simple. If an object is not an array, and it has the property `length`, it's assumed as array-like objects. According to https://tc39.github.io/ecma262/#sec-number.max_safe_integer, `Math.pow(2, 53) - 1` is equal to `Number.MAX_SAFE_INTEGER`, which represents for the maximum of a safe integer value.

As defined, **NodeLists**, **HTML Collections**, and **Strings** all belong to array-like objects.
