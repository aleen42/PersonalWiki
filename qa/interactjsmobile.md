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

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
