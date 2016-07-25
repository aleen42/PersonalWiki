## Promise [Back](./../es6.md)

Promise is used for asynchronous calculating, which is an object which means that it will be done in the future.

```js
var promiseObj = new Promise(function (resolve, reject)) {
    /** calling resolve when the job is done */
    resolve();
    
    /** calling reject when the job failed */
    reject();
};
```

A Promise object will only have **three states**:

- pending: the initial state
- fulfilled: successful state
- rejected: failed state

There are 2 prototype functions: `then()` and `catch()`:

When a Promise object has changed its state, `Promise.prototype.then()` will be called