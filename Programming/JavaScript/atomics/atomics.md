## Atomics [Back](../JavaScript.md)

**Atomics** is a global built-in projects provided since ES6 for operating [`SharedArrayBuffer`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/SharedArrayBuffer) and [`ArrayBuffer`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/ArrayBuffer) in JavaScript. Like **Math**, it is not a function object, so it is not constructible.

```js
const ab = new ArrayBuffer(1024);
const ta = new Uint8Array(ab);

ta[0]; // => 0
ta[0] = 5;

Atomics.add(ta, 0, 12); // => 5
Atomics.load(ta, 0); // => 17

Atomics.sub(ta, 0, 2); // => 17
Atomics.load(ta, 0); // => 15

Atomics.and(ta, 0, 1); // => 15
Atomics.load(ta, 0); // => 1

Atomics.or(ta, 0, 12); // => 1
Atomics.load(ta, 0); // => 13

Atomics.xor(ta, 0, 1); // => 13
Atomics.load(ta, 0); // => 12

// compared with expected, and replace if matched
Atomics.compareExchange(ta, 0, 5, 7); // => 12
Atomics.load(ta, 0); // => 12
Atomics.compareExchange(ta, 0, 12, 7); // => 12
Atomics.load(ta, 0); // => 7

// replace directly and return the old value
Atomics.exchange(ta, 0, 12); // => 7
Atomics.load(ta, 0); // => 12

// store directly and return the stored value
Atomics.store(ta, 0, 2); // => 2
Atomics.load(ta, 0); // => 2

/**
 * determine whether the Atomics methods use locks or atomic hardware
 * operations when applied to typed arrays with the given element byte size.
 */
Atomics.isLockFree(1); // => true
Atomics.isLockFree(2); // => true
Atomics.isLockFree(3); // => false
Atomics.isLockFree(4); // => true
Atomics.isLockFree(5); // => false
Atomics.isLockFree(6); // => false
Atomics.isLockFree(7); // => false
Atomics.isLockFree(8); // => true
```

If different threads have used the same data constructed with `SharedArrayBuffer`, one can wait for expected data in a specific index position by using `Atomics.wait`, while the other can notify up this sleeping thread by using `Atomics.notify`. (Note: These operations work with a shared `Int32Array` only.)
