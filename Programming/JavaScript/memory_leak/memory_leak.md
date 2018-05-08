## Memory Leak (內存泄漏) [Back](./../JavaScript.md)

In the process of developing front-end application, like web application, "memory leak" means that a space created before **cannot be used or collect any more** until the browser is closed.

Though the browser has GC (Garbage Collection), but there is bug on this collection, which will lead to memory leak case.

Here we list some cases that will cause memory leak in JavaScript:

### Event Listener

When a DOM has changed, if its event listener has not be removed, IE will not handle it for you and it causes memory leak.

```html
<div id="myDiv">
    <input type="button" value="Click me" id="myBtn">
</div>

<script type="text/javascript">
    var btn = document.getElementById('myBtn');
    btn.onclick = function () {
        /**
         * the div with id myDiv will be changed into a text,
         * but its click event listener still exsists.
         */
        document.getElementById('myDiv').innerHTML = 'Processing...';
    };
</script>
```

In such kinds of cases, you can solve by remove the listener:

```html
<div id="myDiv">
    <input type="button" value="Click me" id="myBtn">
</div>

<script type="text/javascript">
    var btn = document.getElementById('myBtn');
    btn.onclick = function () {
        /** clear listner */
        btn.onclick = null;
        
        document.getElementById('myDiv').innerHTML = 'Processing...';
    };
</script>
```

Or use event delegation(事件委託):

```html
<div id="myDiv">
    <input type="button" value="Click me" id="myBtn">
</div>

<script type="text/javascript">
    var btn = document.getElementById('myBtn');
    btn.onclick = function (event) {
        /** event delegation */
        event = event || window.event;
        
        if (event.target.id === 'myBtn') {
            document.getElementById('myDiv').innerHTML = 'Processing...';
        }
    };
</script>
```

### DOM or ActiveX Object Reference

In ECMAScript, reference between two DOM elements can be collected, if no other elements refer to them like:

```js
var a = document.getElementById('xxx');
var b = document.getElementById('xx');

/** can still be collected */
a.reference = b;
b.reference = a;
```

However, in IE, if you loop to refer to any DOM or ActiveX Object, GC won't collect and release these elements.

```js
var a = document.getElementById('xxx');
a.reference = a;
```

### Closure

Closures will sometimes cause memory leak by holding a variable.

```js
function bindEvent() {
    var obj = document.getElementById('xxx');
    
    obj.onclick = function () {
        /** will keep holding obj even if it's a empty function */
    };
}
```

For this situation, we can solve it by defining handling event outside the container:

```js
function clickHandler() {
    /** handler for click event */
}

function bindEvent() {
    var obj = document.getElementById('xxx');
    
    obj.onclick = clickHandler;
}
```

Or directly release by deleting:

```js
function bindEvent() {
    var obj = document.getElementById('xxx');
    
    obj.onclick = function () {
        /** empty function */
    };
    
    /** delete this reference */
    obj = null;
}
```

### Delete loosely

Sometimes, if you delete an object loosely, it will result in memory leak:

```js
var a = { p: { x: 1 } };
var b = a.p;

delete a.p;

console.log(b.x);   /** still output => 1 */
```

Therefore, when deleting an object, remember to **delete recursively**.

```js
var a = { p: { x: 1 } };
var b = a.p;

function deleteObj(obj) {
    if (_.isObject(obj)) {
        delete obj;
        
        for (var i in obj) {
            deleteObj(i);
        }
    }
}
```

### Boxing?

According to some documents, the following code will result in memory leak in IE, because IE will temporary create a String obj when accessing the property `length`, which will have a leak:

```js
var s = 'abc';

console.log(s.length);
```

Therefore, before we access any property of a value object, we are recommended to convert them before:

```js
var s = '123';

console.log(new String(s).length);
```

### Illegal DOM Operations?

Some illegal DOM operations will result in memory leak in IE, like we call `appendChild` of a DOM element, which is not in the DOM tree.

### Pollution of the global namespace

Undefined variable will be defined in the global name-space, which is another memory leak:

```js
function foo() {
    bar = 'this is a hidden global variable';
}
```

Actually:

```js
function foo() {
    window.bar = 'this is a hidden global variable';
}
```

Worse situation:

```js
function foo() {
    this.bar = 'potential global';
}

foo();
```

Therefore, we can use the **strict mode** to limit our code:

```js
/**
 * any acident global variable will thorw out an error
 * in the strict mode 
 */
'use strict';
```
