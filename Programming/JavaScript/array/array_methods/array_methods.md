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
`splice(index, howmany, item1, item2, ..., itemX)` is used to add/remove items of an array from the index, and add before deleting howmany items.

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


