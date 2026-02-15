## The internal function: `createAssigner()` [Back](./../underscore.md)

In underscore, you may have to know this important function, which is named `createAssigner()`. Before discussing about what it has done, we may also have to know another three APIs calling this function firstly. They're `_.extend()`, `_.extendOwn()`, and `_.defaults()`.

Firstly, when we want to merge all properties from an object b to an object a, we may remember the function `Object.assign(a, b)`. That's exactly what `_.extend()` has done. And `_.extendOwn()`will only copy own properties of one object to another one. When it comes to `_.defaults()`, it's familiar with `_.extend()`, but what the difference is `_.defaults()` will check whether there are repeated properties while copying. If so, the second property will not override the first one.

For these three APIs, underscore has implemented them all by calling `createAssigner()`:

```js
_.extend = createAssigner(_.allKeys);
_.extendOwn = createAssigner(_.keys);
_.defaults = createAssigner(_.allKeys, true);
```

Then, let's go to have a look at the function they call:

```js
/**
 * An internal function for creating assigner functions.
 * There're three methods using this internal function
 * _.extend & _.extendOwn & _.defaults
 * _.extend = createAssigner(_.allKeys);
 * _.extendOwn = _.assign = createAssigner(_.keys);
 * _.defaults = createAssigner(_.allKeys, true);
 */
var createAssigner = function(keysFunc, undefinedOnly) {
    /** return a clousure function */
    return function(obj) {
        var length = arguments.length;
        /** if the object is null or the second paramter has not been provided */
        if (length < 2 || obj == null) return obj;
        
        /** iteration of sources */
        for (var index = 1; index < length; index++) {
            var source = arguments[index],
            /** use different `keysFunc` to extract keys from a sorce object */
            keys = keysFunc(source),
            l = keys.length;
            
            /** iterate key-value pairs */
            for (var i = 0; i < l; i++) {
                var key = keys[i];
                /**
                 * If `undefinedOnly` has not been provided,
                 * it means that the original key-value pair
                 * can be overriden by the source object.
                 * If it does has been provided, then check whether the key has already exisited by checking `obj[key] === void 0`
                 */ 
                if (!undefinedOnly || obj[key] === void 0) 
                    obj[key] = source[key];
            }
        }
        
        /** return the modified object */
        return obj;
    };
};
```

As `undefinedOnly` will accept `null` when this function is called, the author has check the number of `arguments` to make decisions about what should be returned. 
