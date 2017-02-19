## Certain object functions like `pick()` and `create()` [Back](./../underscore.md)

`_.pick()` is used to pick up some specific key-value pairs from an object. For example:

```js
_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, 'name', 'age'); /** => {name: 'moe', age: 50} */

_.pick({name: 'moe', age: 50, userid: 'moe1'}, ['name', 'age']);
=> {name: 'moe', age: 50}

_.pick({name: 'moe', age: 50, userid: 'moe1'}, function(value, key, object) {
  return _.isNumber(value);
});
=> {age: 50}
```
