## How to preload resources with JavaScript [Back](./qa.md)

### 1.  A image resource loader class

```js
(function (root, factory) {
    if (typeof define === 'function' && define.amd) {
        /** AMD style */
        define(factory);
    } else if (typeof exports === 'object') {
        /** Node, CommonJS style */
        module.exports = factory();
    } else {
        /** 浏览器全局变量(root 即 window) */
        root.resLoader = factory(root);
    }
}(this, function () {
    var isFunc = function (f) {
        return typeof f === 'function';
    }
    
    /** 构造器函数 */
    function resLoader(config) {
        this.option = {
            resourceType : 'image',     /** 资源类型，默认为图片 */
            baseUrl : './',             /** 基准url */
            resources : [],             /** 资源路径数组 */
            onStart : null,             /** 加载开始回调函数，传入参数total */
            onProgress : null,          /** 正在加载回调函数，传入参数currentIndex, total */
            onComplete : null           /** 加载完毕回调函数，传入参数total */
        }
        
        if (config) {
            for (i in config) {
                this.option[i] = config[i];
            }
        } else {
            alert('error parameters');
            return;
        }
        
        /** 加载器的状态，0：未启动   1：正在加载   2：加载完毕 */
        this.status = 0;
        
        /** 资源总数 */
        this.total = this.option.resources.length || 0;
        
        /** 当前正在加载的资源索引 */
        this.currentIndex = 0;
    };

    resLoader.prototype.start = function () {
        this.status = 1;
        var _this = this;
        var baseUrl = this.option.baseUrl;
        for (var i = 0, l = this.option.resources.length; i < l; i++) {
            var r = this.option.resources[i];
            var url = '';
            
            if (r.indexOf('http://') ===0 || r.indexOf('https://')===0) {
                url = r;
            } else {
                url = baseUrl + r;
            }

            var image = new Image();
            image.onload = function () {
                _this.loaded();
            };
            
            image.onerror = function () {
                _this.loaded();
            };
            
            image.src = url;
        }
        
        if (isFunc(this.option.onStart)) {
            this.option.onStart(this.total);
        }
    }

    resLoader.prototype.loaded = function () {
        if (isFunc(this.option.onProgress)) {
            this.option.onProgress(++this.currentIndex, this.total);
        }
        
        /** 加载完毕 */
        if (this.currentIndex===this.total) {
            if (isFunc(this.option.onComplete)) {
                this.option.onComplete(this.total);
            }
        }
    }

    /** 暴露公共方法 */
    return resLoader;
}));
```

### 2. Usage

```js
var loader = new resLoader({
    resources : [
       'images/bg2.jpg'
    ],
    onStart : function (total) {
    },
    onProgress : function (current, total) {
    },
    onComplete : function (total) {
    }
});
```

### 3. Prefetching

#### Firefox

As per MDN, you can use the `<link>` tags in head of the document,

```html
<link rel="prefetch" href="/assets/my-preloaded-image.png">
```

Also can be set into a request header:

```
Link: </assets/my-preloaded-image.png>; rel=prefetch
```

Or within a html `meta` tag:

```html
<meta http-equiv="Link" content="</assets/my-preloaded-image.png>; rel=prefetch">
```

Of course you can prefetch the next page you know:

```html
<link rel="next" href="2.html">
```

#### IE 11

```html
<link rel="prefetch" href="http://example.com/style.css" />
<link rel="dns-prefetch" href="http://example.com/"/>
<link rel="prerender" href="http://example.com/nextpage.html" />
```

#### Chrome

Chrome also does the same things as both Firefox and IE.