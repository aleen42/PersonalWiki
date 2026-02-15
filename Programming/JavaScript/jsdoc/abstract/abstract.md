## @abstract [Back](../jsdoc.md)

> This tag is the same with @virtual

It is used to specify members that must be implemented (or overridden) for base classes.

```js
/**
 * Base class
 * @constructor
 */
class Base {
    /**
     * fn method of the base class
     * @abstract
     * @returns {boolean}
     */
    fn() { return true; }
}

/**
 * inherited class
 * @constructor
 */
class Inherit extends Base {
    /**
     * fn method of the inherited class
     * @returns {boolean}
     */
    fn() { return false; }
}
```
