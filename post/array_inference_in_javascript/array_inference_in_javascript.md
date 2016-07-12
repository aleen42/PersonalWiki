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

