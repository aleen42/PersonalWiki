## Block Domain [Back](./../es6.md)

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