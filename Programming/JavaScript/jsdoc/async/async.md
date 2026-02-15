## @async [Back](../jsdoc.md)

The `@async` tag indicates that a function is **asynchronous**, which means that the function you called should return a promise.

*Note: **DO NOT** use this tag for other types of asynchronous functions, like functions that provide a callback.*

```js
/**
* asynchronous function
* @async
* @returns {Promise<*>}
*/
function asynchronous() {
    return new Promise((resolve, reject) => {});
}

async function main() {
    await asynchronous();
}
```
