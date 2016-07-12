## Common Type Inference(類型判斷) and some useful tutorials [Back](./../underscore.md)


## Type Inference(類型判斷)

Firstly, we will talk about the type inference of arrays. And in my post, ["Javascript中判断数组的正确姿势"](http://www.cnblogs.com/zichi/p/5103842.html), I have done an analysis for different kinds of ways in inferring about their advantages/disadvantages.

Here I have given the right code:

```js
function isArray(a) {
    return Array.isArray ? Array.isArray(a) : Object.prototype.toString.call(a) === '[object Array]';
}
```