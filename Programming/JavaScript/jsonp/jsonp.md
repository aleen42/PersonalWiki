## JSONP [Back](./../JavaScript.md)

**JSONP**, also named **JSON with padding** or **JSON-P**, which is a JSON extension used by web developers to overcome the cross-domain restrictions with `<script>`. `<script>` is used to load JavaScript from a URL, and use a JavaScript engine to parse, rather than a JSON engine.

So, the difference from JSON is that you must return a executable JavaScript from the URL. In JSONP, the data in JSON will be wrapped by a callback function, which will be delivered to the server through URL parameters.

```html
<script type="text/javascript" 
    src="http://www.example.com/getData?dataId=123&jsonp=parseResponse">
</script>
```


