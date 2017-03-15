## How to shuffle an array [Back](./../underscore.md)

Shuffling an array is a normal problem in coding, which can be used in many cases like card games. Generally, we can complete this function by creating an new array, and extracting items from the origin one randomly.

```js
function shuffle(arr) {
    var ret = [];
    
    while (arr.length) {
        var index = Math.floor(Math.random() * arr.length);
        
        ret.push(arr[index]);
        arr.splice(index, 1);
    }
    
    return ret;
}
```

In this common way, the algorithm mainly costs in accessing the array and extracting items. If the time of `Array.prototype.splice()` can be represented by `O(n)`, then the time of whole algorithm should be represented as `O(n^2)`.
