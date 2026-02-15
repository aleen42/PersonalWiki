## Currying [Back](../JavaScript.md)

Currying is always seen in JavaScript, and what actually it is? To make it simple, **currying** is exactly a way to reduce numbers of parameters of a function into one.

> f(m, n) => f(m)(n)

Take multiply as an example, we can exactly define two kinds of multiply function like the following snippet, where the after one is an example of currying:

```js
let multiply;
multiply = (m, n) => m * n; /** multiply(3, 4) === 12 */

/** currying */
multiply = m => n => m * n; /** multiply(3)(4) === 12 */
```

In fact, we have used the feature of closures in JavaScript, which helps us to collect arguments when the function block is created. With currying, we won't suffer from functions with many arguments any more. Besides, it is mostly useful when creating functional functions with extracting common parts.

In ES5, there are problems of nested functions when using currying, making code hard to read:

```js
function multiply(m) {
    return function (n) {
        return function (o) {
            return function (p) {
                /** return ... */
            };
        };
    };
}
```

Fortunately, arrow functions in ES6 has worked around this problem for us:

```js
const multiply = m => n => o => p => {/** return ... */};
```

Quite elegant, right?
