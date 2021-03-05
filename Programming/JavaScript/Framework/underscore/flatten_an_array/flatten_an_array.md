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
        
        /** if the value is an array of an argument, then flatten it */
        if (isArrayLike(value) && (_.isArray(value) || _.isArguments(value))) {
            /**
             * flatten current level of array or arguments object
             * if `shallow` is false, then flatten recursively to reassign the value
             */
            if (!shallow) 
                value = flatten(value, shallow, strict);
            
            /** value shoule be an array */
            var j = 0, len = value.length;
            
            /** update the length? */
            output.length += len;
            
            /** push all elements of this value to the output array */
            while (j < len) {
                output[idx++] = value[j++];
            }
        } else if (!strict) { 
            /** if `strict` is false then do not ignore the element which is not an array */
            output[idx++] = value;
        }
    }
    
    return output;
};
```

So `_.flatten()` has been completed by the following code snippet:

```js
_.flatten = function(array, shallow) {
    /** given array and whether to flatten just one layer */
    return flatten(array, shallow, false);
};
```

`_.union()` has also called `flatten()` to complete its duty to combine different sets (arrays with only unique elements):

```js
_.union = function() {
    return _.uniq(flatten(arguments, true, true));
};
```

`_.difference()`, `_.pick()`, and `_.omit` have also used `flatten()` to implement. Therefore, one of the most elegant things of underscore is that it has created many predicate methods to implement hundreds of functions.
