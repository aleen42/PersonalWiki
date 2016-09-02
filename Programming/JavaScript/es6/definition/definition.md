## Variables Definition [Back](./../es6.md)

Usually we will define a variable in ES5 with the notation command `var`. In ES6, `let` and `const` have been come out to change this way. This document will have a introduction to talk about differences between them.

### let

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