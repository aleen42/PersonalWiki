## Differences between Cookie, localStorage, and sessionStorage [Back](./qa.md)

They are all used to store data into local storage.

**Cookie** is always used to store data, which can identify a user, into local clients (like browsers) with encryption, and they will be cleared after a expired time. The most important thing you should know is that **Cookie** will be in HTTP requests head, which will be transferred between **Server** and **Client**. (**< 4kb**)

**localStorage**: only store into local storage and won't be cleared after browsers close. (**> 5Mb**)

**sessionStorage**: only store into local storage and will be cleared after browsers close. (**> 5Mb**)

In JavaScript, you can operate them with provided APIs.

```js
/**
 * localStorage & sessionStorage
 */
var localStorage = window.localStorage;
var sessionStorage = window.sessionStorage;

/** localStorage */
localStorage.setItem('key', 'value');
var value = localStorage.getItem('key');

localStorage.removeItem('key');
localStorage.clear();

/** sessionStorage */
sessionStorage.setItem('key', 'value');
var value = sessionStorage.getItem('key');

sessionStorage.removeItem('key');
sessionStorage.clear();

/** storage event */
function handleStorage(e) {
    if (!e) {
        e = window.event;
    }
}

if (window.addEventListener) {
    window.addEventListener('storage', handleStorage, false);
} else if (window.attachEvent) {
    window.attachEvent('storge', handleStorage);
}

/**
 * Cookie
 */
document.cookie = 'key=value;';

function getCookie(name) {
    var arr;
    var reg = new RegExp("(^| )" + name + "=([^;]*)(;|$)");
    
    if (arr = document.cookie.match(reg)) {
        return unescape(arr[2]);
    } else {
        return null;
    }
}

/** time for second, which is 10 seconds by default */
function setCookie(name, value, time) {
    time = time || 10;
    var exp = new Date();
    exp.setTime(exp.getTime() + time * 1000); /** expire time: 20s */
    document.cookie = name + '=' + value + '; expires=' + exp.toGMTString();    
}

function deleteCookie(name) {
    var exp = new Date();
    exp.setTime(exp.getTime() - 1);
    var cval = getCookie(name);
    
    if (cval !== null) {
        document.cookie= name + "=" + cval + ";expires="+exp.toGMTString();
    }
}
```