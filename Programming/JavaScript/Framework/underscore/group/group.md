## Group [Back](./../underscore.md)

`group()` is an internal function in underscore, which is mainly used to implement three APIs: `_.groupBy()`, `_.indexBy()`, and `_.countBy()`.

Firstly, the following snippet has described how to use `_.groupBy()` to group an array according to some conditions:

```js
_.groupBy([1.1, 1.2, 2.1], function (num) {
    return Math.floor(num);
}); /** => { 1: [1.1, 1.2], 2: [2.1] } */

_.groupBy(['one', 'two', 'three'], 'length');
/** => { 3: ['one', 'two'], 5: ['three'] } */
```

It's apparent that the second parameters passed to the method has decided how to group a given array. Without looking at the implementation of underscore, we can also easily complete it by us:

```js
function groupBy(arr, conditions) {
    /** closuren */
    return function () {
        /** to return an object */
        var result = {};
        
        /** if the `conditions` is a property name */
        if (Object.prototype.toString.call(conditions) === '[object String]') {
            /** override conditions */
            conditions = function () {
                return conditions;
            };
        }
        
        /** iterate the array */
        for (var i = 0, len = arr.length; i < len; i++) {
            var key = condition(arr[i]);
            
            if (result[key] === void 0) {
                result[key] = [];
            }
            
            result[key].push(arr[i]);
        }
    };
}
```
