## Variables Definition [Back](./../es6.md)

Usually we will define a variable in ES5 with the notation command `var`. In ES6, `let` and `const` have been come out to change this way. This document will have a introduction to talk about differences between them.

### let

#### Domain

`let` is familiar with `var`, but what it defines is only worked in a blocked `{}`.

```js
{
    var a = 1;
    let b = 1;
}

console.log(a); /** => 1                                */
console.log(b); /** => ReferenceError: b is not defined */
```

According to this new feature, it's proper to use `let` in a `for` block:

```js
for (let i = 0 ; i < 10; i++) {}

console.log(i); /** => ReferenceError: b is not defined */
```

That's because if we use `var` to define index in a loop structure, it will easily go wrong like this (**the array item is not pointed to a closure**):

```js
var a = [];

for (var i = 0; i < 10; i++) {
    a[i] = function () {
        console.log(i);
    };
}

a[6].call();    /** => 10   */
```

To fix this, you're going to write like this:

```js
var a = [];

for (var i = 0; i < 10; i++) {
    a[i] = (function (index) {
        return function () {
            console.log(index);
        };
    })(i);
}

a[6].call();    /** => 6    */
```

#### Variables Hoisted

`var` will have a phenomena called "variables hosited(變量提升)", which `let` will not.

```js
console.log(foo);   /** => undefined                            */
console.log(bar);   /** => ReferenceError: bar is not defined   */

var foo = 1;
let bar = 1;
```

#### Temporal Dead Zone (TDZ, 暫時性死區)

```js
var tmp = 123;

if (true) {
    tmp - 'abc';    /** => ReferenceError: tmp is not defined   */
    let tmp;
}
```

That's because ES6 has explicitly specified that if a block has use `let` or `const` to define a variable, any operation to this variables before their declaration will throw an error of `ReferenceError`.

```js
if (true) {
    /** the start point of a TDZ to `tmp` */
    tmp = 'abc';
    console.log(tmp);   /** => ReferenceError: tmp is not defined   */
    
    /** the end point of the TDZ to `tmp` */
    let tmp;
    console.log(tmp);   /** => undefined                            */
    
    tmp = 'bcd';
    console.log(tmp);   /** => abc                                  */
}
```

With TDZ, it means that it's not secure to use `typeof`.

```js
if (true) {
    typeof tmp;         /** => ReferenceError: tmp is not defined   */
    let tmp;
}

if (true) {
    console.log(typeof tmp);         /** => undefined               */
}
```

Besides, some TDZ is hard to identify:

```js
function bar(x = y, y = 2) {
    return [x, y];      /** => ReferenceError: y is not defined     */
}

function foo(x = 2, y = x) {
    return [x, y];      /** => [2, 2]                               */
}

bar();
foo();
```

```js
let x = 1;
switch('case2') {
case 'case1':       /** eslint: no-case-declarations */
    let x = 2;
    break;
case 'case2':
    console.log(x); /** => ReferenceError: x is not defined */
    break;
}
```

#### Duplicate Definition

Duplicate definition will cause problems when defining variables in the same domian:

```js
function () {
    /** Error */
    let a = 10;
    var a = 1;
}

function () {
    let a = 10;
    
    /** Error */
    let a = 1;
}

function func(arg) {
    /** Error */
    let arg;
}

function func(arg) {
    {
        /** No Error */
        let arg;
    }
}
```

### const

`const` is another command to define variables, which are **read-only**. Once they are assigned, they can not be changed any more.

```js
const PI = 3.14;
console.log(PI);    /** => 3.14                                                     */

PI = 3;             /** => TypeError: Assignment to constant variable.              */
```

Besides, when initiating a variable with `const`, they should be assigned.

```js
const foo;          /** => SyntaxError: Missing initializer in const declaration    */
```

If you want to initiate a constant variable for an array or an object, using `const` only ensures that **the pointer is constant**.

```js
const arr = [];

/** No Error */
arr.push('1');

/** No Error */
a.length = 0;

a = ['What'];       /** => TypeError: Assignment to constant variable.              */

const obj = {};

obj.prop = 123;

obj = {
    prop: 123
};                  /** => TypeError: Assignment to constant variable.              */
```

If you want to lock on the whole object, you can use `Object.freeze()`.

```js
const obj = Object.freesize({});

'use strict';

/** Not work the normal mode */
/** Error in the strict mode */
obj.prop = 123;
```

Anything else is same as `let`.


