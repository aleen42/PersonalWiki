## Algorithms and Flow Control [Back](./../high_performance.md)

The overall structure of code will determine as to how fast it will be executed. A lot of performance impact is directly related to how the code has been organized.

This chapter will have some coding techniques discussed for optimizing the performance.

### Loops

In any programming language, the majority of code execution time is spent within loops, and in JavaScript, you can use a loop structure with different ways.

The first is the standard `for` loop:

```js
for (var i = 0; i < 10; i++) {
    /** loop body */
}
```

There are four parts to the `for` loop: initialization, pretest condition, post-execute, and the loop body. When a `for` loop is encountered, the initialization code is executed first, followed by the pretest condition. If the pretest condition evaluates to `true`, then the body of loop will be executed, and then the post-execute code is run.

> Note that: using `var` statement in the initialization part will create a functional-level variable, which does not belong to a block scope. It means that, after the loop finishes, this variable can still be accessed inside the same function.

The second type is the `while` loop:

```js
var i = 0;

while (i < 10) {
    /** loop body */
    i++;
}
```

The third type of loop is `do-while` loop, and what it differs from `while` loop is that, it's executed at least once.

```js
var i = 0;

do {
    /** loop body */
} while (i++ < 10);
```

The fourth and last loop is `for-in` loop, which aims to enumerates the named properties of any object:

```js
for (var prop in obj) {
    /** loop body */
}
```

#### Loop Performance

Of the four loop types provided by JavaScript, only one of them is significantly slower than the other: the **`for-in`** loop. A `for-in` loop can end up as much as seven times slower than the other loop types. For this reason, it's recommended to avoid using it unless you intent to iterate over an unknown umber of object properties. If you have known list of properties to iterate over, it's faster to use another type of loop:

```js
var props = ['prop1', 'prop2'];
var i = 0;

while (i < props.length) {
    /** access the object with obj[props[i]] */
}
```

> Note that: you should never use `for-in` to iterate over members of an array.
