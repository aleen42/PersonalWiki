## Reflect [Back](../JavaScript.md)

**Reflect** is a global built-in project provided since ES6 for interceptable operations in JavaScript. It provides static methods as the same as those of **proxy handlers**. Like **Math**, it is not a function object, so it is not constructible.

```js
const obj = { a: 1, b: 2 };

// Detect whether an object has specified properties
Reflect.has(obj, 'a'); // => true
Reflect.has(obj, 'c'); // => false

// Get owned keys
Reflect.ownKeys(obj); // => ["a", "b"], equivalent to `Object.keys(obj)`

// Set keys
Reflect.set(obj, 'c', 3); // => true, equivalent to `Object.assign(obj, {c : 3})`
Reflect.defineProperty(obj, 'd', { value: 4 }); // => true
Reflect.has(obj, 'c'); // => true
Reflect.has(obj, 'd'); // => true

// Delete keys
Reflect.deleteProperty(obj, 'c'); // => true, equivalent to `delete obj.c`  
Reflect.has(obj, 'c'); // => false
```

Except for operating objects, we can also do it with functions:

```js
function test(a, b, c) { console.log(a, b, c); }

// Call functions
Reflect.apply(test, window, [1, 2, 3]); // => 1 2 3, equivalent to `test.apply(window, [1, 2, 3])`
// Constructor
Reflect.constructor(test, [1, 2, 3]); // => equivalent to `new test(1, 2, 3)` 
```
