## Modernizr [Back](./../Framework.md)

<p align="center">
    <img src="./logo.png" width="30%" />
</p>

![modernizr](https://aleen42.github.io/badges/src/modernizr.svg)

- [**Modernizr.js**](http://modernizr.com/docs/#s1) is a small JavaScript library that detects the availability of native implementations for next-generation web technologies, i.e. **features** that stem from the **HTML5** and **CSS3**.
- JQuery通過內置JQuery.browser,可以返回瀏覽器版本. 它通過user agent來獲取瀏覽器的相關信息(JQuery1.9版本前) 
- JQuery通過內置JQuery.support檢測feature方案來判斷是否需要回退(JQuery1.9版本後), 原因是user agent容易被偽造, 從而導致JQuery.browser的真實性
- 由於Modernizer內置**html5shiv**類庫, 因此我們必須在`<body>`加載之前引用Modernizer.js

### Code

```html
<script src="js/modernizr.custom.js"></script>
```

### Download

- Just Click [**here**](http://modernizr.com/download/#-csstransitions-shiv-cssclasses-prefixed-testprop-testallprops-domprefixes-load) to download.
