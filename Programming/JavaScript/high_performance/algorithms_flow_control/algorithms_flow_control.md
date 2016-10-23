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

Aside from `for-in` loop, all other loop types have the same performance characteristics. Therefore, type won't be a factor of performance, but there're actually two other factors you may consider:

- Work done per iteration
- Number of iterations

##### **Decrease the work per iteration**

A typical array-processing loop can be created using any of the three fast loop types.

The code is most frequently written as follows:

```js
/** original loops */
for (var i = 0; i < items.length; i++) {
    process(item[i]);
}

var j = 0;
while (j < items.length) {
    process(items[j++]);
}

var k = 0;
do {
    process(items[k++]);
} while (k < items.length);
```

Consider the code snippet above, `items.length` will always be accessed per iteration, and it's absolutely an optimizing point for us. Depending on the length of the array, we can save around 25% off the total loop execution time in most browsers (even up to 50% in IE).

```js
/** minimize numbers of accessing properties of objects by storing it into a local variable */
for (var i = 0, len = items.length; i < len; i++) {
    process(item[i]);
}

var j = 0;
var count = items.length;
while (j < count) {
    process(items[j++]);
}

var k = 0;
var num = items.length;
do {
    process(items[k++]);
} while (k < num);
```

Besides that, reversing loop order is a common performance optimization in programming languages but generally isn't very well understood. In JavaScript, reversing a loop does result in a small performance improvement for loops, provided that you eliminate extra operations as a result:

```js
/** reverse loop order */
for (var i = items.length; i--; ) {
    process(item[i]);
}

var j = items.length;
while (j--) {
    process(items[j]);
}

/** remember not to access outside the array */
var k = items.length - 1;
do {
    process(items[k]);
} while (k--);
```

So why it's more faster? The control condition has been changed from two comparisons (is the iterator less than the total and is that equal to `true`) to just a single one (is that value `true`). Cutting down from two comparisons to one speeds up the loops even further. With reversing loop order and minimizing the number of accessing properties, the execution time can be up to 50%-60% faster than the original one.

> Note that: decreasing the work down per iteration is most effective when the loop has a complexity of O(n). When it's more complex than O(n), it's advisable to decrease the number of iterations.

##### **Decreasing the number of iterations**

Even the fastest code in a loop body will add up when iterated thousands of times. Therefore, we also need to decrease the nubmer of iterations, and the most well know approach to do this is a pattern called *Duff's Device*.

A typical implementation should look like this:

```js
/** credit: Jeff Greenberg */
var iterations = Math.floor(items.length / 8);
var startAt = itmes.length % 8;
var i = 0;

do {
    switch (startAt) {
    case 0: process(items[i++]);
    case 7: process(items[i++]);
    case 6: process(items[i++]);
    case 5: process(items[i++]);
    case 4: process(items[i++]);
    case 3: process(items[i++]);
    case 2: process(items[i++]);
    case 1: process(items[i++]);
    }

    startAt = 0;
} while (--iterations);
```

The basic idea behind this Duff's Device implementation is that each iteration through the loop is allowed a maximum of eight calls to `process()`.

A slightly faster version of this algorithm is to remove the `switch` statement and to separate the remainder process from the main one:

```js
/** credit: Jeff Greenberg */
var i = itmes.length % 8;

while (i) {
    process(items[i--]);
}

i = Math.floor(items.length / 8);

while (i) {
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
    process(items[i--]);
}
```

> Note that: if you have a loop at a large mounts of iterations, for instance, 500000, and the execution time with Duff's Device is up to 70% less than a regular loop.

#### Function-Based Iteration

`forEach()` is a function defined for you to iterate an array object, which will get three arguments for iterations, and it's implemented natively in Firefox, Chrome, and Safari:

```js
items.foreach(function (value, index, array) {
    /** loop body */
});
```

In addition, most JavaScript libraries have the logical equivalent:

```js
/** YUI 3 */
Y.Array.each(items, function (value, index, array) {
    /** loop body */
});

/** jQuery */
jQuery.each(items, function (index, value) {
    /** loop body */
});

/** Dojo */
dojo.forEach(items, function (value, index, array) {
    /** loop body */
});

/** Prototype */
items.each(function (value, index) {
    /** loop body */
});

/** MooTools */
$each(items, function (value, index) {
    /** loop body */
});
```

Even though function-based iteration represents a more convenient method for iteration, however, in all cases, function-based iteration takes up to eight times as long as loop-based iteration, because of the overhead associated with an extra method being called on each array item.

### Conditionals

Similar in nature to loops, conditionals determine how execution flows through JavaScript. Since different browsers have implemented different flow control optimizations, it's not always clear which technique to use.

#### `if-else` Versus `switch`

The prevailing theory on using `if-else` or `switch` is based on the number of conditions, for easier readable code. As it turns out, the `switch` statement is faster in most cases when compared to `if-else`, but **significantly faster when the number of conditions is large**. Generally speaking, `if-else` is best used when there are two values or a few different ranges of values, and there're more than two values, the `switch` statement is the most optimal choice.

#### Optimizing `if-else`

When optimizing the `if-else` statement, the goal is always to minimize the number of conditions to evaluate before taking the correct path. Considering the following case:

```js
if (value < 5) {
    /** do something */
} else if (value > 5 && value < 10) {
    /** do something */
} else {
    /** do something */
}
```

This code is optimal only if `value` is most frequently less than 5, and get the correct path when only using one condition to evaluate. If not, you can optimize it to obey the principle: **More frequent the condition it is, sooner evaluated it should be**.

#### Lookup Tables

Sometimes, `if-else` or `switch` are both not the best choice for you, when there're a large number of conditions. In reverse, you should use a lookup tables, which can be created using arrays or regular objects. In addition, lookup tables will get code more readable for you:

```js
/** switch statement */
switch (value) {
    case 0: return result0;
    case 1: return result1;
    case 2: return result2;
    case 3: return result3;
    case 4: return result4;
    case 5: return result5;
    case 6: return result6;
    case 7: return result7;
    case 8: return result8;
    case 9: return result9;
    case 10: return result10;
}

/** lookup tables */
var results = [result0, result1, result2, result3, result4, result5, result6, result7, result8, result9, result10];

return results[value];
```

Lookup tables are most useful when there's logical mapping between a single key and a single value, while a `switch` statement is more appropriate when each key requires a unique action or set of actions to take place.

Of course, when conditions are not enumerable, lookup tables or `switch` won't be a choice for you.

### Recursion

Complex algorithms are typically made easier by using recursion.

```js
function factorial(n) {
    if (n === 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
```

The problem with recursive functions is that missing a terminal condition can lead to the long execution time, blocking the user interface. Further, recursive functions are more likely to run into browser call stack size limit.
