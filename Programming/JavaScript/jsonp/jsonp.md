## JSONP [Back](./../JavaScript.md)

### Description

**JSONP**, also named **JSON with padding** or **JSON-P**, which is a JSON extension used by web developers to overcome the cross-domain restrictions with `<script>`. `<script>` is used to load JavaScript from a URL, and use a JavaScript engine to parse, rather than a JSON engine.

So, the difference from JSON is that you must return a executable JavaScript from the URL. In JSONP, the data in JSON will be wrapped by a callback function, which will be delivered to the server through URL parameters like the following:

```html
<script type="text/javascript" 
    src="http://www.example.com/getData?dataId=123&jsonp=parseResponse">
</script>
```

Then, the browser will get a script like this:

```js
parseResponse({ "name": "Aleen", "id": "123" });
```

### Security

Due to corss-domain, including script tags from servers allows the remote server to inject any content into a website. If the remote servers have vulnerabilities(弱點) that allow JavaScript injection, the page served from the original server is exposed to an increased risk. That's **CSRF/XSRF** attack.

