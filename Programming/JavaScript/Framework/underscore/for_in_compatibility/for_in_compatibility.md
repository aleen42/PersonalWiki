## Compatibility problems of `for ... in` [Back](./../underscore.md)

As we known, `for ... in` will only loop through all the **enumerable attributes**. Objects created by the inner constructors of Array and Object will inherit all the non-enumerable attributes like `indexOf()` from String, or `toString()` from Object. `for ... in` will iterate to loop through all the enumerable attributes of objects and attributes inherited from their constructors. (include overridden built-in attributes)

```js
var obj = {
    name: 'hanzichi',
    age: 30
};

for (var k in obj) {
    console.log(k, obj[k]);
}

/** 
 * output:
 *  => name hanzichi
 *  => 30
 */
```

However, there is a compatibility problem in IE8 (Apparently, IE8 has treated `toString` as a non-enumerable attribute, even if it's overridden):

```js
var obj = { toString: 'hanzichi' };

for (var k in obj) {
    alert(k);
}

/**
 * output:
 *  => toString (Chrome)
 *  => nothing hanppen in IE*
 */
```

Therefore, in underscore.js, there is a method named `hasEnumBug` to get bug from IE8:

```js
/**
 * Keys in IE < 9 that won't be iterated by `for key in ...` and thus missed.
 * And the but can be judged by checking whether `toString` can be overriden */
var hasEnumBug = !{ toString: null }.propertyIsEnumerable('toString');
```

Besides, underscore.js has listed out all the familiar situation in the set `nonEnumerableProps`.

```js
/** the keys which can not be iterated with for ... in */
var nonEnumerableProps = ['valueOf', 'isPrototypeOf', 'toString', 'propertyIsEnumerable', 'hasOwnProperty', 'toLocaleString'];
```

If some has been ignored, it will also provide a method used for collecting, named `collectNonEnumProps`.

```js
function collectNonEnumProps(obj, keys) {
    var nonEnumIdx = nonEnumerableProps.length;
    var constructor = obj.constructor;

    /** check whether `proto` is inherited */
    var proto = (_.isFunction(constructor) && constructor.prototype) || ObjProto;

    /**
     * Constructor is a special case.
     * if the object has `constructor` but the key is not included in the array `keys`, then save it in it
     */
    var prop = 'constructor';
    if (_.has(obj, prop) && !_.contains(keys, prop)) keys.push(prop);
    
    /** check the `nonEnumerableProps` array */
    while (nonEnumIdx--) {
        prop = nonEnumerableProps[nonEnumIdx];
        /** 
         * obj[prop] !== proto[prop] is used to check whether the property is from the inherited prototype
         * then check whether the array `keys` has contained non-enumerable properties
         */
        if (prop in obj && obj[prop] !== proto[prop] && !_.contains(keys, prop)) {
            keys.push(prop);
        }
    }
}
```

After overriding all the attributes, keys can be gotten under IE 9. However, there are still a doubt why handling constructor specially.