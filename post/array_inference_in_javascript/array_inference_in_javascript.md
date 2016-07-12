## [轉載] Javascript中判斷數組的正確姿勢 [Back](./../post.md)

> - Author: [hanzichi · 韩子迟](https://github.com/hanzichi)
- Origin: http://www.cnblogs.com/zichi/p/5103842.html
- Time: Jan, 5th, 2016

在 Javascript 中，如何判断一个变量是否是数组？

最好的方式是用 ES5 提供的 `Array.isArray()` 方法（毕竟原生的才是最屌的）：

```js
var a = [0, 1, 2];
console.log(Array.isArray(a));  // true
```

但是鉴于低版本 IE 不支持 ES5，如需兼容，需要想想别的办法。

`typeof`？

我们都知道，数组是特殊的对象，所以数组的 typeof 结果也是 object，而因为 null 的结果也是 object，所以如需用 typeof 运算符来判断数组，需要这么写：

```js
var a = [0, 1, 2];
// 是 object 同时排除 null、排除纯对象
console.log(typeof a === 'object' && a !== null && Object.prototype.toString.call(a) !== '[object Object]');  // true
```

`instanceof`？

来回忆下 instanceof 运算符的使用方式。a instanceof b，如果返回 true，表示 a 是 b 的一个实例。那么如果 a instanceof Array 返回 true，是不是就说明 a 是 数组类型呢？跟 instanceof 师出同门的还有 constructor，是否同样可以判断呢？

```js
var a = [0, 1, 2];
console.log(a instanceof Array);  // true 就是数组？
console.log(a.constructor === Array); // true 数组？
```

答案是否定的，需要注意嵌套 frame 的情况。

index.htm 代码：

```html
<iframe src='a.htm'></iframe>
<script>
    window.onload = function() {
      var a = window.frames[0].a;
      console.log(a instanceof Array);  // false
      console.log(a.constructor === Array);  // false
    };
</script>
```