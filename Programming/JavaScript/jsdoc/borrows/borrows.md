## @borrows [Back](../jsdoc.md)

The `@borrows` tag allows you to borrow some documents from another symbol to the current one. It is useful especially when there are many references, where you don't want to duplicate the same documentation.

```js
/**
 * email tool
 * @function 
 */
function email_tool() {}

module.exports = {
    /**
     * email
     * @borrows email_tool as email 
     */
    email: email_tool,
};
```
