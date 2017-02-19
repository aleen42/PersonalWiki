## How to find items in an array [Back](./../underscore.md)

Before discussing about this topic, we have been used to using [`Array.prototype.indexOf()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/indexOf) or [`Array.prototye.findIndex()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/findIndex) to find an item in an array. Similarly, underscore has also implemented some methods for you to do the same thing like `_.findIndex()`, `_.findLastIndex()`, `_.indexOf()`, `_.lastIndexOf()`, and `_.sortIndex()`.

Firstly, it's easy to know that both `_.findIndex()` and `_.findLastIndex()` are used to find items in an array with given conditions (functions). Take the following case as an example:

```js
var arr = [1, 3, 5, 2, 4, 6];

var isEven = function(num) {
    return !(num & 1); /** `num & 1` is same as `num % 2 === 1` */
};

var idx = _.findIndex(arr, isEven); /** => 3 */
```

As we can see, the method `_.findIndex()` will return the element which has matched the given condition. Conversely, `_.findLastIndex()` is used to find the last element which has matched the conditions which you provide.

To implement such two familiar functions, underscore has create a so called predicate function to decide how to search: positive or negative.

```js
/**
 * Generator function to create the findIndex and findLastIndex functions
 * dir === 1 means to find in a positive sequence
 * dir === -1 means to find in a negative sequence
 */
function createPredicateIndexFinder(dir) {
    /** return a closure function */
    return function(array, predicate, context) {
        predicate = cb(predicate, context);
        
        var length = getLength(array);
        
        /** set the start position according to dir */
        var index = dir > 0 ? 0 : length - 1;
        
        for (; index >= 0 && index < length; index += dir) {
          /** return the index if matched */
          if (predicate(array[index], index, array)) return index;
        }
        
        /** return -1 if nothing is found */
        return -1;
    };
}

// Returns the first index on an array-like that passes a predicate test
// 从前往后找到数组中 `第一个满足条件` 的元素，并返回下标值
// 没找到返回 -1
// _.findIndex(array, predicate, [context]) 
_.findIndex = createPredicateIndexFinder(1);

// 从后往前找到数组中 `第一个满足条件` 的元素，并返回下标值
// 没找到返回 -1
// _.findLastIndex(array, predicate, [context]) 
_.findLastIndex = createPredicateIndexFinder(-1);

```