## Common Type Inference(類型判斷) and some useful tutorials [Back](./../underscore.md)


## Type Inference(類型判斷)

Firstly, we will talk about the type inference of arrays. And in my post, ["Javascript中判断数组的正确姿势"](http://www.cnblogs.com/zichi/p/5103842.html), I have done an analysis for different kinds of ways in inferring about their advantages/disadvantages.

Here I have given the right code:

```js
function isArray(a) {
    return Array.isArray ? Array.isArray(a) : Object.prototype.toString.call(a) === '[object Array]';
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

`nativeIsArray` means the method of `Array.isArray` in ES5.