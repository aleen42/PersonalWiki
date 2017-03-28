## How to detect IE version with JavaScript [Back](./qa.md)

```js
const ieMode = document.documentMode;
const isIE = !!window.ActiveXObject;

const isIE6 = isIE && !window.XMLHttpRequest;
const isIE7 = isIE && !isIE6 && !ieMode || ieMode === 7;
const isIE8 = isIE && ieMode === 8;
const isIE9 = isIE && ieMode === 9;
```
