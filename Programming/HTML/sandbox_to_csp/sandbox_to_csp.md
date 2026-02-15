## A transition from IFrame sandbox to CSP [Back](../HTML.md)

As security requirements of presented contents to avoid XSS vulnerabilities growing larger and larger, developers may need some technics to eliminate scripts like using [`sandbox`](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/iframe#attr-sandbox) with `allow-same-origin` and no `allow-scripts` in IFrames. Nevertheless, I recently [found](https://github.com/mdn/browser-compat-data/pull/7153) that, we can't do two things in such a frame under Safari or [below Chrome 70](https://github.com/mdn/browser-compat-data/pull/9281):

- We can bind any event handlers upon nodes inside an iframe via accessing `iframe.contentDocument` but failed to run.
- We can't post any messages via `iframe.contentWindow.postMessage`.

In those two cases, browsers should throw an error:

```
[Error] Blocked script execution in 'xxx' because the document's frame is sandboxed and the 'allow-scripts' permission is not set.
```

Certainly, there is also a snippet of POC to detect whether your browser will do so:

```js
let sandboxInteroperable;
$('<iframe sandbox=allow-same-origin>').on('load', function () {
    $(this).contents().find('body').click(() => { sandboxInteroperable = 1; })[0].click();
    $(this).remove();
}).appendTo('body');
```

So in Safari and Chrome 70-, we need an alternative to solve the compatibility problem. That's [`script-src`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy/script-src) of [`Content-Security-Policy`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy) (CSP). *Notice: choose it rather than [`csp` of IFrame](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/iframe#attr-csp) because of its better compatibility.*

```html
<!-- wrapper.html -->
<meta http-equiv="Content-Security-Policy" content="script-src 'none';">
```

If you can use service side rendering page to construct such a wrapper page, you can also choose a more [compatible](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy#browser_compatibility) way to set CSP rather than `<meta>`:

```jsp
<!-- wrapper.jsp -->
<%
    response.addHeader("Content-Security-Policy", "script-src 'none';");
    out.clear();
%>
```
