## Stage 4 (Finished) [Back](../tc39.md)

This note refers to [the official collections](https://github.com/tc39/proposals/blob/master/finished-proposals.md).

### 1. Array.prototype.includes

```typescript
Array.prototype.includes = function (searchElement: T, fromIndex?: number): boolean;
```

> Author: Domenic Denicola

> Expected Publication Year: 2016

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

### 2. Exponentiation operator

> Author: Rick Waldron

> Expected Publication Year: 2016

To support exponentiation with `**` notation.

```js
console.log(Math.pow(2, 2)); /** => 4 */
console.log(2 ** 2); /** => 4 */
console.log(2 ** (1 / 2)); /** => 1.4142135623730951 */
```

### 3. Object.values / Object.entries

> Author: Jordan Harband

> Expected Publication Year: 2017

As for we can get all keys of an JavaScript object through `Object.keys`, why can't we use some supported methods to export all values or even key-value pairs of such an object?

```js
console.log(Object.keys({a: 1, b: 2})); /** => ['a', 'b'] */

console.log(Object.values({a: 1, b: 2})); /** => [1, 2] */
console.log(Object.entries({a: 1, b: 2})); /** => [['a', 1], ['b', 2]] */
```

### 4. String.prototype.padStart / String.prototype.padEnd

```typescript
String.prototype.padStart = function (maxLength: number, fillString?: string): string;
String.prototype.padEnd = function (maxLength: number, fillString?: string): string;
```

> Author: Jordan Harband

> Expected Publication Year: 2017

To support padding a string with given minimal length of such a string.

```js
console.log('abc'.padStart(4)); /** => " abc" */
console.log('abc'.padEnd(4)); /** => "abc " */
console.log('abc'.padEnd(1)); /** => "abc" */
console.log('abc'.padStart(4, '-').padEnd(5, '-')); /** => "-abc-" */
```

### 5. Object.getOwnPropertyDescriptors

```typescript
Object.getOwnPropertyDescriptors = function <T>(o: T): {
    [P in keyof T]: TypedPropertyDescriptor<T[P]>} & { [x: string]: PropertyDescriptor
};
```

> Author: Jordan Harband, Andrea Giammarchi

> Expected Publication Year: 2017

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

> Expected Publication Year: 2017

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

> Expected Publication Year: 2017

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

> Expected Publication Year: 2017

### 9. Lifting template literal restriction

> Author: Tim Disney

> Expected Publication Year: 2018

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

> Expected Publication Year: 2018

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

> Expected Publication Year: 2018

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

> Expected Publication Year: 2018

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
