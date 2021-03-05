## How to calculate the size of an iFrame [Back](./qa.md)

```js
var calcPageHeight = function(doc) {
    var cHeight = Math.max(doc.body.clientHeight, doc.documentElement.clientHeight);
    var sHeight = Math.max(doc.body.scrollHeight, doc.documentElement.scrollHeight);
    return Math.max(cHeight, sHeight);
};

var calcPageWidth = function(doc, win) {
    if (!!win.ActiveXObject && doc.documentMode <= 8 && doc.compatMode === 'CSS1Compat') {
        /**
         * extract the minimal value under IE compatible mode,
         * so that the scroll bar won't be outside the container
         */
        var cWidth = Math.min(doc.body.clientWidth, doc.documentElement.clientWidth);
        /** also set body width to fix existence of scrollbars. */
        // doc.body.style.width = cWidth - 30 + 'px';

        return cWidth;
    } else {
        return Math.max(doc.body.clientWidth, doc.documentElement.clientWidth);
    }
};
```
