## NaN? [Back](./../underscore.md)

Before talking about something about `NaN`, we should know that what it means. Actually `NaN` is also called as Not-A-Number value, which means that the value is not a number. It's usually returned as a result after failed to calculate some expression like `Math.sqrt(-1)`, or `parseInt('number')`. Of course, you may also have seen `Number.NaN`, which is completely same as `NaN`. Furthermore, they're both Number types:

```js
console.log(Object.prototype.toString.call(NaN)); /** => "[object number]" */
console.log(Object.prototype.toString.call(Number.NaN)); /** => "[object number]" */
```

Although `NaN` is a Number, it is not equal to itself:

```js
console.log(NaN == NaN); /** => false */
console.log(NaN === NaN); /** => false */
```

However, the global method `isNaN` will always return true when judging whether a value is `NaN`:

```js
isNaN(NaN); /** => true */
isNaN(undefined); /** => true */
isNaN({}); /** => true */
isNaN('number'); /** => true */
```

That's because the value passed into the method will be firstly converted into Number types:

```js
Number(NaN); /** => NaN */
Number(undefined); /** => NaN */
Number({}); /** => NaN */
Number("abc"); /** => NaN */
```

Then, ES6 has imported `Number.isNaN()` to judge strictly:

```js
isNaN = function (value) {
    return Number(value) === NaN;
};

Number.isNaN = Number.isNaN || function (value) {
    return typeof value === 'number' && isNaN(value);
};
```

However, this implementation still have a problem:

```js
Number.isNaN(new Number(NaN)); /** => false */
```

Therefore, underscore has fixed by implementing this:

```js
_.isNaN = function (obj) {
    return Object.prototype.toString.call(obj) === '[object Number]' && obj !== +obj;
};
```

But this causes a huge problem:

```js
_.isNaN(new Number(0)); /** => true */
_.isNaN(new Number(1)); /** => true */
```

Therefore, the most elegant way to implement this method should be:

```js
_.isNaN = function (obj) {
    return Object.prototype.toString.call(obj) === '[object Number]' && isNaN(obj);
};
```
