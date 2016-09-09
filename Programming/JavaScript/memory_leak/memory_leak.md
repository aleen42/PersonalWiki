## Memory Leak (內存洩漏) [Back](./../JavaScript.md)

In the process of developing front-end application, like web application, "memory leak" means that a space created before **cannot be used or collect any more** until the browser is closed.

Though the browser has GC (Garbage Collection), but there is bug on this collection, which will lead to memory leak case.

Here we list some cases that will cause memory leak in JavaScript:

### Event Listener

When a DOM has changed, if its event listener has not be removed, IE will not handle it for you and it causes memory leak.


