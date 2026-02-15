## Methods of an array [Back](./../array.md)

### Basic Operations

#### 1. `concat(arrayX, arrayX, ..., arrayX)`

`concat(arrayX, arrayX, ..., arrayX)` is used to put more than two arrays into one, and return.

```js
const a = [1, 2, 3];
console.log(a.concat(4, 5));            /** => [1, 2, 3, 4, 5]          */

const b = [4, 5];
const c = [6];
console.log(a.concat(b, c));            /** => [1, 2, 3, 4, 5, 6]       */
```

***concat(arrayX, arrayX, ..., arrayX) will return an new array copy, without changing the original one.***

#### 2. `join(separator)`

`join(separator)` is used to put items in an array into an string, with a separator.

```js
const a = ['Hello', 'World'. 'Aleen'];
console.log(a.join(', '));              /** => Hello, World, Aleen      */
```

#### 3. `pop()` & `shift()`

`pop()` is used to delete and return the last item of an array.
`shift()` is used to delete and return the first item of an array.

```js
const a = [1, 2, 3, 4, 5, 6];
console.log(a.pop());                   /** => 6                        */
console.log(a);                         /** => [1, 2, 3, 4, 5]          */
console.log(a.shift());                 /** => 1                        */
console.log(a);                         /** => [2, 3, 4, 5]             */
```

#### 4. `push(item1, item2, ..., itemX)` & `unshift(item1, item2, ..., itemX)`

`push(item1, item2, ..., itemX)` is used to push one item into the last position of an array, and return the new length of this array.
`unshift(item1, item2, ..., itemX)` is used to push one item into the first position of an array, and return the new length of this array.

```js
const a = [2, 3, 4, 5];
console.log(a.push(6));                 /** => 5                        */
console.log(a);                         /** => [2, 3, 4, 5, 6]          */
console.log(a.unshift(1));              /** => 6                        */
console.log(a);                         /** => [1, 2, 3, 4, 5, 6]       */
```

#### 5. `reverse()`

`reverse()` is used to reverse the order of an array.

```js
const a = [1, 2, 3, 4, 5];
console.log(a.reverse());               /** => [5, 4, 3, 2, 1]          */
console.log(a);                         /** => [5, 4, 3, 2, 1]          */
```

***reverse() will change the original array, rather than creating a new copy***

#### 6. `sort(sortby)`

`sort(sortby)` will have a sort of an array, based on the character or the number among them.

- sortby(optional): must be a function to specify which is the before one
    - function sortby(a, b)
        - return **<0**: a is the before one
        - return **=0**: a or b can be the before one
        - return **>0**: b is the before one

```js
const a = [3, 5, 1, 2, 4];
console.log(a.sort());                  /** => [1, 2, 3, 4, 5]          */

function sortby(a, b) {
    return b - a;
}

console.log(a.sort(sortby));            /** => [5, 4, 3, 2, 1]          */
```

***sort(sortby) will change the original array, rather than creating a new copy***

#### 7. `slice(start, end)` & `splice(index, howmany, item1, item2, ..., itemX)`

`slice(start, end)` is used to get items of an array from the start to the end. (**not include the end**)
`splice(index, howmany, item1, item2, ..., itemX)` is used to add/remove items of an array from the index, and add before deleting `howmany` items.

- end(optional): specify when to end, which is equivalent to the (length + 1) of the array.

```js
const a = [1, 2, 3, 4, 5];
console.log(a.slice(2, 4));             /** => [3, 4]                   */
console.log(a.slice(1));                /** => [2, 3, 4, 5]             */
console.log(a.slice(3, 4));             /** => [4]                      */
```

***slice(start, end) will return an new array copy, without changing the original one.***

```js
const a = [1, 2, 3, 4, 5];
console.log(a.splice(0, 2, 7, 8));      /** => [7, 8, 3, 4, 5]          */
console.log(a.splice(4, 0, 1));         /** => [1, 2, 3, 4, 5, 1]       */
```

***splice(index, howmany, item1, item2, ..., itemX) will change the original array, rather than creating a new copy***

#### 8. `toString()` && `toLocaleString()`

Both `toString()` and `toLocaleString()` will return a string, but the method `toLocalString()` will return various result according to the local environment like time.

```js
const a = [1, 2, 3, 4];
console.log(a.toString());              /** => 1,2,3,4                  */
console.log(a.toLocaleString());        /** => 1,2,3,4                  */
console.log(a.join());                  /** => 1,2,3,4                  */
console.log(a.join(,));                 /** => 1,2,3,4                  */
console.log(a.join() === a.toString()); /** => true                     */
```

### Sets Operations

#### 1. `each()`

```js
/**
 * [each: iterate each item of an array]
 * @param  {Function} fn [iterating function]
 * @return {[type]}      [description]
 */
Array.prototype.each = function (fn) {
    /** fn is assigned to Function.K by default */
    fn = fn || Function.K;

    /** a set of results */
    var a = [];

    /** get arguments into an array except the first argument */
    var args = Array.prototype.slice.call(arguments, 1);

    /** loop to call function */
    for (var i = 0; i < this.length; i++) {
        /** apply arguments to the function to call */
        var res = fn.apply(this, [this[i], i].concat(args));

        if (res !== null) {
            /** push the result into the array and return eventually */
            a.push(res);
        }
    }

    return a;
}
```

#### 2. `uniquelize()`

```js
/**
 * [uniquelize: remove replicate items from an array]
 * @return {[type]} [description]
 */
Array.prototype.uniquelize = function () {
    var ra = new Array();

    for (var i = 0; i < this.length; i++) {
        if (!ra.contains(this[i])) {
            ra.push(this[i]);
        }
    }

    return ra;
}
```

#### 3. `intersect(a, b)`

```js
Array.intersect = function (a, b) {
    return a.uniquelize().each(function (o) {
        return b.includes(o) ? o : null;
    });
};
```

#### 4. `union(a, b)`

```js
Array.union = function (a, b) {
    return a.concat(b).uniquelize();
};
```

#### 5. `minus(a, b)`

```js
Array.minus = function (a, b) {
    return a.uniquelize().each(function (o) {
        return b.includes(o) ? null : o;
    });
};
```

#### 6. `complement(a, b)`

```js
Array.complement = function (a, b) {
    return Array.minus(Array.union(a, b), Array.intersect(a, b));
}
```

### Feature Operations

#### 1. `Array.of(element0, element1, ..., elementX)`

`Array.of(element0, element1, ..., elementX)` is used to put mutiple elements into one array and return a new array instance.

```js
console.log(Array.of(1));               /** => [1]                  */
console.log(Array.of(undefined));       /** => [undefined]          */
```

**Polyfill:**

```js
if (!Array.of) {
    Array.of = function() {
        return Array.prototype.slice.call(arguments);
    };
}
```

#### 2. `Array.from(obj, mapFn, thisArg)`

`Array.from(obj, mapFn, thisArg)` is used to convert a array-like object into an array.

Those two kindes of array-like objects can be converted into arries:

- Array-like Object (with `length` attribute, and any objects with keys)
- Iteratable Object (like Map, Set, and so on)

- **mapFn**(optional): the map function which will be executed before the array return.
- **thisArg**(optional): `this` for `mapFn`.

```js
Array.from(obj, mapFn, thisArg);
Array.from(obj).map(mapFn, thisArg);

function convertIntoArray() {
    return Array.from(argments);
}

console.log(convertIntoArray(1, 2, 3)); /** => [1, 2, 3]            */
console.log(Array.from('foo'));         /** => ["f", "o", "o"]      */
```

**Polyfill:**

```js
// Production steps of ECMA-262, Edition 6, 22.1.2.1
// Reference: https://people.mozilla.org/~jorendorff/es6-draft.html#sec-array.from
if (!Array.from) {
    Array.from = (function () {
        var toStr = Object.prototype.toString;

        var isCallable = function (fn) {
            return typeof fn === 'function' || toStr.call(fn) === '[object Function]';
        };

        var toInteger = function (value) {
            var number = Number(value);
            if (isNaN(number)) { return 0; }
            if (number === 0 || !isFinite(number)) { return number; }
            return (number > 0 ? 1 : -1) * Math.floor(Math.abs(number));
        };

        var maxSafeInteger = Math.pow(2, 53) - 1;

        var toLength = function (value) {
            var len = toInteger(value);
            return Math.min(Math.max(len, 0), maxSafeInteger);
        };

        // The length property of the from method is 1.
        return function from(arrayLike/*, mapFn, thisArg */) {
            // 1. Let C be the this value.
            var C = this;

            // 2. Let items be ToObject(arrayLike).
            var items = Object(arrayLike);

            // 3. ReturnIfAbrupt(items).
            if (arrayLike == null) {
                throw new TypeError("Array.from requires an array-like object - not null or undefined");
            }

            // 4. If mapfn is undefined, then let mapping be false.
            var mapFn = arguments.length > 1 ? arguments[1] : void undefined;
            var T;

            if (typeof mapFn !== 'undefined') {
                // 5. else      
                // 5. a If IsCallable(mapfn) is false, throw a TypeError exception.
                if (!isCallable(mapFn)) {
                    throw new TypeError('Array.from: when provided, the second argument must be a function');
                }

                // 5. b. If thisArg was supplied, let T be thisArg; else let T be undefined.
                if (arguments.length > 2) {
                    T = arguments[2];
                }
            }

            // 10. Let lenValue be Get(items, "length").
            // 11. Let len be ToLength(lenValue).
            var len = toLength(items.length);

            // 13. If IsConstructor(C) is true, then
            // 13. a. Let A be the result of calling the [[Construct]] internal method of C with an argument list containing the single item len.
            // 14. a. Else, Let A be ArrayCreate(len).
            var A = isCallable(C) ? Object(new C(len)) : new Array(len);

            // 16. Let k be 0.
            var k = 0;
            // 17. Repeat, while k < len… (also steps a - h)
            var kValue;

            while (k < len) {
                kValue = items[k];

                if (mapFn) {
                    A[k] = typeof T === 'undefined' ? mapFn(kValue, k) : mapFn.call(T, kValue, k);
                } else {
                    A[k] = kValue;
                }

                k += 1;
            }

            // 18. Let putStatus be Put(A, "length", len, true).
            A.length = len;
            // 20. Return A.
            return A;
        };
    }());
}
```

#### 3. `Array.isArray(value)`

`Array.isArray(value)` is used to justify whether the value is an array.

**Polyfill:**

```js
if (!Array.isArray) {
    Array.isArray = function (obj) {
        return Object.prototype.toString.call(obj) === '[Object Array]';
    }
}
```

#### 4. `filter(callback, thisArg)`

`filter(callback, thisArg)` is used to filter all elements in an array, and create a new one for which get true from callback.

- **thisArg**(optional): `this` for `callback`.

```js
console.log([12, 5, 8, 130, 44].filter(function (item) {
    return item >= 10;
}));        /** => [12, 130, 44] */

console.log([12, 5, 8, 130, 44].filter(function (item, i) {
    return item >= 10 && (i % 2 === 0);
}));        /** => [12, 44] */
```

**Polyfill:**

```js
if (!Array.prototype.filter) {
    Array.prototype.filter = function (fun /*, thisArg */) {
        "use strict";

        if (this === void 0 || this === null) {
            throw new TypeError();
        }

        var t = Object(this);
        var len = t.length >>> 0;

        if (typeof fun !== "function") {
            throw new TypeError();
        }

        var res = [];
        var thisArg = arguments.length >= 2 ? arguments[1] : void 0;

        for (var i = 0; i < len; i++) {
            if (i in t) {
                var val = t[i];

                // NOTE: Technically this should Object.defineProperty at
                //       the next index, as push can be affected by
                //       properties on Object.prototype and Array.prototype.
                //       But that method's new, and collisions should be
                //       rare, so use the more-compatible alternative.
                if (fun.call(thisArg, val, i, t)) {
                    res.push(val);
                }
            }
        }

        return res;
    };
}
```

#### 5. `some(callback, thisArg)`

`some(callback, thisArg)` is used to test whether some element in the array passes the test implementation by the provided function.

- **callback**: a provided function which take three arguments:
    - **currentValue**: the current element being passed
    - **index**: the index of the current element being passed
    - **array**: the array some() was called upon
- **thisArg**(optional): `this` for `mapFn`.

```js
function isBiggerThan10(element, index, array) {
    return element > 10;
}

console.log([2, 5, 8, 1, 4].some(isBiggerThan10));  /** => false */
console.log([12, 5, 8, 1, 4].some(isBiggerThan10)); /** => true */
```

**polyfill:**

```js
// Production steps of ECMA-262, Edition 5, 15.4.4.17
// Reference: http://es5.github.io/#x15.4.4.17
if (!Array.prototype.some) {
    Array.prototype.some = function(fun/*, thisArg*/) {
        'use strict';

        if (this == null) {
            throw new TypeError('Array.prototype.some called on null or undefined');
        }

        if (typeof fun !== 'function') {
            throw new TypeError();
        }

        var t = Object(this);
        var len = t.length >>> 0;

        var thisArg = arguments.length >= 2 ? arguments[1] : void 0;

        for (var i = 0; i < len; i++) {
            if (i in t && fun.call(thisArg, t[i], i, t)) {
                return true;
            }
        }

        return false;
    };
}
```
