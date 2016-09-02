## Block Domain [Back](./../es6.md)

### Introduction

In ES5, there is only **Global Domain** and **Function Domain**, which will cause some problems in cases. That's why ES6 has brought us with **Block Domain**.

**Domain** specifies the accessibility of a variable.

And what problems will occur when there is no **Block Domain**?

**Case 1: prevent overriden fom the internal domain**

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

### Block Domain in ES6

In ES6, `let` is based on a block domain.

```js
function f() {
    let n = 5;
    
    if (true) {
        let n = 20;
    }
    
    console.log(n); /** => 5        */
}
```