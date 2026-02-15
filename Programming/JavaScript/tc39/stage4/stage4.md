## Stage 4 (Finished) [Back](../tc39.md)

This note refers to [the official collections](https://github.com/tc39/proposals/blob/master/finished-proposals.md).

## ECMAScript 2016

### 1. `Array.prototype.includes`

```typescript
Array.prototype.includes = function (searchElement: T, fromIndex?: number): boolean;
```

> Author: Domenic Denicola
>
> Expected Publication Year: 2016
>
> https://github.com/tc39/Array.prototype.includes

Sometimes we may need to detect whether an array has an expected element:

```js
/** without it before */
console.log([1, 2, 3].indexOf(1) > -1); /** => true */
/** with Array.prototype.includes */
console.log([1, 2, 3].includes(1)); /** => true */
```

And why not use `has` instead? The author said that `has` is used for conceptual "keys", while `includes` is used for conceptual "values". This proposal is just an extension like what `String.prototype.includes` to `String.prototype.indexOf`.

In addition, there are some illustrative examples for this proposal:

```js
console.log([1, 2, NaN].includes(NaN)); /** => true */

console.log([1, 2, -0].includes(+0)); /** => true */
console.log([1, 2, +0].includes(-0)); /** => true */

console.log([1, 2, 3].includes(1, 1)); /** => false */
```

### 2. Exponentiation operator (`**`)

> Author: Rick Waldron
>
> Expected Publication Year: 2016
>
> https://github.com/tc39/proposal-exponentiation-operator

To support exponentiation with `**` notation.

```js
console.log(Math.pow(2, 2)); /** => 4 */
console.log(2 ** 2); /** => 4 */
console.log(2 ** (1 / 2)); /** => 1.4142135623730951 */
```

## ECMAScript 2017

### 3. `Object.{values, entries}`

> Author: Jordan Harband
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/proposal-object-values-entries

As for we can get all keys of a JavaScript object through `Object.keys`, why can't we use some supported methods to export all values or even key-value pairs of such an object?

```js
console.log(Object.keys({a: 1, b: 2})); /** => ['a', 'b'] */

console.log(Object.values({a: 1, b: 2})); /** => [1, 2] */
console.log(Object.entries({a: 1, b: 2})); /** => [['a', 1], ['b', 2]] */
```

### 4. `String.prototype.{padStart, padEnd}`

```typescript
String.prototype.padStart = function (maxLength: number, fillString?: string): string;
String.prototype.padEnd = function (maxLength: number, fillString?: string): string;
```

> Author: Jordan Harband
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/proposal-string-pad-start-end

To support padding a string with a given minimal length of such a string.

```js
console.log('abc'.padStart(4)); /** => " abc" */
console.log('abc'.padEnd(4)); /** => "abc " */
console.log('abc'.padEnd(1)); /** => "abc" */
console.log('abc'.padStart(4, '-').padEnd(5, '-')); /** => "-abc-" */
```

### 5. `Object.getOwnPropertyDescriptors`

```typescript
Object.getOwnPropertyDescriptors = function <T>(o: T): {
    [P in keyof T]: TypedPropertyDescriptor<T[P]>} & { [x: string]: PropertyDescriptor
};
```

> Author: Jordan Harband, Andrea Giammarchi
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/proposal-object-getownpropertydescriptors

Since we can get a descriptor from an object with a given key, why can't we get all descriptors of an object with natural methods without looping each time?

```js
const obj = {a: 1};

console.log(Object.keys(obj).reduce((descriptors, key) => Object.assign(descriptors, {
   [key]: Object.getOwnPropertyDescriptor(obj, key),
}), {}));
/** => {a: {value: 1, writable: 1, enumerable: true, configurable: true}} */
console.log(Object.getOwnPropertyDescriptors(obj));
/** => {a: {value: 1, writable: 1, enumerable: true, configurable: true}} */
```

The following illustrative snippet has shown more usages around such a nature method:

```js
/** shallow clone */
const shallowClone = obj => Object.create(
   Object.getPrototypeOf(obj),
   Object.getOwnPropertyDescriptors(obj)
);
/** shallow merge */
const shallowMerge = (target, source) => Object.defineProperties(
   target,
   Object.getOwnPropertyDescriptors(source)
);

/** mixin solution */
const mix = obj => ({
    with : (...mixins) => mixins.reduce((c, mixin) => shallowMerge(c, mixin), obj),
});

console.log(mix({a: 1}).with({b: 2}, {c: 3})); /** => {a: 1, b: 2, c: 3} */
```

### 6. Trailing commas in function parameters lists

> Author: Jeff Morrison
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/proposal-trailing-function-commas

Sometimes it is common to toggle function parameters with new lines for a prettier format:

```js
function test(
   param1,
   param2,
   param3
) {
   /** ... */
}
```

With this proposal, you can add trailing commas in the list of parameters like trailing commas in array or object:

```js
/** trailing commas in function parameter lists */
function test(
   param1,
   param2,
   param3,
) {
   /** ... */
   /** trailing commas in objects */ 
   const obj = {
      a: 1,
      b: 2,
    };
   
   /** trailing commas in arrays */
   const arr = [
      1,
      2,
   ];
}
```

### 7. Async / Await

More detailed for asynchronous programming at [here](../../async_programming/async_programming.md).

> Author: Brian Terlson
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/ecmascript-asyncawait

```js
const tasks = [
   () => new Promise(resolve => setTimeout(resolve.bind(0, 1), 1000)).then(console.log),
   () => Promise.resolve(2).then(console.log),
];

(async function () {
   await tasks[0]();
   await tasks[1]();
})(); /** => 1, 2 */

(() => {
   tasks[0]();
    tasks[1]();
})(); /** => 2, 1 */
```

### 8. Shared Memory and Atomics

> Author: Lars T Hansen
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/ecmascript_sharedmem

## ECMAScript 2018

### 9. Lifting template literal restriction

> Author: Tim Disney
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-template-literal-revision

When it comes to a template literal, there is a way we can handle string templates with tagged methods like the following snippet:

```js
function tag(strings, ...expressions) {
   console.log(strings);
   console.log(expressions);
}

/** => ["That is ", " and ", "", raw: Array(3)] */
/** => ["A", "B"] */
tag`That is ${'A'} and ${'B'}`;
```

However, before this proposal, the following cases are illegal:

```js
function latex(strings) {}

latex`
    \newcommand{\fun}{\textbf{Fun!}} /** works just fine */
    \newcommand{\unicode}{\textbf{Unicode!}} /** Illegal token! */
    \newcommand{\xerxes}{\textbf{King!}} /** Illegal token! Breve over the h goes */
    \u{h}ere /** Illegal token! */
`;
```

That is because `\u` is the start of a Unicode escape in JavaScript, like `\u00FF` or `\u{42}`, resulting in considering `\unicode` as illegal. Similar cases also happen with `\x`, `\0100`. After this proposal, tagged template literals will remove the restriction.

```js
tag`\unicode`; /** works fine */
```

### 10. `s` (`dotAll`) flag for regular expressions

> Author: Mathias Bynens
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-regexp-dotall-flag

In JavaScript regular expressions, the dot notation `.` does not match all like line terminator characters:

```js
console.log(/./.test('\u000a')); /** => false - LINE FEED (LF) (\n) */
console.log(/./.test('\u000d')); /** => false - CARRIAGE RETURN (CR) (\r) */
console.log(/./.test('\u2028')); /** => false - LINE SEPARATOR */
console.log(/./.test('\u2029')); /** => false - PARAGRAPH SEPARATOR */
```

However, there are more line terminator characters that are outside the specification, which make developers confusing:

```js
console.log(/./.test('\u000b')); /** => true - VERTICAL TAB (\v) */
console.log(/./.test('\u000c')); /** => true - FORM FEED (\f) */
console.log(/./.test('\u0085')); /** => true - NEXT LINE */
```

That's why we need some workarounds to match anything with regular expressions in JavaScript, like `[\s\S]` or `[^]`.

With this proposal we can solve this problem with passing `s`:

```js
console.log(/./s.test('\u000a')); /** => true - LINE FEED (LF) (\n) */
console.log(/./s.test('\u000d')); /** => true - CARRIAGE RETURN (CR) (\r) */
console.log(/./s.test('\u2028')); /** => true - LINE SEPARATOR */
console.log(/./s.test('\u2029')); /** => true - PARAGRAPH SEPARATOR */
```

In addition, `s` flag does not stands for `singleline`, in comparison with `m` flag for `multiline`, because `dotAll` seems like it has given a much better description. When both the `s` (`dotAll`) and `m` (`multiline`) flags are set, `.` matches any character while still allowing `^` and `$` to match.

```js
console.log(/^.$/sm.test(`
    test
`)); /** => true */

console.log(/^.$/m.test(`
    test
`)); /** => false */
```

### 11. Named capturing groups in regular expressions

> Author: Gorkem Yakin, Daniel Ehrenberg
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-regexp-named-groups

If you are familiar with regular expressions in JavaScript, you should know how to use capturing groups for matching and storing what we need. However, the order of multiple groups is always confusing especially when we have a sufficient complicated expression. After this proposal, we can name groups without knowing the order anymore.

```js
console.log(/(\d{4})-(\d{2})-(\d{2})/.exec('2019-07-15'));
/** => ["2019-07-15", "2019", "07", "15", index: 0, input: "2019-07-15", groups: undefined] */
console.log(/(?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2})/.exec('2019-07-15').groups);
/** => {year: "2019", month: "07", day: "15"} */
```

Certainly, there are some advanced usages as the proposal specified:

1. References to capturing groups within expressions:
    ```js
    console.log(/(\d{2})-\1/.test('08-07')); /** => false */
    console.log(/(\d{2})-\1/.test('08-08')); /** => true */

    console.log(/(?<month>\d{2})-\k<month>/.test('08-08')); /** => true */
    ```

2. references to capturing groups within replacement:
    ```js
    console.log('2019-07-15'.replace(
       /(?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2})/,
       '$<year>/$<month>/$<day>'
    )); /** => 2019/07/15 */

    console.log('2019-07-15'.replace(
        /(?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2})/,
        (...args) => {
           const {day, month, year} = args[args.length - 1];
           return `${year}/${month}/${day}`;
        })); /** => 2019/07/15 */
    ```

So why are matched values stored in a property named `groups`, but not the result itself? It helps solve the problem of naming conflicts. If there are no named capturing groups, the value of such a property should be `undefined`.

When it comes to references, the `\k<name>` syntax may have compatible problems when you want to match a literal string `"k<name>"`. In such a case, the result depends on whether or not the expression has a named group, `name`. If it does has, it should be a reference.

### 12. Rest / Spread Properties

> Author: Sebastian Markbåge
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-object-rest-spread

ECMAScript 2015 (ES6) has introduced **rest** for array destructuring assignment and **spread** for array literals.

```js
const [a, b, ...rest] = [1, 2, 3, 4];
console.log(rest); /** => [3, 4] */

console.log([1, 2, ...[3, 4]]); /** => [1, 2, 3, 4] */
```

As for this proposal, it has introduced the same concept for objects:

```js
const {a, b, ...c} = {a: 1, b: 2, x: 3, y: 4};
console.log(c); /** => {x: 3, y: 4} */

console.log({a: 1, b: 2, ...{x: 3, y: 4}}); /** => {a: 1, b: 2, x: 3, y: 4} */
```

### 13. RegExp Lookbehind Assertions (`(?<=)`, `(?<!)`)

> Author: Gorkem Yakin, Nozomu Katō, Daniel Ehrenberg
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-regexp-lookbehind

With lookahead assertions (`(?!...)`) supported before in JavaScript, we can easily find a word which is not a specified one as mentioned in [the note](../../regular/words_lines_special/words_lines_special.md#find-all-except-a-specific-word). However, the language does not support look behind assertions to do this in a reversed way as [another note](../../regular/words_lines_special/words_lines_special.md#find-any-word-not-preceded-by-a-specific-word) said. Since that proposal, we can also do this easily by using `(?<=...)`.

To know the meaning of assertions in JavaScript regular expressions, I have referred to the example of MDN:

1. Lookahead assertions (`/x(?=y)/`): Matches "x" only if "x" is followed by "y".
2. Negative lookahead assertions (`/x(?!y)/`): Matches "x" only if "x" is not followed by "y".
3. Lookbehind assertions (`/(?<=y)x/`): Matches "x" only if "x" is preceded by "y".
4. Negative look behind assertions (`/(?<!y)x/`): Matches "x" only if "x" is not preceded by "y".

### 14. RegExp Unicode Property Escapes

> Author: Mathias Bynens
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-regexp-unicode-property-escapes

With this proposal, developers can access the set of Unicode symbols, that are used exclusively in some specified script, in a regular expression by setting with a Unicode Property `\p{...}` and `\P{...}` with `u` flags:

```js
/\p{UnicodePropertyName=UnicodePropertyValue}/u
```

The aliases of **UnicodePropertyName** and **UnicodePropertyValue** has been defined in [`PropertyAliases.txt`](http://unicode.org/Public/UNIDATA/PropertyAliases.txt) and [`PropertyValueAliases.txt`](http://unicode.org/Public/UNIDATA/PropertyValueAliases.txt). For example, if we want to match some Greek characters:

```js
/\p{Script=Greek}/u.test('π'); /** => true */
```

For binary options, the following syntax is available like `Alphabetic`, `Math`, or `Uppercase`:

```js
/\p{LoneUnicodePropertyNameOrValue}/u
```

This syntax may also be used as a shorthand for `General_Category` values, e.g. `\p{Letter}` instead of `\p{General_Category=Letter}`.

### 15. `Promise.prototype.finally`

> Author: Jordan Harband
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-promise-finally

With `Promise.prototype.finally`, we do not need to use `Promise.prototype.then(func, func)` to handle fulfilled or rejected state at the same time anymore.

In addition, `finally` won't change the result of a promise chain:

```js
Promise.resolve(1).then(() => {}, () => {}); /** => resolve undefined */
Promise.resolve(1).finally(() => {}); /** => still resolve 1 */
```

### 16. Asynchronous Iteration

> Author: Domenic Denicola
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-async-iteration

Since we can use async / await as [the proposal](#7-async--await) said, we also need a feature to support asynchronous iteration so that developers can iterate some promises, especially when the next promise replies on the previous one. The proposal has introduced three types of iterations: the **AsyncIterator** interface, an asynchronous iteration statement (`for-await-of`), and async generator functions.

1. the **AsyncIterator** interface

    An async iterator is much like an iterator, except that the `next()` method returns a promise for a `{value, done}` pair.

    ```js
    const {value, done} = syncIterator.next();

    asyncIterator.next().then(({value, done}) => { /** ... */ });
    ```

    To create a synchronous iterator which can be used by `for...of`:

    ```js
    const iterator = {
        [Symbol.iterator]: function* () {
           yield 1;
           yield 2;
           yield 3;
        },
    };

    console.log([...iterator]); /** => 1 2 3 */
    for (const val of iterator) { console.log(val); } /** => 1, 2, 3 */
    ```

    To create an asynchronous iterator which can be used by `for await...of`:

    ```js
    const asyncIterator = {
        [Symbol.asyncIterator]: function* () {
           yield 1;
           yield 2;
           yield 3;
        },
    };

    (async () => {
        for await (const val of asyncIterator) { console.log(val); } /** => 1, 2, 3 */ 
    })();
    ```

2. An asynchronous iteration statement (`for await...of`)

    The proposal introduces that we can iterate some async functions in sequential like that:

    ```js
    (async () => {
        for await (const task of tasks()) { console.log(task); }
    });
    ```

    *Note that: statements are only allowed within async function and async generator functions.*

3. Async generator functions

    Async generator functions are similar to generator functions, with the following differences:

    * When called, async generator functions return an object, an *async generator* whose methods (`next`, `throw`, and `return`) return promises for `{ value, done }`, instead of directly returning `{ value, done }`. This automatically makes the returned async generator objects *async iterators*.
    * `await` expressions and `for`-`await`-`of` statements are allowed.
    * The behaviour of `yield*` is modified to support delegation to async iterable.

    For example:

    ```js
    async function* readLines(path) {
       let file = await fileOpen(path);
    
       try {
          while (!file.EOF) {
             yield await file.readLine();
          }
       } finally {
          await file.close();
       }
    } 
    ```

## ECMAScript 2019

### 17. Optional `catch` binding

> Author: Michael Ficarra
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-optional-catch-binding

Before this proposal, you cannot omit the parameter and have to define the variable even if you want to ignore it:

```js
try { /** do something */ } catch (ignore) {}
```

After this proposal, you can remove this unused pattern:

```js
try { /** do something */ } catch {}
```

### 18. `JSON` superset

> Author: Richard Gibson
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-json-superset

A proposal to extend [ECMA-262](http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-262.pdf) syntax into a superset of JSON.

### 19. `Symbol.prototype.description`

> Author: Michael Ficarra
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-Symbol-description

A read-only property to return the optional description of a `Symbol` object:

```js
console.log(Symbol().description); /** => undefined */
console.log(Symbol('').description); /** => "" */
console.log(Symbol('desc').description); /** => "desc" */
console.log(Symbol('desc').toString()); /** => "Symbol(desc)" */

/** a well-known symbol */
console.log(Symbol.iterator.description); /** => "Symbol.iterator" */
/** global symbols */
console.log(Symbol.for('foo').description); /** => "foo" */
```

### 20. `Function.prototype.toString` revision

> Author: Michael Ficarra
>
> Expected Publication Year: 2019
>
> https://tc39.es/Function-prototype-toString-revision/

A proposal of a revision at `Function.prototype.toString`:

- ensure that the string's parse contains the same function body and parameter list as the original
- for functions defined using ECMAScript code, `toString` must return source text slice from beginning of the first token to end of the last token matched by the appropriate grammar production
- for built-in function objects and [bound function](https://tc39.github.io/ecma262/#sec-bound-function-exotic-objects) exotic objects, `toString` must not return anything other than [NativeFunction](https://tc39.es/Function-prototype-toString-revision/#prod-NativeFunction)
- for callable objects which were not defined using ECMAScript code, `toString` must return [NativeFunction](https://tc39.es/Function-prototype-toString-revision/#prod-NativeFunction)
- for functions created dynamically (through the Function and GeneratorFunction constructors), `toString` must synthesise a source text
- for all other objects, `toString` must throw a TypeError exception
- implementations must not be required to retain source text for all functions defined using ECMAScript code

### 21. `Object.fromEntries`

> Author: Darien Maillet Valentine
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-object-from-entries

Aims to do reversal operation of `Object.entries`, like [`_.formPairs`](https://lodash.com/docs/4.17.4#fromPairs) in Lodash:

```js
console.log(Object.entries({a: 1, b: 2})); /** => [["a", 1], ["b", 2]] */
console.log(Object.fromEntries([['a', 1], ['b', 2]])); /** => {a: 1, b: 2} */
```

### 22. Well-formed `JSON.stringify`

> Author: Richard Gibson
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-well-formed-stringify

Aims to prevent `JSON.stringify` from returning ill-formed Unicode strings:

```js
console.log(JSON.stringify('\uD834\uDF06')); /** => "𝌆" */
console.log(JSON.stringify('\uDF06\uD834')); /** => "\\udf06\\ud834" rather than "��" */
```

### 23. `String.prototype.{trimStart, trimEnd, trimLeft, trimRight}`

> Author: Sebastian Markbåge
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-string-left-right-trim

A proposal to support trim in one side of a string. `trimLeft` and `trimRight` are just aliases of `trimStart` and `trimEnd`.

```js
console.log(' foo '.trimLeft()); /** => "foo " */
console.log(' foo '.trimRight()); /** => " foo" */
console.log(' bar '.trimStart()); /** => "bar " */
console.log(' bar '.trimEnd()); /** => " bar" */
```

### 24. `Array.prototype.{flat, flatMap}`

> Author: Brian Terlson, Michael Ficarra, Mathias Bynens
>
> Expected Publication Year: 2019
>
> https://github.com/tc39/proposal-flatMap

With `Array.prototype.flat`, developers can operate an array by concatenating all child arrays into it recursively up to the specified depth. For example:

```js
console.log([1, [2, [3]], 4].flat()); /** => [1, 2, [3], 4], specify depth as 1 by default */
console.log([1, [2, [3]], 4].flat(1)); /** => [1, 2, [3], 4] */
console.log([1, [2, [3]], 4].flat(2)); /** => [1, 2, 3, 4] */
```

With `Array.prototype.flatMap`, we can flat each child item via 1 depth of an array after map it:

```js
console.log([{a: 1}, {a : [2, [3]]} , {a:4 }].flatMap(({a}) => a)); /** => [1, 2, [3], 4] */
```

## ECMAScript 2020

### 25. `String.prototype.matchAll`

> Author: Jordan Harband
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/String.prototype.matchAll

With this proposal, we don't need to use a `RegExp` object to execute matching some patterns within a string anymore. For Example, if we want to match all `test` keywords within a sentence, we may implement the requirement like this before:

```js
const sentence = 'This is a test case where we can test a case of matching several patterns.';
const regex = /test/g;
const matches = [];

let match;
while (match = regex.exec(sentence)) {
   matches.push(match);
}

console.log(matches); /** => [["test", index: 10, input: "xxx", groups: undefined], ["test", index: 33, input: "xxx", groups: undefined]] */
```

After that, we can use `String.prototype.matchAll` to do so:

```js
const matches = [...'This is a test case where we can test a case of matching several patterns.'.matchAll(/test/g)];

console.log(matches); /** => [["test", index: 10, input: "xxx", groups: undefined], ["test", index: 33, input: "xxx", groups: undefined]] */
```

*Notice that: `String.prototype.matchAll` will return an iterator, named as `RegExpStringIterator`.*

### 26. `import()`

> Author: Domenic Denicola
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-dynamic-import

As we know, `import` cannot be called dynamically like this before:

```js
if (es3) { /** Syntax Error: statement expected */ 
   import 'core-js/shim';
}
```

Since this proposal, we can use `import` statement like calling a function, which will return a promise:

```js
if (es3) {
   import('core-js/shim').then(module => { /** do something with the module */ });
}
```

### 27. BigInt

> Author: Daniel Ehrenberg
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-bigint


`BigInt` is a new primitive which provides a way to represent whole numbers larger than 2<sup>53</sup>, which is the largest number Javascript can reliably represent with the `Number` primitive.

```js
console.log(Number.MAX_SAFE_INTEGER); /** => 9007199254740991, this is 1 less than 2^53 */
console.log(Number.MAX_SAFE_INTEGER + 1); /** => 9007199254740992, OK */
console.log(Number.MAX_SAFE_INTEGER + 2); /** => 9007199254740992, same above */
console.log(Number.MAX_SAFE_INTEGER + 3); /** => 9007199254740994, OK again? */
console.log(Number.MAX_SAFE_INTEGER + 4); /** => 9007199254740994, Emmmmm */
```

There is some syntax you may need to know when using `BigInt`:

```js
const bigInt = 9007199254740991n;
const bigInt1 = BigInt(9007199254740991);
const bigInt2 = BigInt('9007199254740991');
```

We can apply arithmetic operations as well as power (`**`) and mod (`%`) operations on `BitInt`, but should with `BitInt` as the right value at the same time:

```js
console.log(BigInt(Number.MAX_SAFE_INTEGER) + 1n); /** => 9007199254740992n, OK */
console.log(BigInt(Number.MAX_SAFE_INTEGER) + 1); /** => Error: Uncaught TypeError: Cannot mix BigInt and other types, use explicit conversions */
```

When it comes to division (`/`), what you may need to know is that what you get should be rounded as it is an integer to some extent.

```js
console.log(4n / 2n); /** => 2n */
console.log(3n / 2n); /** => 1n, but not 1.5n */
```

When compare `BitInt` with `Number`, it equals when not strictly:

```js
console.log(1n == 1); /** => true */
console.log(1n === 1); /** => false */

console.log(1n < 2); /** => true */
console.log(2n > 2); /** => false */
console.log(2 > 2); /** => false */
console.log(2 > 2n); /** => false */
console.log(2 >= 2n); /** => true */
```

Also, `0n` is the same as `0`, which will be treated as `false` in conditions:

```js
console.log(0n || 'else'); /** => "else" */
```

Some situations of converting between `BitInt` and `Number` should be noticed:

1. Initializing:

    ```js
    BigInt(1.5); /** => RangeError: The number 1.5 is not a safe integer and thus cannot be converted to a BigInt */
    BigInt('1.5'); /** => SyntaxError: Cannot convert 1.5 to a BigInt */ 
    ```

2. Operating:

    ```js
    Math.round(1n); /** => TypeError: Cannot convert a BigInt value to a number */
    Math.max(1n, 10n); /** => TypeError: Cannot convert a BigInt value to a number */

    1n | 0; /** TypeError: Cannot mix BigInt and other types, use explicit conversions */ 
    ```

3. Parsing:

    ```js
    parseFloat(1234n); /** => 1234 */
    parseInt(10n); /** => 10 */ 

    parseInt(900719925474099267n); /** => 900719925474099300, lose precision */
    ```

4. Serializing:

    ```js
    JSON.stringify({a: 10n}); /** => TypeError: Do not know how to serialize a BigInt */ 
    ```

For more advanced usages, please visit [here](https://github.com/tc39/proposal-bigint/blob/master/ADVANCED.md).

### 28. `Promise.allSettled()`

> Author: Jason Williams, Robert Pamely, Mathias Bynens
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-promise-allSettled

In comparison with `Promise.all()`, `Promise.allSettled()` returns a promise that is fulfilled with an array of results, whenever all promises have settled, even if some promises have been rejected. `Promise.all()` will immediately return a promise rejected with the first rejected promise result.

```js
(async () => {
   const successful = (await Promise.allSettled([fetch('source1'), fetch('source2')])).filter(/* promise = */({status}) => status === 'fulfilled');
})();
```

There is an example to show the exact difference between `Promise.all()` and `Promise.allSettled()`:

```js
(async () => {
   const requests = ['source1', 'source2'];
    
   try {
        await Promise.all(requests);
        console.log('All requests have completed; now I can remove the loading indicator.');
    } catch {
        console.log('At least one request has failed, but some of the requests still might not be finished! Oops.');
    }
    
    /** We know all API calls have finished. We use finally but allSettled will never reject. */
    Promise.allSettled(requests).finally(() => {
        console.log('All requests are completed: either failed or succeeded, I don’t care');
        /** remove loading ... */
    });
})();
```

### 29. `globalThis`

> Author: Jordan Harband
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-global

In JavaScript, it should be a hot topic to discuss how to access the global object:

- Web: `window (Window)`, `self (WindowProxy)`, `this (WindowProxy)`, or `frames (WindowProxy)`
- Node: `global` (not available in shell-like V8's `d8`, or JavaScript Core's `jsc`), or `this`

In a global standalone function, we can access the global object via `this`, but not in module function or strict mode within a function (`use strict;`). In such a case, we can also access the global object via `Function('return this')()`, although it can result in performance problems like using `eval`. However, this way is still not available in some [CSP settings](https://github.com/paulmillr/es6-shim/issues/301), like Chrome apps.

Here is a snippet to conclude what was mentioned above:

```js
function getGlobal() {
    return typeof window != 'undefined' ? window /** Web */
        : (typeof process === 'object' && typeof require === 'function' && typeof global === 'object') ? global /** Node */
            : this || Function('return this')(); /** module function / strict mode */
}
```

So what is the difference between `window` and `globalThis`? As the page changes, `globalThis` maintains the same identity of `window`, while `window` is swapped out.

Take an example in the proposal, where there are two sources of the frame, `a.html` and `b.html`.

```html
<!-- a.html -->
<script>
    globalThis.foo = 'a';
    globalThis.getGlobalThis = () => globalThis;
</script>
```

```html
<!-- b.html -->
<script>
    globalThis.getGlobalThis = () => globalThis;
</script>
```

When we simulate that the page changes between two contents, we will find that `window.foo` will be lost while `globalThis.foo` is not:

```html
<iframe src="a.html"></iframe>
<script>
    const iframe = document.querySelector('iframe');
    iframe.onload = () => {
        console.log(frames[0].foo); /** window.foo => 'a' */ 
        const before = frames[0].getGlobalThis();
        console.log(before.foo); /** globalThis.foo => 'a' */

        iframe.onload = () => {
            console.log(frames[0].foo) /** window.foo => undefined */;
            console.log(before === frames[0].getGlobalThis()); /**  => true */
            console.log(before.foo); /** globalThis.foo => 'a' */
        };
        iframe.src = 'b.html';
    };
</script>
```

In my opinion, `globalThis` is a special existence that stands for a higher level of global environments between different frames. Sometimes we may not distinguish it from the so-called "global object" easily.

### 30. `for-in` mechanics

> Author: Kevin Gibbons
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-for-in-order

This proposal aims to create a convention about the order of iterating a JavaScript Object via some APIs:

- [`Object.keys`](https://tc39.es/ecma262/#sec-object.keys)
- [`Object.values`](https://tc39.es/ecma262/#sec-object.values)
- [`Object.entries`](https://tc39.es/ecma262/#sec-object.entries)
- [`JSON.parse`](https://tc39.es/ecma262/#sec-json.parse) via [`InternalizeJSONProperty`](https://tc39.es/ecma262/#sec-internalizejsonproperty)
- [`JSON.stringify`](https://tc39.es/ecma262/#sec-json.stringify) via [`SerializeJSONObject`](https://tc39.es/ecma262/#sec-serializejsonobject)

Including the `for ... in` statement itself.

### 31. Optional Chaining

> Author: Gabriel Isenberg, Claude Pache, Dustin Savery
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-optional-chaining

Before this proposal, when we hope to avoid problems of NPE (Null Pointer Exceptions) in JavaScript, we may code like this:

```js
const street = user && user.address && user.address.street;
const done = cb => { /** do something before callback */ cb && cb(); };
```

After that, we can simplify it:

```js
const street = user?.address?.street;
const done = cb => { /** do something before callback */ cb?.(); };
```

### 32. Nullish coalescing Operator

> Author: Gabriel Isenberg
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-nullish-coalescing

Before this proposal, when we want to assign a variable with a fallback default value, we usually use `||` notation like this:

```js
const options = {};
options.yes = yes || true;
```

However, when it comes to falsy value like zero (`0`), falsy boolean (`false`), or an empty string (`""`), we usually do not expect to fallback as it is a meaningful value sometimes:

```js
const options = {};
options.index = index || -1; /** fallback to -1 when index is 0 */
```

This proposal aims to handle this situation by making fallback condition strictly to only `undefined` or `null`:

```js
const options = {};
options.index = index ?? -1; /** fallback to -1 only when index is `null` or `undefined` */
```

### 33. `import.meta`

> Author: Domenic Denicola
>
> Expected Publication Year: 2020
>
> https://github.com/tc39/proposal-import-meta

Since ES6, there are ES modules corresponding to CommonJS modules in NodeJS, and in 2018, we can write a module with `.mjs` extension file, and require them with `<script type="module" src="xxx.mjs"></script>`.

However, some meta information of ES modules still misses before this proposal like `__dirname`, `__filename`, `module` in CommonJS modules. With `import.meta` we can get some meta information of current module like using `import.meta.url` for getting the URL of current module; `import.meta.scriptElement.dataset` for getting `data-` attribute specified in the script tag.

## ECMAScript 2021

### 34. `String.prototype.replaceAll`

> Author: Peter Marshall, Jakob Gruber, Mathias Bynens
>
> Expected Publication Year: 2021
>
> https://github.com/tc39/proposal-string-replaceall

When it comes to how to replace all specified substrings inside a string, we may use regex or splitting and joining before:

```js
console.log('a+b+c'.replace(/\+/g, '-')); /** => "a-b-c" */
console.log('a+b+c'.split('+').join('-')); /** => "a-b-c" */
```

With this proposal:

```js
console.log('a+b+c'.replaceAll('+', '-')); /** => "a-b-c" */

console.log('a+b+c'.replaceAll(/\+/, '-')); /** => Uncaught TypeError: String.prototype.replaceAll called with a non-global RegExp argument */
console.log('a+b+c'.replaceAll(/\+/g, '-')); /** => "a-b-c" */
```

### 35. `Promise.any`

> Author: Mathias Bynens, Kevin Gibbons, Sergey Rubanov
>
> Expected Publication Year: 2021
>
> https://github.com/tc39/proposal-promise-any

The proposal can be described with a table:

| name                                          | description                                             |
|:----------------------------------------------|:--------------------------------------------------------|
| [`Promise.allSettled`](#28-promiseallsettled) | does not short-circuit until all promises are settled   |
| `Promise.all`                                 | short-circuits when one promise is rejected             |
| `Promise.race`                                | short-circuits when one promise is settled              |
| `Promise.any`                                 | short-circuits when one promise is resolved (fulfilled) |

### 36. WeakRefs

> Author: Dean Tribble, Sathya Gunasekaran
>
> Expected Publication Year: 2021
>
> https://github.com/tc39/proposal-weakrefs

This proposal has mainly described two new advanced features for us: `WeakRef` and `FinalizationRegistry`.

`WeakRef` mainly aims to help developers referring to large objects without holding them longer in memory. Assume that there is a collection of large images constructed of `ArrayBuffer`:

```js
const weakCacheOf = fn => {
    const cache = new Map(); /** Map<WeakRef> */
    return key => {
        let cached;
        const ref = cache.get(key);
        if (ref && (cached = ref.deref())) return cached; /** WeakRef.deref() will return `undefined` when referenced item has been GC */
        
        const item = fn(key);
        cache.set(key, new WeakRef(item)); /** store weak references to large images */
        return item;
    };
};

const getCachedImage = weakCacheOf(getImage);
```

`FinalizationRegistry` mainly aims to help developers to know whether a specified object is reclaimed during GC through a callback. For example:

```js
const registry = new FinalizationRegistry(val => {
    /**
    * Callback the second parameter you passed when registering.
    * It also means that the responding object you registered has been reclaimed.
    */
});

registry.register(objectA, 'The Object A');
registry.register(objectB, 'The Object B');
```

If you don't want to observe them later, you may need to pass a third value, which is something like a registration token:

```js
registry.register(objectC, 'The Object C', objectC);
/** ... */
registry.unregister(objectC);
```

Combine `WeakRef` with `FinalizationRegistry`, we can simply create a weak cache like this:

```js
const weakCacheOf = fn => {
    const cache = new Map()/** Map<WeakRef> */, cleanup = new FinalizationRegistry(key => {
        const ref = cache.get(key);
        ref && !ref.deref() && cache.delete(key); /** release the reference key when the item is GC */
    });

    return key => {
        let cached;
        const ref = cache.get(key);
        if (ref && (cached = ref.deref())) return cached; /** WeakRef.deref() will return `undefined` when referenced item has been GC */
        
        const item = fn(key);
        cache.set(key, new WeakRef(item)); /** store weak references to large images */
        cleanup.register(item, key);
        return item;
    };
};

const getCachedImage = weakCacheOf(getImage);
```

### 37. Logical Assignment Operators

> Author: Justin Ridgewell
>
> Expected Publication Year: 2021
>
> https://github.com/tc39/proposal-logical-assignment

Combine Logical Operators and Assignment Expressions:

```js
a &&= b;
a && (a = b);

a ||= b;
a || (a = b);

a ??= b;
a ?? (a = b);
```

### 38. Numeric Separators

> Author: Sam Goto, Rick Waldron
>
> Expected Publication Year: 2021
>
> https://github.com/tc39/proposal-numeric-separator

Simply, numeric separators help readers to identify the digit of a number. That's like we always use `1,000,000,000` to describe 1 billion rather than `1000000000`.

This proposal has stated that using underscores notation (`_`) to separate for us:

```js
console.log(1_000_000_000); /** => 1000000000 */
console.log(0.000_001); /** => 0.000001 */
console.log(0b1010_0001_1000_0101); /** => 41349 */
console.log(0xA0_B0_C0); /** => 10531008 */
console.log(1_000_000_000_000n); /** => 1000000000000n */
console.log(0o1234_5670); /** => 2739128 */
```

## ECMAScript 2022

### 39. Class Fields

> Author: Daniel Ehrenberg
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-private-methods, https://github.com/tc39/proposal-class-fields, https://github.com/tc39/proposal-static-class-features

The major features of those proposals have respectively stated:

- Public and private instance fields of Classes

    With ES2015, there is no way to define private instance fields:

    ```js
    class X {
       constructor() {
          this.foo = 'public instance';
       }
       
       method() {
          return this.foo;
       }
    }
    
    class Y extends X {
       constructor() {
          super();
          this.foo = void 0; // extend with undefined
       }
    }
    
    console.log((new Y()).method()); // => undefined
    ```

    With the new proposal, you can define it and a public one in a more convenient way:

    ```js
    class X {
        foo = 'public instance';
        #bar = 'private instance'; // private instance fields
        
        method() {
           return [this.foo, this.#bar];
        }
    }
    
    class Y extends X {
       foo; // extend with undefined 
    }
    
    console.log((new Y()).method()); // => [undefined, "private instance"]
    ```

- Private instance methods and accessors (getter/setter)

    ```js
    class X {
       #bar = 'private instance'; // private instance fields
       
       get #b() { return this.#bar; }
       set #b(value) {
          // ...
          this.#bar = value;
       }
       
       #method() {
          return this.#b;
       }
    }
    
    class Y extends X {}
    
    console.log((new Y()).method); // => undefined
    ```

- Static class fields and private static methods

    It is quite useful for defining a utility class:

    ```js
    class HTML {
        static encode = val => `${val}`
            .replace(/&/g, '&amp;')
            .replace(/>/g, '&gt;')
            .replace(/</g, '&lt;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#39;');
    
        static decode = val => `${val}`
            .replace(/&amp;/gi, '&')
            .replace(/&lt;/gi, '<')
            .replace(/&gt;/gi, '>')
            .replace(/(&quot;|&#034;|&#34;)/gi, '"')
            .replace(/(&#039;|&#39;)/gi, "'")
            .replace(/&nbsp;/gi, ' ');
    }

    console.log(HTML.encode('&gt;')); // => "&amp;gt;"
    console.log(HTML.decode('&gt;')); // => ">" 
    ```

### 40. RegExp Match Indices

> Author: Ron Buckton
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-regexp-match-indices

This proposal has provided additional information about the start and end indices of captured substrings relative to the start of the input string when specifying RegExp with `d` notation.

```js
const {indices} = /a+(?<Z>z)?/d.exec('xaaaz');

console.log('xaaaz'.slice(...indices[0])); // => "aaaz"
console.log('xaaaz'.slice(...indices[1])); // => "z"
console.log('xaaaz'.slice(...indices.groups['Z'])); // => "z"
```

### 41. Top-level Await

> Author: Myles Borins, Yulia Startsev, Daniel Ehrenberg, Guy Bedford, Ms2ger
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-top-level-await

After the proposal, we don't need to wrap top-level `await` calling inside an `async` function anymore:

```js
(async () => {
   await Promise.resolve(1);
})();

await Promise.resolve(1); // => 1
```

### 42. Ergonomic brand checks for Private Fields

> Author: Jordan Harband
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-private-fields-in-in

To avoid throwing error when using `this.#brand` to detect whether the private field has existed:

```js
class C {
    get #brand() {
        throw new Error('exception');
    }
    
    static isBrandExisted(instance) {
        try {
            instance.#brand;
            return true;
        } catch {
            return false;
        }
    }
}

console.log(C.isBrandExisted(new C())); // => false
```

The proposal has described another way to detect with `in` notation:

```js
class C {
    get #brand() {
        throw new Error('exception');
    }
    
    static isBrandExisted(instance) {
        return #brand in instance;
    }
}

console.log(C.isBrandExisted(new C())); // => true
```

Remember that it obeys the rule of OOP: Cannot access the private field outside the class' lexical scope.

```js
console.log(#brand in new C()); // => Uncaught SyntaxError: Private field '#brand' must be declared in an enclosing class
```


### 43. `.at()`

> Author: Shu-yu Guo, Tab Atkins
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-relative-indexing-method

A proposal to add the`.at()` method to all the basic indexable classes (`Array`, `String`, `TypedArray`), so that we can access negative indexes meaning the position from the last:

```js
console.log([1, 2, 3].at(0)); // => 1
console.log(new Int8Array([1, 2, 3]).at(0)); // => 1
console.log('123'.at(0)); // => "1"

console.log([1, 2, 3].at(-1)); // => 3
console.log(new Int8Array([1, 2, 3]).at(-1)); // => 3
console.log('123'.at(-1)); // => "3"
```

### 44. `Object.hasOwn`

> Author: Jamie Kyle
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-accessible-object-hasownproperty

With this proposal, you won't need to implement a separated method for checking owned properties of an object like this:

```js
const hasOwn = Object.prototype.hasOwnProperty
hasOwn.call(obj, 'foo');
```

It has described `Object.hasOwn` for you:

```js
Object.hasOwn(obj, 'foo');
```

### 45. Class Static Blocks

> Author: Ron Buckton
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-class-static-block

The proposal has described a static block statement for us where we can do more complicated initialization of static fields.

1. To evaluate static fields with predefined one inside the class definition:

    ```js
    // Before the proposal
    class C {
        static x = ['foo', 'bar'];
        static y;
        static z;
    }
    
    C.y = C.x[0];
    C.z = C.x[1];
    ```

    ```js
    // After the proposal
    class C {
        static x = ['foo', 'bar'];
        static {
            this.y = this.x[0];
            this.z = this.x[1];
        }
    }
    ```

2. Access scopes inside the class definition:

    ```js
    // Before the proposal
    let getX;
    class C {
        #x;
        constructor(x) { this.#x = {data: x}; }
        static getX = instance => instance.#x;
    }
    
    getX = C.getX;
    console.log(getX(new C('instance'))); // => {data: "instance"}
    ```

    ```js
    // After the proposal
    let getX;
    class C {
        #x;
        static getX;
        constructor(x) { this.#x = {data: x}; }
        static {
            getX = this.getX = instance => instance.#x;
        }
    }
    
    console.log(getX(new C('instance'))); // => {data: "instance"}
    ```

### 46. Error Cause

> Author: Chengzhong Wu
>
> Expected Publication Year: 2022
>
> https://github.com/tc39/proposal-error-cause

This proposal aims to provide an optional parameter for the `Error()` constructor with a `cause` property to help chain errors, so that we can trace them according to the stack.

```js
try {
    await fetch('//error').catch(err => {
        throw new Error('Caused by', {cause: err});
    });
} catch (e) {
    console.log(`${e}\n\t${e.cause}`); // => Error: Caused by
                                       // =>     TypeError: Failed to fetch  
}
```

## ECMAScript 2023

### 47. Array find from last

> Author: Wenlu Wang
>
> Expected Publication Year: 2023
>
> https://github.com/tc39/proposal-array-find-from-last

This proposal is for introducing two methods: `Array.prototype.findLast` and `Array.prototype.findLastIndex()`, with which we can find the last matched item and its index easily, in comparison with `Array.prototype.find()` and `Array.prototype.findIndex()`:

```js
[1, 2, {a : 1}, {a : 1, b : 2}].findLast(item => item?.a === 1); // => {a: 1, b: 2}
[1, 2, {a : 1}, {a : 1, b : 2}].find(item => item?.a === 1); // => {a: 1}

[1, 2, {a : 1}, {a : 1, b : 2}].findLastIndex(item => item?.a === 1); // => 3
[1, 2, {a : 1}, {a : 1, b : 2}].findIndex(item => item?.a === 1); // => 2
```

Without this proposal, we may need to reverse it first:

```js
[1, 2, {a : 1}, {a : 1, b : 2}].reverse().find(item => item?.a === 1); // => {a: 1, b: 2}
[1, 2, {a : 1}, {a : 1, b : 2}].reverse().findIndex(item => item?.a === 1); // => 3
```

### 48. Hashbang Grammar

> Author: Bradley Farias
>
> Expected Publication Year: 2023
>
> https://github.com/tc39/proposal-hashbang

With this proposal, the JavaScript engine can unify and standardize the usages of Hashbang (`#!`), and we don't need to strip it before passing:

```js
#!/usr/bin/env node
// JavaScript
'use strit';
console.log(1);
```

### 49. Symbols as WeakMap keys

> Author: Daniel Ehrenberg, Richard Button, Robin Ricard, Leo Balter, Rick Waldron, Caridy Patiño
>
> Expected Publication Year: 2023
>
> https://github.com/tc39/proposal-symbols-as-weakmap-keys

With this proposal, we add an item into the [`WeakMap`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakMap) with a key of [`Symbol`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol):

```js
const weak = new WeakMap();
weak.set(Symbol('key'), { /* data */ });
```

Nevertheless, [registered symbols](https://tc39.es/ecma262/multipage#sec-symbol.for) are limited to use according to the [issue 21](https://github.com/tc39/proposal-symbols-as-weakmap-keys/issues/21):

```js
const weak = new WeakMap();
weak.set(Symbol.for('a'), {}); // Throws "Uncaught TypeError: Invalid value used as weak map key"
```

While [well-Known symbols](https://tc39.es/ecma262/multipage#sec-well-known-symbols) are allowed:

```js
const weak = new WeakMap();
weak.set(Symbol.iterator, {}); // OK
```

### 50. Change Array by copy

> Author: 	Ashley Claymore, Robin Ricard
>
> Expected Publication Year: 2023
>
> https://github.com/tc39/proposal-change-array-by-copy

The proposal provides additional methods on `Array.prototype` and `TypedArray.prototype` to avoid changing on the array by returning a new copy of it with the change, in comparison with some methods which will touch the target like `Array.prototype.reverse()`, `Array.prototype.sort()`, `Array.prototype.splice()`, etc.

```js
const sequence = [1, 2, 3];
sequence.toReversed(); // => [3, 2, 1]
sequence; // => [1, 2, 3]

const outOfOrder = new Uint8Array([3, 1, 2]);
outOfOrder.toSorted(); // => Uint8Array [1, 2, 3]
outOfOrder; // => Uint8Array [3, 1, 2]

const correctionNeeded = [1, 1, 3];
correctionNeeded.with(1, 2); // => [1, 2, 3]
correctionNeeded; // => [1, 1, 3]
```
