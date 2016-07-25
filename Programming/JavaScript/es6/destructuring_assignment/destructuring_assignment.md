## Destructuring Assignment [Back](./../es6.md)

Destructuring Assignment(解構賦值) has made it possible to extract data from an array or an object, which will be assigned to a new variable.

```js
var [a, b] = [1, 2];
console.log(a);         /** => 1    */
console.log(b);         /** => 2    */

var [a, b, ...rest] = [1, 2, 3, 4, 5];
```