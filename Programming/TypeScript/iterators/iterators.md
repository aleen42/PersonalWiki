## Iterators [Back](../TypeScript.md)

Since ECMAScript 2015(ES6), an object, like `Array`, `Map`, `Set`, `String`, `Int32Array`, `Uint32Array`, etc., has been deemed iterable if it has an implementation of [`Symbol.iterator`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol/iterator) property:

```typescript
console.log('123'[Symbol.iterator]); /** => ƒ [Symbol.iterator]() { [native code] } */
```

The property has also ben used by `for...of` statements:

```typscript
const arr = [1, 'string', false];
for (const value of arr) {
    console.log(value); /** 1, 'string', false */
}
```

Similar to `for...of` statements, `for...in` statements are mainly used for accessing keys of iterable objects.

When targeting an ES5 or ES3 within TypeScript, iterators are only allowed on values of `Array` type, and the compiler will automatically generate a simple `for` loop for a `for...of` loop, for instance:

```typescript
let numbers = [1, 2, 3];
for (let num of numbers) {
    console.log(num);
}
```

will be generated as:

```typescript
var numbers = [1, 2, 3];
for (var _i = 0; _i < numbers.length; _i++) {
    var num = numbers[_i];
    console.log(num);
}
```
