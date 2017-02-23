## Flatten an array [Back](./../underscore.md)

Flattening an array means to simplify an array with extracting embedded array of another array. The following case has apparently shown us what is flattening an array:

```js
[[[1, 2], [1, 2, 3]], [1, 2]] => [1, 2, 1, 2, 3, 1, 2] /** flatten in a deep way */
[[[1, 2], [1, 2, 3]], [1, 2]] => [[1, 2], [1, 2, 3], 1, 2] /** flatten only one layer */
```

Before analyzing the method `_.flatten()` of underscore, we should consider how to call this method firstly:

```js
var flatten = function(input, shallow, strict, startIndex) {
    // ...
};
```
