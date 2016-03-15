## How to use JavaScript to interact with Android and IOS [Back](./qa.md)

### Call Android or IOS

##### Android

```js
window.jsCallBack.func(status, msg);
```

##### IOS

```js
window.location.href = 'objc://' + 'getParam1:withParam2::/' + EncodeUtf8(status) + ':/' + EncodeUtf8(msg);
```

```js
/** utf8 encoding */
function EncodeUtf8(s1) {
    // escape函数用于对除英文字母外的字符进行编码。如“Visit W3School!”->"Visit%20W3School%21"
    var s = escape(s1);
    var sa = s.split("%");//sa[1]=u6211
    var retV = "";
    if (sa[0] != "") {
        retV = sa[0];
    }
    for (var i = 1; i < sa.length; i++) {
        if (sa[i].substring(0, 1) == "u") {
            retV += Hex2Utf8(Str2Hex(sa[i].substring(1, 5)));
            if (sa[i].length >= 6) {
                retV += sa[i].substring(5);
            }
        }
        else retV += "%" + sa[i];
    }
    return retV;
}

```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
