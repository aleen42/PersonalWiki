## XMLHttpRequest [Back](./../web_api.md)

**XMLHttpRequest**, also called XHR is designed firstly by MicroSoft, which is **used to request resources from a url**. Although it's named with XML, but it can request all types of resources, with HTTP, FTP protocol and so on.

#### 1. new an object

```js
var xhr = new XMLHttpRequest();
```

### 2. create a AJAX request with XHR

```js
function createXHR() {
    if (XMLHttpRequest) {
        /** not IE 6 */
    } else if (ActiveXObject) {
    }
}

function ajax(obj) {
    var xhr = 
}
```
