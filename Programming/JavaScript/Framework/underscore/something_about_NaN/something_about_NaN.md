## NaN? [Back](./../underscore.md)

Before talking about something about `NaN`, we should know that what it means. Actually `NaN` is also called as Not-A-Number value, which means that the value is not a number. It's usually returned as a result after failed to calculate some expression like `Math.sqrt(-1)`, or `parseInt('number')`. Of course, you may also have seen `Number.NaN`, which is completely same as `NaN`. Furthermore, they're both Number types:

```js
console.log(Object.prototype.toString.call(NaN)); /** => "[object number]" */
console.log(Object.prototype.toString.call(Number.NaN)); /** => "[object number]" */
```
