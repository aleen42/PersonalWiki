## How to know the valueOf() method [Back](./qa.md)

In ECMAScript 5, the method `valueOf()` is defined as followed:

> when the **valueOf** method is called, the following steps are taken:

> 1. Let `O` be the result of calling **ToObject** passing the **this** value as the argument.

> 2. If `O` is the result of calling the Object constructor with a host object, then return either `O` or another value such as the host object originally passed to the constructor. The specific result that is returned is implementation-defined.

> 3. return `O`.

To put it simple, this method will call `ToObject(this)`, and return different things according to this:

- `this` is the original object, returning will depends on different browsers.
- `this` is not the original object, returning will return the mothod `ToObject(this)`.

Parameter Types|Return
:-------------:|:-----
undefined|Throw `TypeError` Exception
null|Throw `TypeError` Exception
Number|Create a Number Object and pass `this` into the constructor
String|Create a String Object and pass `this` into the constructor
Boolean|Create a Boolean Object and pass `this` into the constructor
Object|`this`

Object Types|Return
:----------:|:-----
undefined|Throw `TypeError` Exception
null|Throw `TypeError` Exception
Number|Create a Number Object whose value is equivalent to the object itself
String|Create a String Object whose value is equivalent to the object itself
Boolean|Create a Boolean Object whose value is equivalent to the object itself
Object|The Object itself

#### Example

```js
var num = 123;
console.log(num.valueOf());                    /** => 123           */
console.log(typeof num);                       /** => number        */
console.log(typeof num.valueOf());             /** => number        */

var num = new Number(123);
console.log(num.valueOf());                    /** => 123           */
console.log(typeof num);                       /** => object        */
console.log(typeof num.valueOf());             /** => number        */
```
