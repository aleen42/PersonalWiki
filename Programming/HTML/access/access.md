## Access Relative Nodes [Back](./../HTML.md)

```html
<html>
    <head>
        <title>DOM Example</title>
    </head>
    <body>
        <p>Hello World!</p>
        <p>Isn't this exciting?</p>
        <p>You're learning to use the DOM!</p>
    </body>
</html>
```

- access `<html />`

```js
var objHtml = this.document.documentElement;
```

- access `<head />` or `<body />`

```js
var objHead = objHtml.firstChild;
var objBody = objHtml.lastChild;
```

```js
var objHead = objHtml.childNodes.item(0);	// objHtml.childNodes[0]
var objBody = objHtml.childNodes.item(1);	// objHtml.childNodes[1]
```

```js
var objHead = this.document.head;
var objBody = this.document.body;
```

