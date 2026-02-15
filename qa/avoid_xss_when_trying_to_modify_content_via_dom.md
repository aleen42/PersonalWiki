## How to avoid XSS when trying to modify HTML content via DOM? [Back](qa.md)

In most cases when we want to manipulate a string content, we may prefer to mount it on the DOM tree and do the manipulation rather than using a complicated regular expression replacement, like:

- finding some nodes to remove
- finding some classes to remove
- modifying the content.

However, this approach always leads to an XSS problem when the external content contains some unexpected scripts like the following snippet:

```js
const unsafe = '<img src=x onerror=alert(1)>';
$('<div>').html(unsafe).find('img').remove(); // leads to a XSS

const div = document.createElement('div');
div.innerHTML = unsafe; // leads to XSS
const img = div.querySelector('img');
img && img.parentNode.removeChild(img);
```

So how can we solve this problem? Roll back to a complicated regex? To avoid this problem, most developers may use some libraries like [js-xss](https://github.com/leizongmin/js-xss) or [DOMPurify](https://github.com/cure53/DOMPurify) to handle complicated regular expressions for them. Nevertheless, these libraries are sometimes too strict to remove some safe tags, except if you can set up the right configurations.

Here, I just want to clarify another simple way where we can rely on the iframe sandbox technics, which can also forbid browsers from accessing resources from the content like loading images:

```js
const unsafe = '<img src=x onerror=alert(1)>';
const $frame = $('<iframe>').appendTo('body'), $sandboxDoc = $frame.contents();
$frame.remove();

// scripts have been blocked
// the document won't also access the image which throws us a 404
$('<div>', $sandboxDoc).html(unsafe).find('img').remove(); 

// by pure javascript
const frame = document.createElement('iframe');
document.body.appendChild(frame);
const sandboxDoc = frame.contentDocument;
frame.parentNode.removeChild(frame);
const div = sandboxDoc.createElement('div');
div.innerHTML = unsafe;
const img = div.querySelector('img');
img && img.parentNode.removeChild(img);
```

Such a document still has a side effect in which DOM nodes won't compute out any styles:

```js
$('<img style="cursor: zoom-in">', $sandboxDoc).css('cursor'); // => ''

// by pure javascript
const img = sandboxDoc.createElement('img');
img.setAttribute('style', 'cursor:zoom-in');
img.style.cursor; // => ''
```

It means that we will have some unexpected results in some situations like we cannot remove the cursor:

```js
$('<img style="cursor: zoom-in">', $sandboxDoc)
    .css({cursor : ''}).prop('outerHTML'); // => '<img style="cursor: zoom-in">'
    
// by pure javascript
img.style.cursor = '';
img.outerHTML; // => '<img style="cursor:zoom-in">'
```

To work around this, we should ensure to construct DOM nodes before removing the document:

```js
function $sandbox(content) {
    const $frame = $('<iframe>').appendTo('body');
    const $elem = $(content, $frame.contents());
    $frame.remove();
    return $elem;
}

$sandbox('<img style="cursor: zoom-in">').css('cursor'); // => 'zoom-in'

// by pure javascript
function sandbox(fn) {
    const frame = document.createElement('iframe');
    document.body.appendChild(frame);
    const elem = fn(frame.contentDocument);
    frame.parentNode.removeChild(frame);
    return elem;
}

sandbox(sandboxDoc => {
    const img = sandboxDoc.createElement('img');
    img.setAttribute('style', 'cursor:zoom-in');
    return img;
}).style.cursor; // => 'zoom-in'
```
