## Common Type Inference(類型判斷) and some useful tutorials [Back](./../underscore.md)


## Type Inference(類型判斷)

### Array

Firstly, we will talk about the type inference of arrays. And in my post, ["Javascript中判断数组的正确姿势"](http://www.cnblogs.com/zichi/p/5103842.html), I have done an analysis for different kinds of ways in inferring about their advantages/disadvantages.

Here I have given the right code:

```js
function isArray(a) {
    Array.isArray ? Array.isArray(a) : Object.prototype.toString.call(a) === '[object Array]';
}
```

While underscore has given the following code:

```js
// Is a given value an array?
// Delegates to ECMA5's native Array.isArray
// 判断是否为数组
_.isArray = nativeIsArray || function(obj) {
    return toString.call(obj) === '[object Array]';
};
```

`nativeIsArray` has been pointed to the method `Array.isArray` in ES5, while `toString` has been pointed to the method `Object.prototype.toString`.

### Object

In underscore, both **function** and **object variables** are treated as an object, only without **null**.

```js
// Is a given variable an object?
// 判断是否为对象
// 这里的对象包括 function 和 object
_.isObject = function(obj) {
    var type = typeof obj;
    return type === 'function' || type === 'object' && !!obj;
};
```