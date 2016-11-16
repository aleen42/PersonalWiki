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

### Calculate when to the top and the bottom
