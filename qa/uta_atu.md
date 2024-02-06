## How to convert string between Unicode and Ascii with JavaScript [Back](./qa.md)

### Ascii to Unicode

```js
function A2U(str) {
    var reserved = '';
    
    for (var i = 0; i < str.length; i++) {
        reserved += '&#' + str.charCodeAt(i) + ';';
    }
    
    return reserved;
}
```

### Unicode to Ascii

```js
function U2A(str) {
    var reserved = '';
    var code = str.match(/&#(d+);/g);
    
    if (code === null) {
        return str;
    }
    
    for (var i = 0; i < code.length; i++) {
        reserved += String.fromCharCode(code[i].replace(/[&#;]/g, ''));
    }
    
    return reserved;
}
```
