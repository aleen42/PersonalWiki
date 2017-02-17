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

### Function Definition in Block Scope

In ES5, it's not allowed to define a function in a block like this:

```js
if (true) {
    function f() {}
}

try {
    function f() {}
} catch (e) {
}
```

However, browsers have not obeyed this rule and you can also define functions whthin a block, except for the **strict mode**.

```js
'use strict';

if (true) {
    /** Error */
    function f() {}
}
```

In ES6, **it's allowed**.

```js
'use strict';

if (true) {
    /** No Error */
    function f() {}
}
```

Besides, function declaration will act like `let`:

```js
function f() {
    console.log('Outside');
}

(function(){
    if (false) {
        function f() {
            console.log('Inside');
        }
    }
    
    f();    /**
             * => Inside    (ES5)
             * => Outside   (ES6)
             * => Uncaught TypeError: f is not a function (Chrome ES6)
             */
})();
```

Why there is an error? That's because Chrome will run like this:

```js
function f() {
    console.log('Outside');
}

(function(){
    var f = undefined;
    
    if (false) {
        function f() {
            console.log('Inside');
        }
    }
    
    f();    /**
             * => Inside    (ES5)
             * => Outside   (ES6)
             * => Uncaught TypeError: f is not a function (Chrome ES6)
             */
})();
```

Therefore, **again recommend that not to declare functions in a block as possible as you can**. If necessary, you can use Function Expression rather than Function Declaration.

```js
{
    let a = 'secret';
    
    /** Function Declaration */
    function f() {
        return a;
    }
}

{
    let a = 'secret';
    
    /** Function Expression */
    let b = function () {
        return a;
    };
}
```

Another case you should pay attention to is that a block scope should be define with the notation `{}`:

```js
'use strict';

if (true) {
    /** No Error */
    function f() {}
}

if (true) 
    /** Error */
    function e() {}
```