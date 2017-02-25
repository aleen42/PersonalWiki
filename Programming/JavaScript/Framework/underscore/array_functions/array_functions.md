## Certain array functions like `compact()`, `difference()`, and `without()` [Back](./../underscore.md)

There are some interesting array functions that will be discussed here like `compact()`, `difference()`, and `without()`.

Firstly, according to the implementation of `_.compact()`, it's not hard to know that this method is always used to filter out `false` from an array.

```js
_.compact = function(array) {
    return _.filter(array, _.identity);
};
```

`_.filter()` is similar to `Array.prototype.filter()`, and it's used to filter out some elements under a given condition, as the function `_.identity` describes. If this function accepts an element of the array and return a `true` value, then the element can be kept into the array.

```js
_.identity = function(value) {
    return value;
};
```

Both `_.without()` and `_.difference()` is used to filter out some elements from an array with given specific values:

```js
var arr = [1, 2, 3, 4, 5];
var result = _.without(arr, 1, 2, 3);
console.log(result); /** => [4, 5] */
```

```js
var arr = [1, 2, 3, 4, 5];
var result = _.difference(arr, [1, 2, 3], [5, 6]);
console.log(result); /** => [4] */
```
