## How to get an array unique [Back](./../underscore.md)

If an array does not have repeated items, it's a unique. Before discussing how to get an array unique in underscore, there have been various ways to complete it.

The most common way is to use another array to store items. If the items is not included in that array, then push it into the array, if not, then ignore it.

```js
function unique(arr) {
    var res = [];
    var len = arr.length;
    
    for (var i = 0; i < len; i++) {
        var item = arr[i];
        
        var res_len = res.length;
        
        for (var j = 0; j < res_len; j++) {
            if (res[j] === item) {
                break;
            }
        }
        
        if (j === res_len) {
            res.push(item);
        }
    }
    
    return res;
}
```

If we don't consider the compatibility of browsers, we can use `Array.prototype.indexOf()` and `Array.prototype.filter()` to simplify it:

```js
function unique(arr) {
    var res = arr.filter(function (item, index, array) {
        return array.indexOf(item) === index;
    });
    
    return res;
}
```
