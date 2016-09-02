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

```
