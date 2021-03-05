## XMLHttpRequest [Back](./../web_api.md)

**XMLHttpRequest**, also called XHR is designed firstly by MicroSoft, which is **used to request resources from a url**. Although it's named with XML, but it can request all types of resources, with HTTP, FTP protocol and so on.

#### 1. new an object

```js
var xhr = new XMLHttpRequest();
```

#### 2. create a AJAX request with XHR

```js
function createXHR() {
    if (XMLHttpRequest) {
        /** not IE 6 */
        return new XMLHttpRequest();
    } else if (ActiveXObject) {
        /** IE 6 */
        var version = [
            'MSXML2.XMLHttp.6.0',
            'MSXML2.XMLHttp.3.0',
            'MSXML2.XMLHttp'
        ];
        
        for (var i = 0; i < versions.length; i++) {
            try {
                return new ActiveXObject(version[i]);
            } catch (e) {
                /** ignore */
            }
        }
    } else {
        throw new Error('Failed to create XHR');
    }
}

function param(obj) {
    var arr = [];
    
    for (var i in obj) {
        arr.push(encodeURIComponent(i) + "=" + encodeURIComponent(obj[i]));
    }
    
    return arr.join('&');
}

function ajax(obj) {
    var xhr = createXHR();

    /** clear cache */
    obj.url = obj.url.indexOf('?') > 0 ? obj.url + '&_=' + new Date().getTime() : obj.url + '?_=' + new Date().getTime();

    /** escape parameters */
    obj.data = param(obj.data);

    /** callback function */
    function callback() {
        if (xhr.status === 200) {
            obj.success(xhr.responseText);
        } else {
            obj.error(xhr.status, xhr.statusText);
        }
    }

    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4) {
            callback();
        }
    };

    /** request */
    if (obj.type === 'POST') {
        xhr.open('POST', obj.url, true);
        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhr.send(obj.data);
    } else if (obj.type === 'GET') {
        obj.url += '&' + obj.data;
        xhr.open('GET', obj.url, true);
        xhr.send();
    }
}
```

#### 3. use AJAX to request resourcs

```js
ajax({
    type: 'POST',
    async: true,
    url: 'api/getData',
    data: {
        id: 'aleen'
    },
    success: function (data) {
        console.log(data);
    },
    error: function (status, errMsg) {
        console.log(errMsg);
    }
});
```
