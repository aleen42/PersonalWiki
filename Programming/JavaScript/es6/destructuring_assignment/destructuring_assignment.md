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
/** ES7 Syntax, still not work in Firefox */
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

var [a, b] = f();
```

Of course, you can ignore some return value like this:

```js
function f() {
    return [1, 2, 3];
}

var [a, , b] = f();

console.log(a);         /** => 1        */
console.log(b);         /** => 3        */
```

### Destructuring Object

#### Simple example

```js
/** should match the key name */
var { p, q } = { p: 42, q: true };

console.log(p);         /** => 42       */
console.log(q);         /** => true     */

/** use a new variable name */
var { p: foo, q: bar } = { p: 42, q: true };
console.log(foo);       /** => 42       */
console.log(bar);       /** => true     */
```

#### Default arguments

In ES5:

```js
function drawES5Chart(options) {
    options = options === undefined ? {} : options;
    var size = options.size === undefined ? 'big' : options.size;
    var cords = options.cords === undefined ? { x: 0, y: 0 } : options.cords;
    var radius = options.radius === undefined ? 25: options.radius;
    
    console.log(size, cords, radius);
}

drawES5Chart({
    cords: { x: 18, y: 30 },
    radius: 30
});
```

In ES6 (still not work in Firefox):

```js
function drawES6Chart({ size = 'big', cords = { x: 0, y: 0 }, radius = 25 } = {}) {
    console.log(size, cords, radius);
}

drawES6Chart({
    cords: { x: 18, y: 30 },
    radius: 30
});
```

#### Load modules

Destructuring Assignments can help loading specific modules from a whold module like [Add-on SDK](https://developer.mozilla.org/en-US/Add-ons/SDK):

```js
const { Loader, main } = require('toolkit/loader');
```

#### Computed object property names and destructuring

```js
let key = 'z';
let { [key]: foo } = { z: 'bar' };

console.log(foo);       /** => bar      */
```
