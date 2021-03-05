## How to get current timestamp with JavaScript [Back](./qa.md)

### Accurate to Seconds

```js
console.log(Date.parse(new Date()));    /** => 1280977330000 */
```

### Accurate to Milliseconds

```js
console.log(new Date().getTime());      /** => 1280977330748 */

console.log((new Date()).valueOf());    /** => 1280977330748 */
```

### Convert timestamp into a date

```js
Date.prototype.format = function (format) {
    var date = {
        'M+': this.getMonth() + 1,
        'd+': this.getDate(),
        'h+': this.getHours(),
        'm+': this.getMinutes(),
        's+': this.getSeconds(),
        'q+': Math.floor((this.getMonth() + 3) / 3),
        'S+': this.getMilliseconds()
    };
    
    if (/(y+)/i.test(format)) {
        format = format.replace(RegExp.$1, (this.getFullYear() + '').substr(4 - RegExp.$1.length));
    }
    
    for (var k in date) {
        if (new RegExp('(' + k + ')').test(format)) {
            format = format.replace(RegExp.$1, RegExp.$1.length == 1 ? date[k] : ('00' + date[k]).substr(('' + date[k]).length));
        }
    }
    
    return format;
}

console.log(new Date(timestamp * 1000).format('yyyy-MM-dd hh:mm:ss'));    /** => 2016-08-16 20:37:01 */
```
