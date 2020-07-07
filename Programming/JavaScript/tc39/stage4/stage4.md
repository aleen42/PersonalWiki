## Stage 4 (Finished) [Back](../tc39.md)

This note refers to [the official collections](https://github.com/tc39/proposals/blob/master/finished-proposals.md).

### 1. `Array.prototype.includes`

```typescript
Array.prototype.includes = function (searchElement: T, fromIndex?: number): boolean;
```

> Author: Domenic Denicola
>
> Expected Publication Year: 2016
>
> https://github.com/tc39/Array.prototype.includes

Sometimes we may need to detect whether an array has am expected element:

```js
/** without it before */
console.log([1, 2, 3].indexOf(1) > -1); /** => true */
/** with Array.prototype.includes */
console.log([1, 2, 3].includes(1)); /** => true */
```

And why not use `has` instead? The author said that `has` is used for conceptual "keys", while `includes` is used for conceptual "values". This proposal is just an extension like what `String.prototype.includes` to `String.prototype.indexOf`.

In addition, there is some illustrative examples for this proposal:

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

### 3. `Object.{values, entries}`

> Author: Jordan Harband
>
> Expected Publication Year: 2017
>
> https://github.com/tc39/proposal-object-values-entries

As for we can get all keys of an JavaScript object through `Object.keys`, why can't we use some supported methods to export all values or even key-value pairs of such an object?

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

To support padding a string with given minimal length of such a string.

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

Since we can get descriptor from an object with given key, why can't we get all descriptors of an object with nature methods without looping each time?

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

Sometimes it is common to toggle function parameters with new lines for prettier format:

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

### 9. Lifting template literal restriction

> Author: Tim Disney
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-template-literal-revision

When it comes to template literal, there is a way we can handle string template with tagged methods like the following snippet:

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

That is because `\u` is the start of a unicode escape in JavaScript, like `\u00FF` or `\u{42}`, resulting in considering `\unicode` as illegal. The similar cases also happen with `\x`, `\0100`. After this proposal, tagged template literals will remove the restriction.

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

However, there are more line terminator characters are outside the specification, which make developers confusing:

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

If you are familiar with regular expressions in JavaScript, you should know how to use capturing groups for matching and storing what we need. However, the order of multiple groups is always confusing especially when we have a sufficient complicated expressions. After this proposal, we can name groups without knowing the order any more.

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

So why are matched values stored in a property named `groups`, but not the result itself? Obviously, it is helpful for solving the problem of naming conflicts. If there are no named capturing groups, the value of such a property should be `undefined`.

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

With lookahead assertions (`(?!...)`) supported before in JavaScript, we can easily find a word which is not a specified one as mentioned in [the note](../../regular/words_lines_special/words_lines_special.md#find-all-except-a-specific-word). However, the language does not support lookbehind assertions to do this in a reversed way as [another note](../../regular/words_lines_special/words_lines_special.md#find-any-word-not-preceded-by-a-specific-word) said. Since that proposal, we can also do this easily by using `(?<=...)`.

To clearly know the meaning of assertions in JavaScript regular expressions, I have refereed to the example of MDN:

1. Lookahead assertions (`/x(?=y)/`): Matches "x" only if "x" is followed by "y".
2. Negative lookahead assertions (`/x(?!y)/`): Matches "x" only if "x" is not followed by "y".
3. Lookbehind assertions (`/(?<=y)x/`): Matches "x" only if "x" is preceded by "y".
4. Negative lookbehind assertions (`/(?<!y)x/`): Matches "x" only if "x" is not preceded by "y".

### 14. RegExp Unicode Property Escapes

> Author: Mathias Bynens
>
> Expected Publication Year: 2018
>
> https://github.com/tc39/proposal-regexp-unicode-property-escapes

With this proposal, developers can access the set of unicode symbols, that are used exclusively in some specified script, in a regular expression by setting with a Unicode Property `\p{...}` and `\P{...}` with `u` flags:

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

    An async iterator is much like an iterator, except that its next() method returns a promise for a `{value, done}` pair.

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

    The proposal introduces that we can iterate some async function in sequential like that:

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
    * The behavior of `yield*` is modified to support delegation to async iterables.

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

After this proposal, you can definitely remove this unused pattern:

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
- for functions defined using ECMAScript code, `toString` must return source text slice from beginning of first token to end of last token matched by the appropriate grammar production
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
