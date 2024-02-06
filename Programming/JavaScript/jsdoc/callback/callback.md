## @callback [Back](../jsdoc.md)

The `@callback` tag is mainly used for specified callback function that can be passed to other functions.

```js
/**
 * other function
 * @param {otherCallback} cb - a callback method
 */
function other(cb) {
    /** ... */
    cb(200, 'Success');
}

/**
 * The callback for calling other methods
 * @callback otherCallback
 * @param {number} code
 * @param {string} message
 */
```
