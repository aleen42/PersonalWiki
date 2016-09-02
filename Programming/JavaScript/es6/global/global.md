## Global [Back](./../es6.md)

Global Object refers to the top object, which is `window` in browsers, while `global` in Node.js.

In ES5, the property of a Global Object is same as a Global Variable.

```js
window.a = 1;
console.log(a);             /** => 1            */

a = 2;
console.log(window.a);      /** => 2            */
```

In ES6, variables defined by `var` and `function` are still same as Global Variables. However, variables defined by `let`, `const` or `class` do not belong to properties of the Global Object.

```js
var a = 1;

/** in Node.js, it should be `global.a = 1;` or `this.a = 1;`  */
console.log(window.a);      /** => 1            */

let b = 1;
console.log(window.b);      /** => undefined    */
```