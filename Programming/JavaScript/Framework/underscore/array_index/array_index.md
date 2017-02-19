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