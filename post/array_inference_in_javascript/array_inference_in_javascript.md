## [轉載] Javascript中判斷數組的正確姿勢 [Back](./../post.md)

> - Author: [hanzichi · 韩子迟](https://github.com/hanzichi)
> - Origin: http://www.cnblogs.com/zichi/p/5103842.html
> - Time: Jan, 5th, 2016

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

a.htm 代码：

```html
<script>
    window.a = [1, 2, 3];
</script>
```

我们看到 index.htm 代码中，变量 a 确实是一个数组，但是 a instanceof Array 的结果却是 false。

这是因为每个 frame 都有一套自己的执行环境，跨 frame 实例化的对象彼此不共享原型链。如果打印 a instanceof window.frames[0].Array，那么结果就是 true 了。

特性嗅探？

```js
var a = [0, 1, 2];

if (a.sort) {
    // 是数组
}
```

也不靠谱，万一某个对象正好有值为 sort 的 key 呢？

```js
var a = {sort: 'me'};

if (a.sort) {
    // 数组？
    // 其实我真的不是数组
}
```

正确的姿势是使用 [Object.prototype.toString()](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Object/toString) 判断：

```js
var a = [0, 1, 2];
console.log(Object.prototype.toString.call(a) === '[object Array]'); // true
```

事实上，这也是一些类库进行数组（甚至其他类型）判断的主流方式。

比如在 jQuery 中进行数组判断的相关代码（PS：摘自 jQuery 1.10.1，最近版本的 jQuery 只保留了 Array.isArray()，没有对不支持 ES5 的浏览器做兼容）：

```js
isArray: Array.isArray || function( obj ) {
    return jQuery.type(obj) === "array";
},

type: function( obj ) {
    if ( obj == null ) {
        return String( obj );
    }
    return typeof obj === "object" || typeof obj === "function" ?
        class2type[ core_toString.call(obj) ] || "object" :
        typeof obj;
},

jQuery.each("Boolean Number String Function Array Date RegExp Object Error".split(" "), function(i, name) {
    class2type[ "[object " + name + "]" ] = name.toLowerCase();
});
```

代码很清晰，如支持原生的 Array.isArray()，则直接判断，不支持的话调用 toString() 进行判断。同时可以看到很多其他类型变量的判断也是基于 toString() 方法。当然这里说的 toString() 均是 Object 原型链上的 toString() 方法。

```js
console.log(Object.prototype.toString.call(10));  // [object Number]
console.log(Object.prototype.toString.call('hello')); // [object String]
console.log(Object.prototype.toString.call(true));  // [object Boolean]
console.log(Object.prototype.toString.call([]));  // [object Array]
console.log(Object.prototype.toString.call({}));  // [object Object]
console.log(Object.prototype.toString.call(function(){}));  // [object Function]
console.log(Object.prototype.toString.call(/a/g));  // [object RegExp]
console.log(Object.prototype.toString.call(null));  // [object Null]
console.log(Object.prototype.toString.call(undefined)); // [object Undefined]
console.log(Object.prototype.toString.call(new Date())); // [object Date]
```

Object.prototype.toString() 为何能返回这样类型的字符串？

ECMA-262：

> Object.prototype.toString( ) When the toString method is called, the following steps are taken:

> 1. Get the [[Class]] property of this object.
> 2. Compute a string value by concatenating the three strings "[object ", Result (1), and "]".
> 3. Return Result (2)

上面的规范定义了 Object.prototype.toString 的行为：首先，取得对象的一个内部属性[[Class]]，然后依据这个属性，返回一个类似于 "[object Array]" 的字符串作为结果（[[]]用来表示语言内部用到的、外部不可直接访问的属性，称为 "内部属性"）。利用这个方法，再配合 call，我们可以取得任何对象的内部属性 [[Class]]，然后把类型检测转化为字符串比较，以达到我们的目的。还是先来看看在 ECMA 标准中 Array 的描述吧：

> new Array([ item0[, item1 [,…]]]) 

> The [[Class]] property of the newly constructed object is set to “Array”.

所以 Javascript 中判断数组的函数可以这样写：

```js
function isArray(a) {
    Array.isArray ? Array.isArray(a) : Object.prototype.toString.call(a) === '[object Array]';
}
```