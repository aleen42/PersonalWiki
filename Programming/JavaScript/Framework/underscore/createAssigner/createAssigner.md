## The internal function: `createAssigner()` [Back](./../underscore.md)

In underscore, you may have to know this important function, which is named `createAssigner()`. Before discussing about what it has done, we may also have to know another three APIs calling this function firstly. They're `_.extend()`, `_.extendOwn()`, and `_.defaults()`.

Firstly, when we want to merge all properties from an object b to an object a, we may remember the function `Object.assign(a, b)`. That's exactly what `_.extend()` has done. And `_.extendOwn()`will only copy own properties of one object to another one. When it comes to `_.defaults()`, it's familiar with `_.extend()`, but what the difference is `_.defaults()` will check whether there are repeated properties while copying. If so, the second property will not override the first one.

For these three APIs, underscore has implemented them all by calling `createAssigner()`:

```js
_.extend = createAssigner(_.allKeys);
_.extendOwn = createAssigner(_.keys);
_.defaults = createAssigner(_.allKeys, true);
```

Then, let's go to have a look at the function they call:

```js
// An internal function for creating assigner functions.
// 有三个方法用到了这个内部函数
// _.extend & _.extendOwn & _.defaults
// _.extend = createAssigner(_.allKeys);
// _.extendOwn = _.assign = createAssigner(_.keys);
// _.defaults = createAssigner(_.allKeys, true);
var createAssigner = function(keysFunc, undefinedOnly) {
    // 返回函数
    // 经典闭包（undefinedOnly 参数在返回的函数中被引用）
    // 返回的函数参数个数 >= 1
    // 将第二个开始的对象参数的键值对 "继承" 给第一个参数
    return function(obj) {
        var length = arguments.length;
        // 只传入了一个参数（或者 0 个？）
        // 或者传入的第一个参数是 null
        if (length < 2 || obj == null) return obj;
        
        // 枚举第一个参数除外的对象参数
        // 即 arguments[1], arguments[2] ...
        for (var index = 1; index < length; index++) {
        // source 即为对象参数
        var source = arguments[index],
        // 提取对象参数的 keys 值
        // keysFunc 参数表示 _.keys 
        // 或者 _.allKeys
        keys = keysFunc(source),
        l = keys.length;
        
        // 遍历该对象的键值对
        for (var i = 0; i < l; i++) {
            var key = keys[i];
            // _.extend 和 _.extendOwn 方法
            // 没有传入 undefinedOnly 参数，即 !undefinedOnly 为 true
            // 即肯定会执行 obj[key] = source[key] 
            // 后面对象的键值对直接覆盖 obj
            // ==========================================
            // _.defaults 方法，undefinedOnly 参数为 true
            // 即 !undefinedOnly 为 false
            // 那么当且仅当 obj[key] 为 undefined 时才覆盖
            // 即如果有相同的 key 值，取最早出现的 value 值
            // *defaults 中有相同 key 的也是一样取首次出现的
            if (!undefinedOnly || obj[key] === void 0) 
                obj[key] = source[key];
            }
        }
        
        // 返回已经继承后面对象参数属性的第一个参数对象
        return obj;
    };
};
```