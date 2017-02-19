## Certain object functions like `pick()` and `create()` [Back](./../underscore.md)

`_.pick()` is used to pick up some specific key-value pairs from an object. For example:

```js
_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, 'name', 'age'); /** => {name: 'moe', age: 50} */

_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, ['name', 'age']); /** => {name: 'moe', age: 50} */

_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, function (value, key, object) {
    return _.isNumber(value);
}); /** => {age: 50} */
```

As we can see, `_.pick()` will receive an object as the first parameter, while the second one has three situations: **Function**, **Array** or **Separative Parameters**.

Let's see how underscore handle those three conditions smartly.

```js
/** if the second parameter is a function */
if (_.isFunction(oiteratee)) {
  keys = _.allKeys(obj);
  iteratee = optimizeCb(oiteratee, context);
}
```