## Methods of an array [Back](./../array.md)

### Basic Operations

###### `concat()`

`concat()` is used to put more than two arrays into one, and return.

{%ace edit=false, lang='javascript', theme='tomorrow'%}
const a = [1, 2, 3];
console.log(a.concat(4, 5));    /** => [1, 2, 3, 4, 5]          */

const b = [4, 5];
const c = [6];
console.log(a.concat(b, c));    /** => [1, 2, 3, 4, 5, 6]       */
{%endace%}

***concat() will return an new array copy, without changing the original one.***

###### `join()`

`join()` is used to put items in an array into an string, with a separator.

{%ace edit=false, lang='javascript', theme='tomorrow'%}
const a = ['Hello', 'World'. 'Aleen'];
console.log(a.join(', '));      /** => "Hello, World, Aleen"    */
{%endace%}

###### `pop()` & `shift()`

`pop()` is used to delete and return the last item of an array.
`shift()` is used to delete and return the first item of an array.

{%ace edit=false, lang='javascript', theme='tomorrow'%}
const a = [1, 2, 3, 4, 5, 6];
console.log(a.pop());           /** => 6                        */
console.log(a);                 /** => [1, 2, 3, 4, 5]          */
console.log(a.shift());         /** => 1                        */
console.log(a);                 /** => [2, 3, 4, 5]             */
{%endace%}

##### `push()` & `unshift()`

`push()` is used to push one item into the last position of an array, and return the new length of this array.
`unshift()` is used to push one item into the first position of an array, and return the new length of this array.

{%ace edit=false, lang='javascript', theme='tomorrow'%}
const a = [2, 3, 4, 5];
console.log(a.push(6));         /** => 5                        */
console.log(a);                 /** => [2, 3, 4, 5, 6]          */
console.log(a.unshift(1));      /** => 6                        */
console.log(a);                 /** => [1, 2, 3, 4, 5, 6]       */
{%endace%}

#### `reverse()`

`reverse()` is used to reverse the order of an array.

{%ace edit=false, lang='javascript', theme='tomorrow'%}
const a = [1, 2, 3, 4, 5];
console.log(a.reverse());       /** => [5, 4, 3, 2, 1]          */
console.log(a);                 /** => [5, 4, 3, 2, 1]          */
{%endace%}

***reverse() will change the original array, rather than creating a new copy***
