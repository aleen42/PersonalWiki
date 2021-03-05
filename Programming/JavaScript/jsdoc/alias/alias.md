## @alias [Back](../jsdoc.md)

The `@alias` tag causes JSDoc to treat all references to a member if the member have a different name:

```js
const Apple = {};

(function(ns) {
    /**
     * core property
     * @alias Apple.Core
     */
    const core = {};

    /** Documented as Apple.Core.seed */
    core.seed = function() {};

    ns.Core = core;
})(Apple);

console.log(Apple.Core);
```

While the `@alias` tag may sound similar to the [`@name`](../name/name.md) tag, these tags behave very differently. The [`@name`](../name/name.md) tag tells JSDoc to ignore any code associated with the comment. For example, when JSDoc processes the following code, it ignores the fact that the comment for `bar` is attached to a function:

```js
/**
 * Bar function.
 * @name bar
 */
function foo() {}
```

The `@alias` tag tells JSDoc to pretend that Member A is actually named Member B. For example, when JSDoc processes the following code, it recognizes that `foo` is a function, then renames `foo` to `bar` in the documentation:

```js
/**
 * Bar function.
 * @alias bar
 */
function foo() {}
```

In most cases, `@alias` tag is helpful for identifying members that are created with an immediately invoked function expression (IIFE):

```js
const obj = (str => {
    /**
     * an alias
     * @type {{str: *, other: *}}
     * @alias obj
     */
    const result = {str};
    result.other = '2';
    return result;
})('1');
```

In addition, it can be an alternative of [`@lends`](../lends/lends.md):

```js
const objA = (str => {
    /**
     * an alias for objB
     * @type {{str: *, other: *}}
     * @alias objA
     */
    const result = {str};
    result.other = '2';
    return result;
})('1');

/**
 * lends for objB
 * @type {{str: *, other: *}}
 */
const objB = (str => {
    /**
     * @lends objB
     */
    const result = {str};
    result.other = '2';
    return result;
})('1');
```
