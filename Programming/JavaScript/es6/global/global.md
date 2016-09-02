## Global [Back](./../es6.md)

Global Object refers to the top object, which is `window` in browsers, while `global` in Node.js.

In ES5, the property of a Global Object is same as a Global Variable.

```js
window.a = 1;
console.log(a);             /** => 1    */

a = 2;
console.log(window.a);      /** => 2    */
```
