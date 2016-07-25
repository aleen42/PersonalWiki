## Destructuring Assignment [Back](./../es6.md)

Destructuring Assignment(解構賦值) has made it possible to extract data from an array or an object, which will be assigned to a new variable.

```js
var [a, b] = [1, 2];
console.log(a);         /** => 1            */
console.log(b);         /** => 2            */

var [a, b, ...rest] = [1, 2, 3, 4, 5];
console.log(a);         /** => 1            */
console.log(b);         /** => 2            */
console.log(rest);      /** => [3, 4, 5]    */

var { a, b } = { a: 1, b: 2 };
console.log(a);         /** => 1            */
console.log(b);         /** => 2            */

/** Notice that, without var, { a, b } = { a: 1, b: 2 }; will be illegal */

{ a, b, ...rest } = { a:1, b: 2, c: 3, d: 4 };
/** ES7 Syntax */
```

### Destructuring Array

#### Simple example

```js
var foo = ['one', 'two', 'three'];

/** Without destructuring */
var one = foo[0];
var two = foo[1];
var three = foo[2];

var [one, two, three] = foo;
```

#### Swapping variables

```js
var a = 1;
var b = 3;

[a, b] = [b, a];

console.log(a);         /** => 3        */
console.log(b);         /** => 1        */
```

#### Return multiple values

```js
function f() {
    return [1, 3];
}
```
