## Group [Back](./../underscore.md)

`group()` is an internal function in underscore, which is mainly used to implement three APIs: `_.groupBy()`, `_.indexBy()`, and `_.countBy()`.

Firstly, the following snippet be described how to use `_.groupBy()` to group an array according to some conditions:

```js
_.groupBy([1.1, 1.2, 2.1], function (num) {
    return Math.floor(num);
}); /** => { 1: [1.1, 1.2], 2: [2.1] } */

_.groupBy(['one', 'two', 'three'], 'length');
/** => { 3: ['one', 'two'], 5: ['three'] } */
```
