## How to convert string between HTML entites and Ascii with JavaScript [Back](./qa.md)

### Ascii to HTML entities

```js
function A2E(str) {
    var reserved = '';
    
    for (var i = 0; i < str.length; i++) {
        reserved += '&#' + str.charCodeAt(i) + ';';
    }
    
    return reserved;
}
```
