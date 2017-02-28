## Algorithms and Flow Control [Back](./../high_performance.md)

The overall structure of code will determine as to how fast it will be executed. A lot of performance impact is directly related to how the code has been organized.

This chapter will have some coding techniques discussed for optimizing the performance.

### 1. Loops

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

#### 1.1 Loop Performance

Of the four loop types provided by JavaScript, only one of them is significantly slower than the other: the **`for-in`** loop. A `for-in` loop can end up as much as seven times slower than the other loop types. For this reason, it's recommended to avoid using it unless you intent to iterate over an unknown umber of object properties. If you have known list of properties to iterate over, it's faster to use another type of loop: (Furthurmore, there is also a compatibility problem with using `for-in`, check [the analysis of underscore](./../../Framework/underscore/for_in_compatibility/for_in_compatibility.md))

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

##### 1.1.1 **Decrease the work per iteration**

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

##### 1.1.2 **Decreasing the number of iterations**

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

#### 1.2 Function-Based Iteration

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

### 2. Conditionals

Similar in nature to loops, conditionals determine how execution flows through JavaScript. Since different browsers have implemented different flow control optimizations, it's not always clear which technique to use.

#### 2.1 `if-else` Versus `switch`

The prevailing theory on using `if-else` or `switch` is based on the number of conditions, for easier readable code. As it turns out, the `switch` statement is faster in most cases when compared to `if-else`, but **significantly faster when the number of conditions is large**. Generally speaking, `if-else` is best used when there are two values or a few different ranges of values, and there're more than two values, the `switch` statement is the most optimal choice.

#### 2.2 Optimizing `if-else`

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

#### 2.3 Lookup Tables

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

### 3. Recursion

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

#### 3.1 Call Stack Limits

The amount of recursion supported by JavaScript engines varies and is directly related to the size of the JavaScript call stack. Except for Internet Explorer, for which the call stack is related to available system memory, all other **browsers have static call stack limits**.

Browsers|Firefox 3|Firefox 3.5|Chrome 1|Chrome 2|IE 7|IE 8
:------:|:-------:|:---------:|:------:|:------:|:--:|:---:
Limitation|3000|3000|21837|21837|1789|2232

Browsers|Opera 9.62|Opera 10 Beta|Safari 2|Safari 3.2|Safari 4
:------:|:-------:|:---------:|:------:|:------:|:--:
Limitation|10000|10000|100|500|37448

When the limitation has been exceeded by introducing too much recursion, the browser will error out with one of the following messages:

- Internet Explorer: "Stack overflow at line x"
- Firefox: "Too much recursion"
- Safari: "Maximum call stack size exceeded"
- Opera: "Abort (control stack overflow)"

Perhaps the most interesting part of stack overflow errors is that they are actual JavaScript errors in some browsers, and can therefore be trapped using a `try-catch` statement. The exception type varies based on the browser being used:

- Firefox: `InternalError`
- Safari and Chrome: `RangeError`
- Internet Explorer: generic `Error` type, and display a dialog box that looks like an alert.
- Opera: won't throw an error, but stop the JavaScript engine

> Note that: even though the error of exceeding limitation of call stack size can be trapped with a `try-catch` statement, it's not recommended.

#### 3.2 Recursion Patterns

When throwing such kind of limitation error, the first step you should do is to identify where the problem is, and in this case, you should be aware of two Recursion patterns.

The first one is:

```js
function recurse() {
    recurse();
}

recurse();
```

The second one is:

```js
function first() {
    second();
}

function second() {
    first();
}

first();
```

Compared with the first one, the second pattern is far more difficult to identify bugs in large code bases. For the first one, limitation exceeding problem will occur when the terminal condition is wrong in most cases. However, if it's correct, then the algorithm contains too much recursion to safely be run in the browser. Then, you should change to use iteration, memoization (記憶化), or both.

#### 3.3 Iteration

Any algorithm that can be implemented using recursion can also be implemented using iteration. Using optimized loops in place of long-running recursive functions can result in  performance improvements due to the lower overhead of loops versus that of executing a function.

As an example, a simple JavaScript implementation of merge sort is as followed:

```js
function merge(left, right) {
    var result = [];

    while (left.length > 0 && right.length > 0) {
        if (left[0] < right[0]) {
            result.push(left.shift());
        } else {
            result.push(right.shift());
        }
    }

    return result.concat(left).concat(right);
}

function mergeSort(items) {
    if (items.length === 1) {
        return items;
    }

    var middle = Math.floor(items.length / 2);
    var left = items.slice(0, middle);
    var right = items.slice(middle);

    return merge(mergeSort(left), mergeSort(right));
}
```

An array of `n` items ends up calling `mergeSort()` 2 * n - 1, which means that an array with more than 1500 items would cause a stack overflow error in Firefox. In this case, we should implement it with iteration:

```js
/** example: [20, 10, 35, 5, 2, 7] */
function mergeSort(items) {
    if (items.length === 1) {
        return items;
    }

    var work = [];

    for (var i = 0, len = items.length; i < len; i++) {
        work.push([items[i]]);
    }

    /** in case of odd number of items */
    work.push([]);

    /**
     * work: [[20], [10], [35], [5], [2], [7], []]
     * loop1: [[10, 20], [5, 35], [2, 7], [], [], [7], []]
     * loop2: [[5, 10, 20, 35], [2, 7], [], [], [], [7], []]
     * loop3: [[2, 5, 7, 10, 20, 35], [], [], [], [], [7], []]
     */
    for (var lim = len; lim > 1; lim = Math.floor((lim + 1) / 2)) {
        for (var j = 0, k = 0; k < lim; j++, k+= 2) {
            work[j] = merge(work[k], work[k + 1]);
        }

        /** in case of odd number of items */
        work[j] = [];
    }

    return work[0];
}
```

Although the iterative version of merge sort may be somewhat slower than the recursive option, it does not have the call stack impact.

#### 3.4 Memoization

Memoization is an approach to avoid work repetition by caching previous calculations for later use, which make it a useful technique for recursive algorithms. Sometimes, when recursive functions are called multiple times, there tends to be a lot of work duplication. Considering using `factorial()` like this:

```js
var fact6 = factorial(6);
var fact5 = factorial(5);
var fact4 = factorial(4);
```

Actually, the result of calling `factorial(4)` can be used when calling `factorial(5)`, as same as calling `factorial(6)`. Therefore, we can rewrite this code for reducing work duplication.

```js
function memfactorial(n) {
    if (!memfactorial.cache) {
        memfactorial.cache = {
            0: 1,
            1: 1
        };
    }

    if (!memfactorial.cache.hasOwnProperty(n)) {
        memfactorial.cache[n] = n * memfactorial(n - 1);
    }

    return memfactorial.cache[n];
}
```

The memoization process may be slightly different for each recursive function, but generally the same pattern applies. However, generic memoization of this type is less optimal, because the `memoize()` function caches the result of a function call with specific arguments. Recursive calls, therefore, are saved only when the shell function is called multiple times with the same arguments. For this reason, it's better to manually implement memoization in those functions that have significant performance issues, rather than apply a generic memoization solution.

```js
function memoize(fundamental, cache) {
    cache = cache || {};

    var shell = function (arg) {
        if (!cache.hasOwnProperty(arg)) {
            cache[arg] = fundamental(arg);
        }

        return cache[arg];
    }

    return shell;
}

var memfactorial = memoize(factorial, { 0: 1, 1: 1 });

memfactorial(6);

/** when calculating 5, it still won't use the cache to fix the performance impact */
memfactorial(5);
```

### 4. Summary

Just optimize your code, and notice the limitation of JavaScript. The larger the amount of code being executed, the larger the performance gain realized (被意識到).

- `for`, `while` and `do-while` loops all are similar to each other.
- Avoid using `for-in` unless you need to iterate over a number of unknown object properties.
- Decrease the amount of work per iteration and decrease the number of loop iterations to improve loop performance.
- `switch` is always faster than `if-else`, but not always the best solution.
- Lookup tables are a faster alternative.
- Notice that limitation of call stack.
- When running into a stack overflow error, change the method to an iterative one, or make use of memoization to avoid work repetition.
