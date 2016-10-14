## How to convert string between HTML entites and Ascii with JavaScript [Back](./qa.md)

### Ascii to HTML entities

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
