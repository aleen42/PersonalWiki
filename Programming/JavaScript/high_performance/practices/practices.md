## Programming Practices [Back](./../high_performance.md)

Every programming language has pain and inefficient patterns that develop over time. Therefore, we should also focus on some patterns in our programming.

### 1. Avoid Double Evaluation

JavaScript, like many scripting languages, allows you to take a string code and execute it from within running code, by using `eval()`, the `Function()` constructor, `setTimeout()`, and `setInterval()`.

```js
var num1 = 5;
var num2 = 6;

var result = eval('num1 + num2');

var sum = new Function('arg1', 'arg2', 'return arg1 + arg2');

setTimeout('sum = num1 + num2', 100);

setInterval('sum = num1 + num2', 100);
```

Whenever you're evaluating JavaScript code from within JavaScript code, you should suffer from a double evaluation penalty. The code is first evaluated as normal, and then, while executing, another evaluation happens to execute the code contained in a string.

Most of time, there is no need to use `eval()` or `Function()`, and it's best to avoid them whenever possible. For the other two function, `setTimeout()` and `setInterval()`, it's recommended to pass in a function as the first argument instead of a string.

> Optimizing JavaScript engines often cache the result of repeated code evaluations using `eval()`. If you are repeatedly evaluating the same code string, you will see greater performance improvements in Safari 4 and all versions of Chrome.

### 2. Use Object/Array Literals

There're multiple ways to create objects and arrays in JavaScript, but nothing is faster than creating them with literals.

Not only are literals evaluated faster, as an added bonus, but literals will also take up less space in the code.

### 3. Don't Repeat Work

One of the primary performance optimization techniques in computer science overall is **work avoidance**. It means two things:

- Don't do work that is not required.
- Do not repeat work that has already been completed.

Probably during our developing, browser detection is the most common type of repeated work. Take event handler as example:

```js
function addHandler(target, eventType, handler) {
    if (target.addEventListener) {
        target.addEventListener(eventType, handler, false);
    } else {
        target.attachEvent('on' + eventType, handler);
    }
}
```

Each time the method is called, the same check is made to see whether `addEventListener` is supported in the current browser.

So how can we optimize this?

#### 3.1 Lazy Loading

The first way to eliminate repeated work is through **lazy loading**, which means that no work is done until the information is necessary. Take the snippet above as an example, we can optimize like this:

```js
function addHandler(target, eventType, handler) {
    if (target.addEventListener) {
        addHandler = function (target, eventType, handler) {
            target.addEventListener(eventType, handler, false);
        }
    } else {
        addHandler = function (target, eventType, handler) {
            target.attachEvent('on' + eventType, handler);
        }
    }

    addHandler(target, eventType, handler);
}
```

#### 3.2 Conditional Advance Loading

An alternative to lazy loading function is **conditional advance loading**, which does the detection in advance, and the load a proper function.

```js
var addHandler = document.body.addEventListener ?
    function (target, eventType, handler) {
        target.addEventListener(eventType, handler, false);
    } :
    function (target, eventType, handler) {
        target.attachEvent('on' + eventType, handler);
    };
```

The trade off between those two methods is whether to load a function in advance or later. If you don't sure whether this method should be called later, it's recommended to adopt a lazy loading.

### 4. Use the Fast Parts

#### 4.1 Bitwise Operators

Bitwise operators are one of the most frequently misunderstood aspects of JavaScript, because developers don't always understand how to use them.

To understand bitwise operators clearly, we should know how to transfer a decimal number into a binary one:

```js
console.log(Number(25).toString(2)); /** => 11001 */
```

Then, four bitwise logic operators in JavaScript are all listed as followed:

```js
/** bitwise AND */
console.log(Number(25 & 3).toString(2)); /** => 1 (11001 & 00011) */

/** bitwise OR */
console.log(Number(25 | 3).toString(2)); /** => 11011 (11001 | 00011) */

/** bitwise XOR */
console.log(Number(25 ^ 3).toString(2)); /** => 11010 (11001 ^ 00011) */

/** bitwise NOT */
console.log(Number(~25).toString(2)); /** => -11010 (~11001) */
```

There are couples of ways to use bitwise operators to speed up JavaScript, one of which is to use bitwise operations instead of pure mathematical operations. For example, there is a common function to check whether a number is an odd number:

```js
function isOdd(num) {
    return (num % 2 === 1);
}
```

we can optimize it as followed, with speeding up up to 50%:

```js
function isOdd(num) {
    return !!(num & 1);
}
```

The second way to use bitwise operators is a technique known as **bitmasks**, which is popular especially when designing options:

```js
const OPTION_A = 1;
const OPTION_B = 2;
const OPTION_C = 4;
const OPTION_D = 8;
```

Then we can create a configuration with multiple options set:

```js
var configuration = OPTION_A | OPTION_C;
```

To check whether a configuration has been set with some specific option like OPTION_A:

```js
if (options & OPTION_A) {
    /** has been set with OPTION_A */
}
```

> JavaScript also supports left shift (`<<`), right shift (`>>`), and signed right shift (`>>>`) bitwise operators.

#### 4.2 Native Methods

No matter how optimal your JavaScript code is, it will never be faster than the native methods provided by the JavaScript engine.

For example, the `Math` object contains properties and methods designed to make mathematical operations easier. There are several mathematical constants available:

Constant|Meaning
--------|-------
Math.E|The value of E, the base of the natural logarithm
Math.LN10|The natural logarithm of 10
Math.LN2|The natural logarithm of 2
Math.LOG2E|The base-2 logarithm of E
Math.LOG10E|The base-10 logarithm of E
Math.PI|The value of π
Math.SQRT1_2|The square root of ½
Math.SQRT2|The square root of 2

Each of these values has been calculated in advance by the engine, so there is no need for you to calculate them yourself. There are also methods to handle mathematical calculations:

Method|Meaning
------|-------
Math.abs(num)|The absolute value of num
Math.exp(num)|Math.E<sup>num</sup>
Math.log(num)|The logarithm of num
Math.pow(num, power)|num<sup>power</sup>
Math.sqrt(num)|The square root of num
Math.acos(x)|The arc cosine of x
Math.asin(x)|The arc sine of x
Math.atan(x)|The arc tangent of x
Math.atan2(y, x)|The arc tangent of y/x
Math.cos(x)|The cosine of x
Math.sin(x)|The sine of x
Math.tan(x)|The tangent of x

> Chrome actually implements a fair amount of its native JavaScript functionality in JavaScript. Because Chrome uses a just-in-time JavaScript compiler for both native functionality and your code, there is sometimes little performance difference between the two.

### 5. Summary

Performance optimization is always existed in our code, therefore sometimes we should take following cases in mind:

- Avoid the double evaluation penalty of using `eval()` and the `Function()` constructor. Also, pass functions into `setTimeout()` and `setInterval()` instead of strings.
- Use object and array literals to create them.
- Use lazy loading or conditional advance loading when browser-detection logic is necessary.
- When performance mathematical operations, consider using bitwise operators.
- Native methods are always faster.
