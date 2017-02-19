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
_.pick = function(object, oiteratee, context) {
    /** result is the created copy to return */
    var result = {}, obj = object, iteratee, keys;

    /** if object is null then return an empty object */
    if (obj == null) return result;

    /** if the second parameter is a function */
    if (_.isFunction(oiteratee)) {
      keys = _.allKeys(obj);
      iteratee = optimizeCb(oiteratee, context);
    } else {
      // 如果第二个参数不是函数
      // 则后面的 keys 可能是数组
      // 也可能是连续的几个并列的参数
      // 用 flatten 将它们展开
      keys = flatten(arguments, false, false, 1);

      // 也转为 predicate 函数判断形式
      // 将指定 key 转化为 predicate 函数
      iteratee = function(value, key, obj) { return key in obj; };
      obj = Object(obj);
    }

    for (var i = 0, length = keys.length; i < length; i++) {
      var key = keys[i];
      var value = obj[key];
      // 满足条件
      if (iteratee(value, key, obj)) result[key] = value;
    }
    return result;
  };
```