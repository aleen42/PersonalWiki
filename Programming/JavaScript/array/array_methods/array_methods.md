## Methods of an array [Back](./../array.md)

### Basic Operations

#### 1. `concat()`

`concat()` is used to put more than two arrays into one, and return.

```js
const a = [1, 2, 3];
console.log(a.concat(4, 5));    /** => [1, 2, 3, 4, 5]          */

const b = [4, 5];
const c = [6];
console.log(a.concat(b, c));    /** => [1, 2, 3, 4, 5, 6]       */
```

***concat() will return an new array copy, without changing the original one.***

#### 2. `join()`

`join()` is used to put items in an array into an string, with a separator.

```js
const a = ['Hello', 'World'. 'Aleen'];
console.log(a.join(', '));      /** => "Hello, World, Aleen"    */
```

#### 3. `pop()` & `shift()`

`pop()` is used to delete and return the last item of an array.
`shift()` is used to delete and return the first item of an array.

```js
const a = [1, 2, 3, 4, 5, 6];
console.log(a.pop());           /** => 6                        */
console.log(a);                 /** => [1, 2, 3, 4, 5]          */
console.log(a.shift());         /** => 1                        */
console.log(a);                 /** => [2, 3, 4, 5]             */
```

##### 4. `push()` & `unshift()`

`push()` is used to push one item into the last position of an array, and return the new length of this array.
`unshift()` is used to push one item into the first position of an array, and return the new length of this array.

```js
const a = [2, 3, 4, 5];
console.log(a.push(6));         /** => 5                        */
console.log(a);                 /** => [2, 3, 4, 5, 6]          */
console.log(a.unshift(1));      /** => 6                        */
console.log(a);                 /** => [1, 2, 3, 4, 5, 6]       */
```

#### 5. `reverse()`

`reverse()` is used to reverse the order of an array.

```js
const a = [1, 2, 3, 4, 5];
console.log(a.reverse());       /** => [5, 4, 3, 2, 1]          */
console.log(a);                 /** => [5, 4, 3, 2, 1]          */
```

***reverse() will change the original array, rather than creating a new copy***

#### 6. `sort()`

`sort()` will have a sort of an array, based on the character or the number among them.

```js
const a = [1, 2, 3, 4, 5];
console.log(a.reverse());       /** => [5, 4, 3, 2, 1]          */
console.log(a);                 /** => [5, 4, 3, 2, 1]          */
```
