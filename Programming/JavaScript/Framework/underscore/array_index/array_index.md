## How to find items in an array [Back](./../underscore.md)

Before discussing about this topic, we have been used to using [`Array.prototype.indexOf()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/indexOf) or [`Array.prototye.findIndex()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/findIndex) to find an item in an array. Similarly, underscore has also implemented some methods for you to do the same thing like `_.findIndex()`, `_.findLastIndex()`, `_.indexOf()`, `_.lastIndexOf()`, and `_.sortIndex()`.

Firstly, it's easy to know that both `_.findIndex()` and `_.findLastIndex()` are used to find items in an array with given conditions (functions). Take the following case as an example:

```js
var arr = [1, 3, 5, 2, 4, 6];

var isEven = function(num) {
    return !(num & 1); /** `num & 1` is same as `num % 2 === 1` */
};

var idx = _.findIndex(arr, isEven); /** => 3 */
```

As we can see, the method `_.findIndex()` will return the element which has matched the given condition. Conversely, `_.findLastIndex()` is used to find the last element which has matched the conditions which you provide.

To implement such two familiar functions, underscore has create a so called predicate function to decide how to search: positive or negative.

```js
/**
 * Generator function to create the findIndex and findLastIndex functions
 * dir === 1 means to find in a positive sequence
 * dir === -1 means to find in a negative sequence
 */
function createPredicateIndexFinder(dir) {
    /** return a closure function */
    return function(array, predicate, context) {
        predicate = cb(predicate, context);
        
        var length = getLength(array);
        
        /** set the start position according to dir */
        var index = dir > 0 ? 0 : length - 1;
        
        for (; index >= 0 && index < length; index += dir) {
          /** return the index if matched */
          if (predicate(array[index], index, array)) return index;
        }
        
        /** return -1 if nothing is found */
        return -1;
    };
}

/**
 * Returns the first index on an array-like that passes a predicate test
 * _.findIndex(array, predicate, [context])
 */
_.findIndex = createPredicateIndexFinder(1);

/** _.findLastIndex(array, predicate, [context]) */
_.findLastIndex = createPredicateIndexFinder(-1);
```

Then, how about `_.sortIndex()`? When there is a ordered array, and if we want to find out where to insert an item so that the array can keep itself ordered, `_.sortIndex()` is the choice. Apparently, we can implement such a function by using binary searching algorithm.

```js
/**_.sortedIndex(list, value, [iteratee], [context]) */
_.sortedIndex = function(array, obj, iteratee, context) {
    /** iteratee can be null or a function */
    iteratee = cb(iteratee, context, 1);
    
    /** the value returned by the iterative function */
    var value = iteratee(obj);
    
    var low = 0, high = getLength(array);
    
    /** binary searching */
    while (low < high) {
        var mid = Math.floor((low + high) / 2);
        if (iteratee(array[mid]) < value) low = mid + 1; else high = mid;
    }
    
    return low;
};
```

When it comes to `_.indexOf()` and `_.lastIndexOf()`, we should know that it's not compatible under IE9, and the implementation of underscore can be taken as a polyfill case to learn (by also using a predict function to create):

```js
/**
 * Generator function to create the indexOf and lastIndexOf functions
 * _.indexOf = createIndexFinder(1, _.findIndex, _.sortedIndex);
 * _.lastIndexOf = createIndexFinder(-1, _.findLastIndex);
 */
function createIndexFinder(dir, predicateFind, sortedIndex) {

// API 调用形式
// _.indexOf(array, value, [isSorted]) 
// _.indexOf(array, value, [fromIndex]) 
// _.lastIndexOf(array, value, [fromIndex]) 
return function(array, item, idx) {
  var i = 0, length = getLength(array);

  // 如果 idx 为 Number 类型
  // 则规定查找位置的起始点
  // 那么第三个参数不是 [isSorted]
  // 所以不能用二分查找优化了
  // 只能遍历查找
  if (typeof idx == 'number') {
    if (dir > 0) { // 正向查找
      // 重置查找的起始位置
      i = idx >= 0 ? idx : Math.max(idx + length, i);
    } else { // 反向查找
      // 如果是反向查找，重置 length 属性值
      length = idx >= 0 ? Math.min(idx + 1, length) : idx + length + 1;
    }
  } else if (sortedIndex && idx && length) {
    // 能用二分查找加速的条件
    // 有序 & idx !== 0 && length !== 0

    // 用 _.sortIndex 找到有序数组中 item 正好插入的位置
    idx = sortedIndex(array, item);

    // 如果正好插入的位置的值和 item 刚好相等
    // 说明该位置就是 item 第一次出现的位置
    // 返回下标
    // 否则即是没找到，返回 -1
    return array[idx] === item ? idx : -1;
  }

  // 特判，如果要查找的元素是 NaN 类型
  // 如果 item !== item
  // 那么 item => NaN
  if (item !== item) {
    idx = predicateFind(slice.call(array, i, length), _.isNaN);
    return idx >= 0 ? idx + i : -1;
  }

  // O(n) 遍历数组
  // 寻找和 item 相同的元素
  // 特判排除了 item 为 NaN 的情况
  // 可以放心地用 `===` 来判断是否相等了
  for (idx = dir > 0 ? i : length - 1; idx >= 0 && idx < length; idx += dir) {
    if (array[idx] === item) return idx;
  }

  return -1;
};
}

// Return the position of the first occurrence of an item in an array,
// or -1 if the item is not included in the array.
// If the array is large and already in sort order, pass `true`
// for **isSorted** to use binary search.
// _.indexOf(array, value, [isSorted]) 
// 找到数组 array 中 value 第一次出现的位置
// 并返回其下标值
// 如果数组有序，则第三个参数可以传入 true
// 这样算法效率会更高（二分查找）
// [isSorted] 参数表示数组是否有序
// 同时第三个参数也可以表示 [fromIndex] （见下面的 _.lastIndexOf）
_.indexOf = createIndexFinder(1, _.findIndex, _.sortedIndex);

// 和 _indexOf 相似
// 反序查找
// _.lastIndexOf(array, value, [fromIndex]) 
// [fromIndex] 参数表示从倒数第几个开始往前找
_.lastIndexOf = createIndexFinder(-1, _.findLastIndex);
```

