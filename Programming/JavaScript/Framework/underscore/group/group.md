## Group [Back](./../underscore.md)

`group()` is an internal function in underscore, which is mainly used to implement three APIs: `_.groupBy()`, `_.indexBy()`, and `_.countBy()`.

Firstly, the following snippet has described how to use `_.groupBy()` to group an array according to some conditions:

```js
_.groupBy([1.1, 1.2, 2.1], function (num) {
    return Math.floor(num);
}); /** => { 1: [1.1, 1.2], 2: [2.1] } */

_.groupBy(['one', 'two', 'three'], 'length');
/** => { 3: ['one', 'two'], 5: ['three'] } */
```

It's apparent that the second parameters passed to the method has decided how to group a given array. Without looking at the implementation of underscore, we can also easily complete it by us:

```js
function groupBy(arr, conditions) {
    /** to return an object */
    var result = {};
    
    /** if the `conditions` is a property name */
    if (Object.prototype.toString.call(conditions) === '[object String]') {
        /** override conditions */
        const keyName = conditions;
        
        conditions = function (item) {
            return item[keyName];
        };
    }
    
    /** iterate the array */
    for (var i = 0, len = arr.length; i < len; i++) {
        var key = conditions(arr[i]);
        
        if (result[key] === void 0) {
            result[key] = [];
        }
        
        result[key].push(arr[i]);
    }
    
    return result;
}
```

What about `_.indexBy()`:

```js
_.indexBy([{ name: 'Peter', age: 40 }, { name: 'Aleen', age: 24 }], 'age');
/**
 * => {
 *       24: { name: 'Aleen', age: 24 },
 *       40: { name: 'Peter', age: 40 }
 *    }
 */

_.indexBy(['one', 'two', 'three'], 'length');
/** => { 3: 'two', 5: 'three' } */
```

As you can see, it's familiar with `_.groupBy()`, and the difference between them is that elements are always unique under the index. If there are more than two elements under the same index, the latter element will override the former one.

```js
function indexBy(arr, conditions) {
    /** to return an object */
    var result = {};
    
    /** if the `conditions` is a property name */
    if (Object.prototype.toString.call(conditions) === '[object String]') {
        /** override conditions */
        const keyName = conditions;
        
        conditions = function (item) {
            return item[keyName];
        };
    }
    
    /** iterate the array */
    for (var i = 0, len = arr.length; i < len; i++) {
        var key = conditions(arr[i]);
        
        /** without creating an array */
        result[key] = arr[i];
    }
    
    return result;
}
```

When it comes to `_.countBy()`, the key is also same with other two methods discussed above, and corresponding object is used to store the number of objects bound to this key in a given array.

```js
function countBy(arr, conditions) {
    /** to return an object */
    var result = {};
    
    /** if the `conditions` is a property name */
    if (Object.prototype.toString.call(conditions) === '[object String]') {
        /** override conditions */
        const keyName = conditions;
        
        conditions = function (item) {
            return item[keyName];
        };
    }
    
    /** iterate the array */
    for (var i = 0, len = arr.length; i < len; i++) {
        var key = conditions(arr[i]);
        
        /** make a counter */
        if (result[key] === void 0) {
            result[key] = 0;
        }
        
        result[key]++;
    }
    
    return result;
}
```

After comparing these three methods, we can actually abstract them with an internal method, like what underscore has done.

```js
function group(handle) {
    return function (arr, conditions) {
        /** to return an object */
        var result = {};
        
        /** if the `conditions` is a property name */
        if (Object.prototype.toString.call(conditions) === '[object String]') {
            /** override conditions */
            const keyName = conditions;
            
            conditions = function (item) {
                return item[keyName];
            };
        }
        
        /** iterate the array */
        for (var i = 0, len = arr.length; i < len; i++) {
            var key = conditions(arr[i]);
            
            /** to handle in three various situations */
            handle(result, key, arr[i]);
        }
        
        return result;
    };
}

var groupBy = group(function (result, key, value) {
    /** create an array to store objects */
    if (result[key] === void 0) {
        result[key] = [];
    }
    
    result.push[value];
});

var indexBy = group(function (result, key, value) {
    /** without creating an array */
    result[key] = value;
});

var countBy = goup(function (result, key, value) {
    /** make a counter */
    if (result[key] === void 0) {
        result[key] = 0;
    }
    
    result[key]++;
});
```

It's an elegant way!
