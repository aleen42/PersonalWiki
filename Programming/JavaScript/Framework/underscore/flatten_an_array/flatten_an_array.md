## Flatten an array [Back](./../underscore.md)

Flattening an array means to simplify an array with extracting embedded array of another array. The following case has apparently shown us what is flattening an array:

```js
[[[1, 2], [1, 2, 3]], [1, 2]] => [1, 2, 1, 2, 3, 1, 2] /** flatten in a deep way */
[[[1, 2], [1, 2, 3]], [1, 2]] => [[1, 2], [1, 2, 3], 1, 2] /** flatten only one layer */
```

Before analyzing the method `_.flatten()` of underscore, we will have a look at the predicate method:

```js
var flatten = function(input, shallow, strict, startIndex) {
    // ...
};
```

As we can see above, the method has accepted four parameters, of which the `input` is the first one to get a given array. Then, `shallow` is a Boolean value for checking whether to flatten just one layer of the array. `startIndex` is used to set up where to start to flatten.

`strict` is also a Boolean value, but it's hard to understand. If `strict` is given a `true` value, then it means that each flattening will ignore any elements which is not an array. For example:

```js
var ans = _.flatten([5, 6, [1, 2], [3, 4]], true, true);
```


