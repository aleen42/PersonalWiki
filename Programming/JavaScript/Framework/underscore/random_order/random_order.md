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

In this common way, the algorithm mainly costs in accessing the array and extracting items. If the time of `Array.prototype.splice()` can be represented by `O(n)`, then the time of whole algorithm should be represented as `O(n^2)`. That's not fast!

To complete it in a more elegant way, we should considering the solution [**Fisher-Yates Shuffle**](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle). The time of such solution can be represented by `O(n)`. This algorithm can be described as: to access each item of an array and swap it **backward** or **forward** with an random item **behind** or **before** this item.

- **Backward**:

```js
function shuffle(arr) {
    var len = arr.length;
    
    for (var i = 0; i < len; i++) {
        var index = Math.floor(Math.random() * i);
    }
}
```