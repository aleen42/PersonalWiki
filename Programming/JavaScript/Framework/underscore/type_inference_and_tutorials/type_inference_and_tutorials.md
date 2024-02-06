## Common type inference(類型判斷) and some useful tutorials [Back](./../underscore.md)

### Type Inference(類型判斷)

#### Array

Firstly, we will talk about the type inference of arrays. And in my post, ["Javascript中判断数组的正确姿势"](./../../../../../post/array_inference_in_javascript/array_inference_in_javascript.md), I have done an analysis for different kinds of ways in inferring about their advantages/disadvantages.

Here I have given the right code:

```js
function isArray(a) {
    Array.isArray ? Array.isArray(a) : Object.prototype.toString.call(a) === '[object Array]';
}
```

While underscore has given the following code:

```js
/** 
 * Is a given value an array?
 * Delegates to ECMA5's native Array.isArray
 */
_.isArray = nativeIsArray || function(obj) {
    return toString.call(obj) === '[object Array]';
};
```

`nativeIsArray` has been pointed to the method `Array.isArray` in ES5, while `toString` has been pointed to the method `Object.prototype.toString`.

#### Object

In underscore, both **function** and **object variables** are treated as an object, only without **null**.

```js
/**
 * Is a given variable an object?
 * An object can be also a function */
 */
_.isObject = function(obj) {
    var type = typeof obj;
    return type === 'function' || type === 'object' && !!obj;
};
```

#### Arguments, Function, String, Number, Date, RegExp, Error

All of those type can be inferred by calling `Object.prototype.toString.call`:

```js
// Add some isType methods: isArguments, isFunction, isString, isNumber, isDate, isRegExp, isError.
// 其他类型判断
_.each(['Arguments', 'Function', 'String', 'Number', 'Date', 'RegExp', 'Error'], function(name) {
    _['is' + name] = function(obj) {
        return toString.call(obj) === '[object ' + name + ']';
    };
});
```

However, `isArguments` will return `[object Object]` under IE 9, so we can infer by checking existence of the attribute `callee`. You know, `arguments.callee` can return the method of current `arguments`.

```js
/**
 * Define a fallback version of the method in browsers (ahem, IE < 9), where
 * there isn't any inspectable "Arguments" type.
 */
if (!_.isArguments(arguments)) {
    _.isArguments = function(obj) {
        /** If it's under IE 9, then to judge whetehr it has the property called `callee` */
        return _.has(obj, 'callee');
    };
}
```

### Utility Class Inference(工具類判斷)

#### DOM Elements

You can just infer an element whether it's a DOM element by ensuring that it's not a `null` and `nodeType` is 1:

```js
// Is a given value a DOM element?
_.isElement = function(obj) {
    /** make sure object is not `null` and the property `nodeType` of this object is `1` */
    return !!(obj && obj.nodeType === 1);
};
```

#### NaN

NaN has belonged to **Number** type, and `Object.prototype.toString.call(NaN)` should be `[object Number]`. Besides, NaN is not equal to itself, so we can infer it like this: (Some bugs, see [#13](https://github.com/hanzichi/underscore-analysis/issues/13))

```js
/**
 * Is the given value `NaN`? (NaN is the only number which does not equal itself).
 * NaN is a Number object which is not equal to itself
 */
_.isNaN = function(obj) {
    return _.isNumber(obj) && obj !== +obj;
};
```

*Notice that: isNaN has been changed to the native method `isNaN`, which will also return true for many other not-number values, such as `undefined`. That means:*

```js
console.log(isNaN(undefined));      /** => true     */
console.log(_.isNaN(undefined));    /** => false    */
```

*Therefore, the new _.isNaN has been modified like this:*

```js
_.isNaN = function(obj) {
    return _.isNumber(obj) && isNaN(obj);  
};
```

*Why adding a `+` before the object? The answer is clear after running the fllowing code:*

```js
var a = new Number(NaN);

console.log(a !== a);               /** => false    */
console.log(a !== +a);              /** => true     */
```

