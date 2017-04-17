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

However, if developer has implemented some objects by adding shims or polyfills, this may has some problems. Therefore, we can also use `userAgent` to detect the version of IE:

```js
function isIE(version) {
    var currentVersion = (function () {
        var returnVersion = -1;
        var userAgent = navigator.userAgent;
        if (navigator.appName === 'Microsoft Internet Explorer') {
            if (/MSIE ([0-9]{1,}[.0-9]{0,})/.exec(userAgent) !== null) {
                returnVersion = parseInt(RegExp.$1, 10);
            }
        } else if (navigator.appName === 'Netscape') {
            if (/Trident\/.*rv:([0-9]{1,}[.0-9]{0,})/.exec(userAgent) !== null) {
                returnVersion = parseInt(RegExp.$1, 10);
            }
        }

        return returnVersion;
    })();

    var isIE = currentVersion > 0;
    
    /**
     * 支持 IE6 ~ 11 的版本检测：
     * '6+'： 表示检测是否为 IE6 以上
     */
    var operations = /^(1[0-1]|[6-9])(\+|-)?$/.exec(version);

    if (version === void 0 || operations === null) {
        // 若没有传 version 或 version 不符合规则，则只判断是否是 IE 浏览器即可
        return isIE;
    }

    var versionNumber = parseInt(operations[1], 10);
    var versionOperator = operations[2];
    switch (versionOperator) {
    case '+':
        return currentVersion >= versionNumber;
    case '-':
        return currentVersion <= versionNumber;
    case '':
        return currentVersion === versionNumber;
    default:
        return currentVersion === versionNumber;
    }
}
```