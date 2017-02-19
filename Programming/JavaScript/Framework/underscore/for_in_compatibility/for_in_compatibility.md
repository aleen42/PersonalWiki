## Compatibility problems of `for ... in` [Back](./../underscore.md)

As we known, `for ... in` will only loop through all the **enumerable attributes**. Objects created by the inner constructors of Array and Object will inherit all the non-enumerable attributes like `indexOf()` from String, or `toString()` from Object. `for ... in` will iterate to loop through all the enumerable attributes of objects and attributes inherited from their constructors. (include overridden built-in attributes)

```js
var obj = {
    name: 'hanzichi',
    age: 30
};

for (var k in obj) {
    console.log(k, obj[k]);
}

/** 
 * output:
 *  => name hanzichi
 *  => 30
 */
```

However, there is a compatibility problem in IE8 (Apparently, IE8 has treated `toString` as a non-enumerable attribute, even if it's overridden):

```js
var obj = { toString: 'hanzichi' };

for (var k in obj) {
    alert(k);
}

/**
 * output:
 *  => toString (Chrome)
 *  => nothing hanppen in IE*
 */
```

Therefore, in underscore.js, there is a method named `hasEnumBug` to get bug from IE8:

```js
/**
 * Keys in IE < 9 that won't be iterated by `for key in ...` and thus missed.
 * And use `toString` to judge whether it can be overriden */
var hasEnumBug = !{ toString: null }.propertyIsEnumerable('toString');
```

Besides, underscore.js has listed out all the familiar situation in the set `nonEnumerableProps`.

```js
// IE < 9 下不能用 for in 来枚举的 key 值集合
var nonEnumerableProps = ['valueOf', 'isPrototypeOf', 'toString', 'propertyIsEnumerable', 'hasOwnProperty', 'toLocaleString'];
```

If some has been ignored, it will also provide a method used for collecting, named `collectNonEnumProps`.

```js
function collectNonEnumProps(obj, keys) {
    var nonEnumIdx = nonEnumerableProps.length;
    var constructor = obj.constructor;

    // proto 是否是继承的 prototype
    var proto = (_.isFunction(constructor) && constructor.prototype) || ObjProto;

    // Constructor is a special case.
    // `constructor` 属性需要特殊处理
    // 如果 obj 有 `constructor` 这个 key
    // 并且该 key 没有在 keys 数组中
    // 存入数组
    var prop = 'constructor';
    if (_.has(obj, prop) && !_.contains(keys, prop)) keys.push(prop);
    
    // nonEnumerableProps 数组中的 keys
    while (nonEnumIdx--) {
        prop = nonEnumerableProps[nonEnumIdx];
        // prop in obj 应该肯定返回 true 吧？是否不必要？
        // obj[prop] !== proto[prop] 判断该 key 是否来自于原型链
        if (prop in obj && obj[prop] !== proto[prop] && !_.contains(keys, prop)) {
            keys.push(prop);
        }
    }
}
```

After overriding all the attributes, keys can be gotten under IE 9. However, there are still a doubt why handling constructor specially.