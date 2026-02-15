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

The difference between these two methods is that `_.without()` will accept single values separated by a comma, while `_.difference()` will accept values constructed with arrays. Therefore, if we have implemented `_.difference()`, we can just implement `_.without()` by calling `_.difference()` after putting arguments into an array:

```js
/** _.difference(array, *others) */
_.difference = function(array) {
    /**
     * because the `strict` property has accepted `true`, an argument like 10 when 
     * calling _.difference(arr, [1, 2], 10); will be ignored
     */
    var rest = flatten(arguments, true, true, 1);
    
    /** use `_.filter()` to filter out */
    return _.filter(array, function(value) {
        return !_.contains(rest, value);
    });
};

_.without = function(array) {
    /** put arguments except the given array into an array */
    return _.difference(array, slice.call(arguments, 1));
};
```

How about implementing it in a reversed way (we have to consider more about arguments when calling both of them):

```js
_.without = function(array) {
    var rest = (this == 'difference') ? _.flatten(arguments, false, false, 1) : Array.prototype.slice.call(arguments, 1);
    
    return _.filter(array, function(value) {
        return !_.contains(rest, value);
    });
};

_.difference = function(array) {
    /** filter out arguments which is not an array firstly */
    var args = _.flatten(arguments, true, true, 1);

    /**
     * let the method `_.without()` know that whether it's called by `_.difference()`,
     * if so, then flatten all the arrays from argments,
     * if not, then do not flatten.
     */
    return _.without.apply('difference', args.unshift(array));
};
```
