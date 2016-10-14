## How to convert string between HTML entites and Ascii with JavaScript [Back](./qa.md)

### Ascii to HTML entities

```js
var entityTabe = {
    
};

function A2E(str) {
    return str.replace(/[\u00A0-\u2666<>\&]/g, function(c) {
        return '&' + (escapeHtmlEntities.entityTable[c.charCodeAt(0)] || '#'+c.charCodeAt(0)) + ';';
    });
}
```
