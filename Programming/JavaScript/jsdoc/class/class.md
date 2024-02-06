## @class [Back](../jsdoc.md)

> This tag is the same with @constructor

The tag `@class`, a.k.a `@constructor` is mainly used for marking a function as being a constructor, which means that callers need to use `new` statement to create an instance of such a method.

```js
/**
* a constructor for Person objects
* @constructor
*/
function Person () {}

const person = new Person();
```
