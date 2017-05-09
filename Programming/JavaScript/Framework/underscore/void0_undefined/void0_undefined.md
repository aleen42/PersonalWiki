## Use `void 0` rather than `undefined` [Back](./../underscore.md)

If you look through the whole source code, you'll never find any `undefiend`, but only one string `"undefined"`, why?

Firstly, `undefined` is not a reversed word, and it's only a attribute of all global objects, which can be override in low edition of IE.

```js
var undefined = 10;
console.log(undefined); /**
                         * => undefined (Chrome)
                         * => 10        (IE 8)
                         */
```

In ES5, `undefined` has been designed as a **read-only** attributes, which can't be overridden. However, you will find that you can do it in a local scope:

```js
(function () {
    var undefined = 10;
    console.log(undefined); /**
                             * => 10 (Chrome)
                             */
})();

(function () {
    undefined = 10;
    console.log(undefined); /**
                             * => undefined (Chrome)
                             */
})();
```

Then, why use the replacement `void 0`?

What is `void` in [MDN statemet](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/void)?

> The void operator evaluates the given expression and then returns undefined.

That means `void` will always return undefined, which can completely take the place of `undefined`. Actually, `void 0`, `void 1` and `void "hello world"` are all same. The most important thing is that `void` can't be overridden.

Although `undefined` can generally be trusted in modern JavaScript environments, there is one trivial advantage of `void 0`: it's shorter. The difference is not enough to worry about when writing code but it can add up enough over large code bases that most code minifiers replace `undefined` with `void 0` to reduce the number of bytes sent to the browser.

However, the disadvantages of using `void 0` is that it has reduced readability of code, and it's recommended to avoid using both `void 0` and `undefined` in our code, despite of the special situation when writing minifier tools, or frameworks.
