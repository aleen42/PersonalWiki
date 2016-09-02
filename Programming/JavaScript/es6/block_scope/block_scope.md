## Block Scope [Back](./../es6.md)

### Introduction

In ES5, there is only **Global Scope** and **Function Scope**, which will cause some problems in cases. That's why ES6 has brought us with **Block Scope**.

**Scope** specifies the accessibility of a variable.

And what problems will occur when there is no **Block Scope**?

**Case 1: prevent overriden fom the internal Scope**

```js
var tmp = '123';

function f() {
    console.log(tmp);
    
    if (false) {
        /** Variables Hoisted */
        var tmp = 'abc';
    }
}

f();    /** => undefined    */
```

**Case 2: variables exposing**

```js
for (var i = 0; i < 10; i++) {}

console.log(i);     /** => 10       */
```

### Block Scope in ES6

In ES6, `let` is based on a block Scope.

```js
function f() {
    let n = 5;
    
    if (true) {
        let n = 20;
    }
    
    console.log(n); /** => 5        */
}
```

With Block Scope, IIFE (Immediately-Invoked Function Expression) is not necessary anymore.

```js
/** IIFE        */
(function() {
    var tmp = 'abc';
    /** ... */
})();

/** Block Scope */
{
    let tmp = 'abc';
}
```

