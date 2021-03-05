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

The answer is so simple. If an object has the property `length`, it's assumed as array-like objects. According to https://tc39.github.io/ecma262/#sec-number.max_safe_integer, `Math.pow(2, 53) - 1` is equal to `Number.MAX_SAFE_INTEGER`, which represents for the maximum of a safe integer value.

> Note that: the maximum of the length of an array or an array-like object is `Math.pow(2, 32) - 1`.

As defined, **NodeLists**, **HTML Collections**, and **Strings** all belong to array-like objects.

When it comes to converting them into a real array, the most simple way is to create a new array and push all items into it:

```js
function arrayFrom(collections) {
    var arr = [];
    
    for (var i = 0, len = collections.length; i < len; i++) {
        arr.push(arguments[i]);    
    }
    
    return arr;
}
```

If you don't need to consider the compatibility of older version IE, you can just use `Array.prototype.slice()` to complete it:

```js
function arrayFrom(collections) {
    var arr = Array.prototype.slice.call(collections);
    
    return arr;
}
```

Or we can even use a literal to make it more simple:

```js
function arrayFrom(collections) {
    var arr = [].slice.call(collections);
    
    return arr;
}
```

ES6 has also provided an alternative for you:

```js
function arrayFrom(collections) {
    var arr = Array.from(collections);
    
    return arr;
}
```