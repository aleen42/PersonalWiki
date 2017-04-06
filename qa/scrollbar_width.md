## How to calculate the width of a scrollbar in browsers [Back](./qa.md)

```js
function getScrollbarWidth() {
    var outer = document.createElement('div');
    outer.style.visibility = 'hidden';
    outer.style.width = '100px';
    outer.style.msOverflowStyle = 'scrollbar'; /** needed for WinJS apps */
    
    document.body.appendChild(outer);
    
    var widthNoScroll = outer.offsetWidth;
    /** force scrollbars */
    outer.style.overflow = 'scroll';
    
    /** add innerdiv */
    var inner = document.createElement('div');
    inner.style.width = '100%';
    outer.appendChild(inner);        
    
    var widthWithScroll = inner.offsetWidth;
    
    /** remove divs */
    outer.parentNode.removeChild(outer);
    
    return widthNoScroll - widthWithScroll;
}
```

If you want to calculate with jQuery, use the following snippet:

```js
function getScrollbarWidth() {
    var parent = $('<div style="'
           + 'width: 50px;'
           + 'height: 50px;'
           + 'overflow: auto'
           + '"><div/></div>')
        .appendTo('body');
    var child  = parent.children();
    var width  = child.innerWidth() - child.height(99).innerWidth();

    parent.remove();

    return width;
}
```
