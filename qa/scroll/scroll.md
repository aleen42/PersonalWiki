## Something about scrolling [Back](./../qa.md)

For a more complicated user experience for browsing a website, sometimes we will do more job about animating according to the scroll-bar. This document is mainly talk about something that we should take in consideration.

### How to listen to the scrolling of scroll-bars?

Before animating, we should know when users scroll the bar firstly:

```js
window.addEventListener('scroll', function () {
    /** the event handler for listening to the scrolling */	
});
```

With such a handler, we will be triggered once users scroll.

### When to the top and the bottom

If you want to know when users scroll the bar to the top or to the bottom, we can calculate like the following:

```js
/** scroll to the top */
var oTop = document.body.scrollTop === 0 ? document.documentElement.scrollTop : document.body.scrollTop;
var oHeight= document.body.scrollHeight === 0 ? document.documentElement.scrollHeight : document.body.scrollHeight;

if (oTop === 0) {
    /** to the top */
}

if (oTop === oHeight - window.innerHeight) {
    /** to the bottom */
}
```

### Browser Support

With testing, the code snippets mentioned above works in IE11+ or other newer browsers.


