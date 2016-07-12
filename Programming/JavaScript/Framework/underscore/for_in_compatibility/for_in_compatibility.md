## Compatibility problems of `for ... in ` [Back](./../underscore.md)

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
// Keys in IE < 9 that won't be iterated by `for key in ...` and thus missed.
// IE < 9 下 不能用 for key in ... 来枚举对象的某些 key
// 比如重写了对象的 `toString` 方法，这个 key 值就不能在 IE < 9 下用 for in 枚举到
// IE < 9，{toString: null}.propertyIsEnumerable('toString') 返回 false
// IE < 9，重写的 `toString` 属性被认为不可枚举
var hasEnumBug = !{toString: null}.propertyIsEnumerable('toString');
```

Besides, underscore.js has listed out all the familiar situation in the set `nonEnumerableProps`.

```js
// IE < 9 下不能用 for in 来枚举的 key 值集合
var nonEnumerableProps = ['valueOf', 'isPrototypeOf', 'toString', 'propertyIsEnumerable', 'hasOwnProperty', 'toLocaleString'];
```

