## Flatten an array [Back](./../underscore.md)

Flattening an array means to simplify an array with extracting embedded array of another array. The following case has apparently shown us what is flattening an array:

```js
[[[1, 2], [1, 2, 3]], [1, 2]] => [1, 2, 1, 2, 3, 1, 2] /** flatten in a deep way */
[[[1, 2], [1, 2, 3]], [1, 2]] => [[1, 2], [1, 2, 3], 1, 2] /** flatten only one layer */
```

Before analyzing the method `_.flatten()` of underscore, we will have a look at the predicate method `flatten()`:

```js
var flatten = function(input, shallow, strict, startIndex) {
    // ...
};
```

As we can see above, the method has accepted four parameters, of which the `input` is the first one to get a given array. Then, `shallow` is a Boolean value for checking whether to flatten just one layer of the array. `startIndex` is used to set up where to start to flatten.

`strict` is also a Boolean value, but it's hard to understand. If `strict` is given a `true` value, then it means that each flattening will ignore any elements which is not an array. For example:

```js
var ans = flatten([5, 6, [1, 2], [3, 4]], true, true);
console.log(ans); /** => [1, 2, 3, 4] */
```

Therefore, if giving `false` to `shallow` and `true` to `strict` at the same time, the method should always return an empty array.

```js
var flatten = function(input, shallow, strict, startIndex) {
    /**
     * ouput is the array to return
     * idx is a counter
     */
    var output = [], idx = 0;
    
    /** start from a given startIndex or 0 by default */
    for (var i = startIndex || 0, length = getLength(input); i < length; i++) {
        var value = input[i];
        // 数组 或者 arguments
        if (isArrayLike(value) && (_.isArray(value) || _.isArguments(value))) {
            // flatten current level of array or arguments object
            // (!shallow === true) => (shallow === false)
            // 则表示需深度展开
            // 继续递归展开
            if (!shallow) 
                // flatten 方法返回数组
                // 将上面定义的 value 重新赋值
                value = flatten(value, shallow, strict);
            
            // 递归展开到最后一层（没有嵌套的数组了）
            // 或者 (shallow === true) => 只展开一层
            // value 值肯定是一个数组
            var j = 0, len = value.length;
            
            // 这一步貌似没有必要
            // 毕竟 JavaScript 的数组会自动扩充
            // 但是这样写，感觉比较好，对于元素的 push 过程有个比较清晰的认识
            output.length += len;
            
            // 将 value 数组的元素添加到 output 数组中
            while (j < len) {
                output[idx++] = value[j++];
            }
        } else if (!strict) { 
            // (!strict === true) => (strict === false)
            // 如果是深度展开，即 shallow 参数为 false
            // 那么当最后 value 不是数组，是基本类型时
            // 肯定会走到这个 else-if 判断中
            // 而如果此时 strict 为 true，则不能跳到这个分支内部
            // 所以 shallow === false 如果和 strict === true 搭配
            // 调用 flatten 方法得到的结果永远是空数组 []
            output[idx++] = value;
        }
    }
    
    return output;
};
```


