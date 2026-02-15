## Symbol [Back](../TypeScript.md)

`Symbol` is a primitive data type arisen from ECMAScript 2015(ES6), which purpose is to be an identifier for object properties. It means that it is immutable and unique:

```typescript
console.log(Symbol() === Symbol()); /** => false */

const obj = {
    id: Symbol(),
};
```

Just like strings, symbols can also be used as keys for object properties:

```typescript
const str = 'key';
const symbol = Symbol('key');

const obj = {
    [str]: 'value',
    [symbol]: 'symbol value',
};
```

Certainly, the member have to be accessed with specific declared symbol:

```typescript
console.log(obj[symbol]); /** => symbol value */
console.log(obj[Symbol('key')]); /** undefined */
```

Can we generate an unreachable property in this way?

```typescript
const obj = {
    [(() => Symbol('key'))()]: 'unreachable value',
};
```

We cannot access including using `for...in` operators, except `Object.getOwnPropertySymbols()`.

```typescript
console.log(obj[Object.getOwnPropertySymbols(obj)[0]]); /** => 'unreachable value' */ 
```

For more details around `Symbol` including its built-in methods, we can check [the document](https://www.typescriptlang.org/docs/handbook/symbols.html#well-known-symbols) from TypeScript or [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol) directly.
