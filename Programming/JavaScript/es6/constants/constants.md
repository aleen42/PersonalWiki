## Constants [Back](./../es6.md)

Support for constants (also known as "immutable variables"), i.e., variables which cannot be re-assigned new content. Notice: this only makes the variable itself immutable, not its assigned content (for instance, in case the content is an object, this means the object itself can still be altered).

### ES6

```js
const PI = 3.141593;
```

### ES5

```js
/**
 * only in ES5 through the help of object properties
 * and only in global context and not in a block scope
 */
Object.defineProperty(typeof global === 'object' ? global : window, "PI", {
    value:        3.141593,
    enumerable:   true,
    writable:     false,
    configurable: false
});
```
