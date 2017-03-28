## How to detect IE version with JavaScript [Back](./qa.md)

```js
const ieMode = document.documentMode;
const isIE = !!window.ActiveXObject;
const isCompatibilityMode = document.compatMode === 'CSS1Compat';

const isIE6 = isIE && !window.XMLHttpRequest;
const isIE7 = isIE && !isIE6 && !ieMode || ieMode === 7;
const isIE8 = isIE && ieMode === 8;
const isIE9 = isIE && ieMode === 9;
```


**browsers**|IE6|IE7|IE8|IE8 Compatibility Mode|IE9|IE9 Compatibility Mode
:----:|:-:|:-:|:-:|:------------:|:-:|:------------:
**documentMode**|undefined|undefined|8|7|9|7
