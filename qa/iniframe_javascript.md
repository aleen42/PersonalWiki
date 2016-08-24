## How to detect whether a document is inside a iframe with JavaScript [Back](./qa.md)

Browsers can block access to `window.top` due to [same origin policy](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Same_origin_policy_for_JavaScript). IE bugs also take place. Here's the working code:

```js
function inIframe () {
    try {
        return window.self !== window.top;
    } catch (e) {
        return true;
    }
}
```

