## How to detect IE version with JavaScript [Back](./qa.md)

```js
const ieMode = document.documentMode;
const isIE = !!window.ActiveXObject;
const isStandardOrCompatMode = document.compatMode === 'CSS1Compat';
const isQuirksMode = document.compatMode === 'BackCompat';

const isIE6 = isIE && !window.XMLHttpRequest;
const isIE7 = isIE && !isIE6 && !ieMode || ieMode === 7;
const isIE8 = isIE && ieMode === 8;
const isIE9 = isIE && ieMode === 9;
const isIE10 = isIE && ieMode === 10;
```

| browsers     |    IE6    |    IE7    | IE8 | IE8 Compatibility Mode | IE9 | IE9 Compatibility Mode | IE10 | IE11 |
|:-------------|:---------:|:---------:|:---:|:----------------------:|:---:|:----------------------:|:----:|:----:|
| documentMode | undefined | undefined |  8  |           8            |  9  |           9            |  10  |  11  |

Or use other objects to detect:

```js
const isIE6 = !!(document.all && !window.XMLHttpRequest && document.compatMode);
const isIE7 = !!(document.all && !document.querySelector && window.XMLHttpRequest);
const isIE8 = !!(document.all && !document.addEventListener && document.querySelector);
const isIE9 = !!(document.all && !window.atob && document.addEventListener);
const isIE10 = !!(document.all && window.atob);
```

Or we can even export the range of IE versions like the following snippet:

```js
/** https://stackoverflow.com/questions/19638981/window-activexobject-difference-in-ie11/20244319#20244319 */
const isIE = 'ActiveXObject' in window; /** exclude IE Edge */
const isLE10 = isIE && !!window.ActiveXObject; /** IE10- (include IE10) */
const isLE9 = isIE && !window.FormData; /** IE9- (include IE9) */
const isLE8 = isIE && !window.addEventListener; /** IE8- (include IE8) */
const isLE7 = isIE && !document.querySelector; /** IE7- (include IE7) */
```

However, if developer has implemented some objects by adding shims or polyfills, this may has some problems. Furthermore, the methods provided above has not supported IE11 at all. Therefore, we need to use `userAgent` to detect the version of IE:

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
     * support version detect between IE6 and IE11
     * '6+': means to detect whether it's IE6 or later
     * '11': means to detect whether it's IE11
     * '8-': means to detect whether it's IE8 or older
     */
    var operations = /^(1[0-1]|[6-9])(\+|-)?$/.exec(version);

    if (version === void 0 || operations === null) {
        /**
         * if there is no version detection,
         * or the regex has failed to, just return whether it's IE
         */
        return isIE;
    }

    var versionNumber = parseInt(operations[1], 10);
    var versionOperator = operations[2];
    
    switch (versionOperator) {
    case '+':
        return currentVersion >= versionNumber;
    case '-':
        return currentVersion <= versionNumber;
    case void 0:
        return currentVersion === versionNumber;
    default:
        return currentVersion === versionNumber;
    }
}
```

If you want more details, check [the answer](https://stackoverflow.com/a/30907476) of StackOverflow.
