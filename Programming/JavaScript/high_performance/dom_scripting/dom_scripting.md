## DOM Scripting [Back](./../high_performance.md)

### 1. DOM

The Document Object Method (DOM) is a language-independent application interface (API) for working with XML and HTML documents.

#### 1.1 Inherently Slow

An excellent analogy is to think of DOM as a piece of land and JavaScript (meaning ECMAScript) as another piece of land, both connected with a toll(收費的) bridge.

Once you access to the DOM, you need to pay for it. **More you work, more you pay**.

### 2. Dom Access and Modification

Modifying elements is even more expensive than accessing, because browsers have to recalculate changes in the page geometry. A disaster will appear when you do it in loops, and especially in loops over HTML collections. For instance, the following code has accessed the document element twice: once to read the value, and once to write.

```js
function innerHTMLLoop() {
    for (var count = 0; count < 15000; count++) {
        document.getElementById('content').innerHTML += 'what';
    }
}
```

So how about storing the element in a local variable? It will only access and modify once. (In IE6, we can save around 155x time)

```js
function innerHTMLLoop() {
    var content = '';

    for (var count = 0; count < 15000; count++) {
        content += 'what';
    }

    document.getElementById('content').innerHTML += content;
}
```

#### 2.1 innerHTML vs DOM methods

Here is a sample task of creating a table of 1000 rows in two ways:

- By concatenating an HTML string and updating the DOM with `innerHTML`

    ```js
    function tableInnerHTML() {
        var i;
        var h = ['<table border="1" width="100%">'];

        h.push('<thead>');
        h.push('<tr><th>id<\/th><th>yes?<\/th><th>name<\/th><th>url<\/th><th>action<\/th> <\/tr>');
        h.push('<\/thead>');
        h.push('<tbody>');

        for (i = 1; i <= 1000; i++) {
            h.push('<tr><td>');
            h.push(i);
            h.push('<\/td><td>');
            h.push('And the answer is... ' + (i % 2 ? 'yes' : 'no'));
            h.push('<\/td><td>');
            h.push('my name is #' + i);
            h.push('<\/td><td>');
            h.push('<a href="http://example.org/' + i + '.html">http://example.org/' + i + '.html<\/a>');
            h.push('<\/td><td>');
            h.push('<ul>');
            h.push(' <li><a href="edit.php?id=' + i + '">edit<\/a><\/li>');
            h.push(' <li><a href="delete.php?id="' + i + '-id001">delete<\/a><\/li>');
            h.push('<\/ul>');
            h.push('<\/td>');
            h.push('<\/tr>');
        }

        h.push('<\/tbody>');
        h.push('<\/table>');

        document.getElementById('content').innerHTML = h.join('');
    }
    ```

- By using only standard DOM methods such as `document.createElement()` and `document.createTextNode()`

    ```js
    function tableDOM() {
        var i;
        var table;
        var thead;
        var tbody;
        var tr;
        var th;
        var td;
        var a;
        var ul;
        var li;

        tbody = documet.createElement('tbody');

        for (i = 1; i <= 1000; i++) {
            tr = document.createElement('tr');
            td = document.createElement('td');
            td.appendChild(document.createTextNode((i % 2) ? 'yes' : 'no'));
            tr.appendChild(td);
            td = document.createElement('td');
            td.appendChild(document.createTextNode(i));
            tr.appendChild(td);
            td = document.createElement('td');
            td.appendChild(document.createTextNode('my name is #' + i));
            tr.appendChild(td);

            a = document.createElement('a');
            a.setAttribute('href', 'http://example.org/' + i + '.html');
            a.appendChild(document.createTextNode('http://example.org/' + i + '.html'));
            td = document.createElement('td');
            td.appendChild(a);
            tr.appendChild(td);

            ul = document.createElement('ul');
            a = document.createElement('a');
            a.setAttribute('href', 'edit.php?id=' + i);
            a.appendChild(document.createTextNode('edit'));
            li = document.createElement('li');
            li.appendChild(a);
            ul.appendChild(li);
            a = document.createElement('a');
            a.setAttribute('href', 'delete.php?id=' + i);
            a.appendChild(document.createTextNode('delete'));
            li = document.createElement('li');
            li.appendChild(a);
            ul.appendChild(li);
            td = document.createElement('td');
            td.appendChild(ul);
            tr.appendChild(td);

            tbody.appendChild(tr);
        }

        tr = document.createElement('tr');
        th = document.createElement('th');
        th.appendChild(document.createTextNode('yes?'));
        tr.appendChild(th);
        th = document.createElement('th');
        th.appendChild(document.createTextNode('id'));
        tr.appendChild(th);
        th = document.createElement('th');
        th.appendChild(document.createTextNode('name'));
        tr.appendChild(th);
        th = document.createElement('th');
        th.appendChild(document.createTextNode('url'));
        tr.appendChild(th);
        th = document.createElement('th');
        th.appendChild(document.createTextNode('action'));
        tr.appendChild(th);

        thead = document.createElement('thead');
        thead.appendChild(tr);
        table = document.createElement('table');
        table.setAttribute('border', 1);
        table.setAttribute('width', '100%');
        table.appendChild(thead);
        table.appendChild(tbody);

        document.getElementById('here').appendChild(table)
    }
    ```

The result of this task has been shown in the followed table:

$$Speed = \frac {t_{DOM} - t_{innerHTML}}{t_{innerHTML}}$$

Browsers|IE 6|IE 7|IE 8|Firefox 3|Firefox 3.5|Safari 3.2
:----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Speed|3.62x|1.75x|1.64x|1.28x|1.17x|1.06x

Browsers|Safari 4|Chrome 2|Chrome 3|Opera 9.64|Opera 10
:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Speed|-1.13x|1.35x|-1.15x|1.19x|0.00x

> As a side note, keep in mind that string concatenation is not optimal in older IE versions, but using an array to concatenate large strings will make innerHTML even faster in such browsers.

#### 2.2 Cloning Nodes

Another way of updating page contents using DOM methods is to clone existing DOM with the method `element.clondNode()`. Cloning nodes is more efficient in most browsers. In comparison with creating elements:

- Cloning is 2% faster in IE8, but not change in IE6 and IE7.
- Up to 5.5% faster in Firefox 3.5 and Safari 4.
- 6% faster in Opera. (but no savings in Opera 10)
- 10% in Chrome 2 and 3% in Chrome 3.

```js
function tableClonedDOM() {
    var i;
    var table;
    var thead;
    var tbody;
    var tr;
    var th;
    var td;
    var a;
    var ul;
    var li;

    var oth = document.createElement('th');
    var otd = document.createElement('td');
    var otr = document.createElement('tr');
    var oa = document.createElement('a');
    var oli = document.createElement('li');
    var oul = document.createElement('ul');

    tbody = document.createElement('tbody');

    for (i = 1; i <= 1000; i++) {
        tr = otr.cloneNode(false);
        td = otd.cloneNode(false);
        td.appendChild(document.createTextNode((i % 2) ? 'yes' : 'no'));
        tr.appendChild(td);
        td = otd.cloneNode(false);
        td.appendChild(document.createTextNode(i));
        tr.appendChild(td);
        td = otd.cloneNode(false);
        td.appendChild(document.createTextNode('my name is #' + i));
        tr.appendChild(td);

        /** ... the rest of the loop ... */
    }

    /** ... the rest of the table generation ... */
}
```

#### 2.3 HTML Collections

**HTML collections** are array-like object, which contains DOM node references. For instances, they are the values returned by the following methods:

- `document.getElementsByName()`
- `document.getElementsByClassName()`
- `document.getElementsByTagName()`

or the following properties:

- `document.images`: All `img` elements on the page
- `document.links`: All `a` elements
- `document.forms`: All `form` elements
- `document.forms[0].elements`: All fields in the first form on the page

As defined in the DOM standard, HTML collections are "assumed to be *live*, meaning that they're automatically updated when the underlying document is updated". To demonstrate that an HTML collection is live, consider the following code:

```js
/** an accidentally infinite loop, because the property `length` of the variable, `alldivs`, are automatically increased. */
var alldivs = document.getElementsByTagName('div');

for (var i = 0; i < alldivs.length; i++) {
    document.body.appendChild(document.createElement('div'));
}
```

As we can see that, looping through an HTML collection may lead to a logic mistakes, and causing performance problem at the same time, because each accessing will lead to a query running on every iteration. Besides, with a sample task, we can demonstrate that loop over an array is significantly faster than looping through an HTML collection of the same size and content.

Firstly, we will copy an HTML collection to an array using a method:

```js
function toArray(collection) {
    for (var i = 0, a = [], len = collection.length; i < len; i++) {
        a[i] = collection[i];
    }

    return a;
}
```

Then, set up a collection and a copy of it into an array:

```js
var collection = document.getElementsByTagName('div');
var arr = toArray(collection);
```

After that, we can create such simple task like this:

```js
/** slower */
function loopCollection() {
    for (var count = 0; count < collection.length; count++) {
        /** do nothing */
    }
}

/** faster */
function loopArray() {
    for (var count = 0; count < array.length; count++) {
        /** do nothing */
    }
}
```

After calling two functions, we can get the result like that:

$$Faster = \frac {t_{collection} - t_{array}}{t_{array}}$$

Browsers|IE 6|IE 7|IE 8|Firefox 3|Firefox 3.5|Safari 3.2
:----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Faster|114x|191x|79x|14.2x|14.9x|2x

Browsers|Safari 4|Chrome 2|Chrome 3|Opera 9.64|Opera 10
:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Faster|3.6x|58x|7.9x|5.7x|3.5x

So where is the cost? When the `length` property of that collection is accessed on every iteration, it causes the collection to be updated, which has occupied too much cost. The way to optimized this is to simply cache the length of that collection into a local variable, and use it instead:

```js
function loopCacheLengthColection() {
    var collection = document.getElementsByTagName('div');
    var len = collection.length;

    for (var count = 0; count < len; count++) {
        /** do nothing */
    }
}
```

> When the collection is a relatively small collection, caching the `length` property is good enough for performance, but if not, using a copied array is more faster. So consider using `toArray()` or `Array.from()` to convert an HTML collection into an copied array first, when it's large.

What if accessing elements of an HTML collection? **Remember to cache it into a local variable**.

```js
/** slow */
function collectionGlobal() {
    var collection = document.getElementsByTagName('div');
    var len = collection.length;
    var name = '';

    for (var count = 0; count < len; count++) {
        name = document.getElementsByTagName('div')[count].nodeName;
        name = document.getElementsByTagName('div')[count].nodeType;
        name = document.getElementsByTagName('div')[count].tagName;
    }

    return name;
}

/** faster */
function collectionLocal() {
    var collection = document.getElementsByTagName('div');
    var len = collection.length;
    var name = '';

    for (var count = 0; count < len; count++) {
        name = collection[count].nodeName;
        name = collection[count].nodeType;
        name = collection[count].tagName;
    }

    return name;
}

/** fastest */
function collectionNodeLocal() {
    var collection = document.getElementsByTagName('div');
    var len = collection.length;
    var name = '';

    for (var count = 0; count < len; count++) {
        var element = collection[count];
        name = element.nodeName;
        name = element.nodeType;
        name = element.tagName;
    }

    return name;
}
```

How fast?

Browsers|IE 6|IE 7|IE 8|Firefox 3|Firefox 3.5|Safari 3.2
:----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Faster (collectionLocal)|2.5x|2.95x|3.6x|2.35x|2.43x|179x
Faster (collectionNodeLocal)|3.23x|3.65x|4.45x|3.62x|4.43x|228x

Browsers|Safari 4|Chrome 2|Chrome 3|Opera 9.64|Opera 10
:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Faster (collectionLocal)|2.15x|4.74x|4.56x|345x|253x
Faster (collectionNodeLocal)|2.74x|5.51x|6.15x|345x|324x

#### 2.4 Walking the DOM

The DOM API has provided multiple methods for accessing specific parts of the overall document structure. In case when you can choose between those approaches, it's beneficial to use the most efficient one.

##### 2.4.1 **Crawling (漫步於) the DOM**

When working with surrounding elements, we may recursively iterating over all children. In this case, not only `childNdoes` we can us, but also the `nextSibling`.

Consider using these two approaches to do a nonrecursive visit of an element's childen:

```js
function visitWtihNextSibling() {
    var el = documet.getElementById('content');
    var ch = el.firstChild;
    var name = '';

    do {
        name = ch.nodeName;
    } while (ch = ch.nextSibling);

    return name;
}

/** and */

function visitWithChildNodes() {
    var el = documet.getElementById('content');
    var ch = el.childNodes;

    /** remember to cache the length into a local variable, cause what `childNodes` return is an HTML collection. */
    var len = ch.length;
    var name = '';

    for (var count = 0; count < len; count++) {
        name = ch[count].nodeName;
    }

    return name;
}
```

These two approaches are mostly equal except in IE. In IE6, `nextSibling` is **16 times** faster than `childNodes`, while in IE7, it's **105 times** faster. Therefore, prefer to use `nextSibling` considering the older IE versions.

##### 2.4.2 **Element Nodes**

DOM properties such as `childNodes`, `firstChild` and `nextSibling` don't distinguish between element nodes and other node types, such as comments or text nodes, which are often just spaces between two tags. Due to this reason, when walking the DOM, you may have to check the type of node, in order to filter out non-element nodes. However, actually this checking is unnecessary DOM work, because most mordern browsers have offered APIs for you, and they are certainly better to be used. (**In IE6, it should be 24 times faster, while 124 times faster in IE7**, but older IE versions are only supported for `children` to access.)

Property|Use as replacement for
:-------|:---------------------
children|childNodes
childElementCount|childNodes.length
firstElementChild|firstChild
lastElementChild|lastChild
nextElementSibling|nextSibling
previousElementSibling|previousSibling

##### 2.4.3 **The Selector API**

Using `getElementById()` or `getElementsByTagName()` or both to identify an element in DOM will be an inefficient way for us. On the other hand, CSS selectors are a convenient way for us because of our familiarity with CSS. For this reason, recent browser versions has provided a method called `querySelectorAll()` as a native browser DOM method. Actually, by using this method, it's faster to identify elements than using JavaScript and DOM to iterate.

```js
var elements = document.querySelectorAll('#menu a');
```

Considering the code above, `elements` will contain a list of references to all `a` elements, which we called that a **NodeList** - another array-like object, but not an HTML collection. So, this can avoid the performance problem of HTML collections mentioned before.

Without this approach, you may code like this. Such verbose you know:

```js
var elements = document.getElementById('menu').getElementsByTagName('a');
```

Another terrible thing is that `elements` will be an HTML collection. It means that you should have to convert it into an array before accessing. In cases that when you want to work with a union of several queries:

With `querySelectorAll`:

```js
var errs = document.querySelectorAll('div.warning, div.notice');
```

With `getElementById` and `getElementsByTagName`:

```js
var errs = [];
var divs = document.getElementsByTagName('div');
var className = '';

for (var i = 0, len = divs.length; i < len; i++) {
    className = divs[i].className;

    if (className === 'notice' || className === 'warning') {
        errs.push(divs[i]);
    }
}
```

The first method should be faster than the second one, but how faster?

Browsers|IE 8|Firefox 3.5|Safari 3.2|Safari 4
:----:|:-----:|:-----:|:-----:|:-----:
Faster|2.46x|2x|6.06x|2.13x

Browsers|Chrome 2|Chrome 3|Opera 10
:------:|:-----:|:-----:|:------:
Faster|3.65x|3.45x|4.88x

Familiar with `querySelectorAll`, `querySelector` is another convenient method for us to use, while it only return the first node matched.

### 3. Repaints and Reflows

Once the browser has downloaded all the components of a page, HTML, markup, JavaScript, CSS, or images, it sill parse through them and **create two internal data structures**:

- *A DOM tree*

    A representation of the page structure

- *A render tree*

    A representation of how the page should be displayed

Hidden DOM elements don't have a corresponding node in the render tree, and nodes in the render tree are called *frames* or *boxes* in accordance with (與 ...  相符) the CSS model that treats page elements as boxes with `margin`, `border`, `padding`, and position. With the DOM and the render tress constructed, the browser can display (or called 'paint') the elements on the page.

When a DOM change affects the geometry of an element (width or height), such as a change in the thickness of the border or adding more text to a paragraph, resulting in an additional line, the browser needs to recalculate the geometry of the element. With the calculated result, the browser will invalidate the part of the render tree that was affected by the change and reconstructs the render tree. This process is know as **Reflow (重排，亦称頁面回流)**. With the reflow completed, the browser will redraw the affected parts of the screen in a process called **Repaint (重繪)**.

So before repaints, are that reflows necessary? The answer is no. Not all DOM changes affect the geometry. For instance, changing the background color of an element won't change its width or height. In that case, there is a repaint only (no reflow).

As both repaint and reflow are expensive operations, which will make the UI of a web application less responsive, it's important to reduce their occurrences whenever possible.

A reflow will happen when:

- Visible DOM elements are added or removed
- Elements change position
- Elements change size (changing in margin, padding, border thickness, width, height, etc.)
- Contents change (text changes or image is replaced with one of a different size.)
- Page renders initially
- Browsers window is resized

What you should notice is that **some changes may cause a reflow of the whole page**: for example, when a scroll bar appears.

#### 3.1 Queuing and Flushing Render Tree Changes

Most browsers will optimize the reflow process by queuing changes and performing them in batches. However, sometimes the queue will be forced to be flushed by us (often involuntarily), in order to make all scheduled changes be applied right way. Flushing the queue happens when we retrieve any layout information like:

- `offsetTop`, `offsetLeft`, `offsetWidth`, `offsetHeight`
- `scrollTop`, `scrollLeft`, `scrollWidth`, `scrollHeight`
- `clientTop`, `clientLeft`, `clientWidth`, `clientHeight`
- `getComputedStyle()` (`currentStyle` in IE)

The browser has to execute the pending changes in the rendering queue, and reflow in order to return correct layout information. For this reason, it's best not to use any properties shown below during the process of changing styles. Otherwise, it will result in some redundant reflow.

Considering the following example:

```js
var computed;
var tmp = '';
var bodyStyle = documet.body.style;

if (document.body.currentStyle) {
    /** IE, Opera */
    computed = document.body.currentStyle;
} else {
    /** W3C */
    computed = document.defaultView.getComputedStyle(document.body, '');
}

/**
 * Each time we retrieve an property, which is unrelated to the changing of color
 * Yet the browser has to flush the render queue and reflow, due to your retrieving
 */
bodyStyle.color = 'red';
tmp = computed.backgroundColor;
bodyStyle.color = 'white';
tmp = computed.backgroundImage;
bodyStyle.color = 'green';
tmp = computed.backgroundAttachment;
```

So, a better approach should avoid retrieving layout information while it's being changed.

```js
bodyStyle.color = 'red';
bodyStyle.color = 'white';
bodyStyle.color = 'green';
tmp = computed.backgroundImage;
tmp = computed.backgroundColor;
tmp = computed.backgroundAttachment;
```

But sometimes, we do need to request those layout information. What we should do is to assign it into a local variables and work with it.

```js
/** inefficient */
function render() {
    el.style.left = 1 + el.offsetLeft + 'px';
    el.style.top = 1 + el.offsetTop + 'px';

    if (el.offsetLeft < 500) {
        requestAnimationFrame(render);
    }
}

/** start the animation */
requestAnimationFrame(render);
```

Instead of this inefficient way, we are going to code like this:

```js
var current = el.offsetLeft;

function render() {
    current++;
    el.style.cssText = 'left: ' + current + 'px; top: ' + current + 'px;';

    if (current < 500) {
        requestAnimationFrame(render);
    }
}

/** start the animation */
requestAnimationFrame(render);
```

#### 3.2 Minimizing Repaints and Reflows

To reduce expensive cost on both two approaches, what you should do is to reduce their number. In another word, just to combine multiple DOM and style changes into a batch and apply them once.

##### 3.2.1 **Style Changes**

Considering this:

```js
/** the worst case will cause reflows three times, though most modern browser will optimize this into once */
var el = document.getElementById('content');
el.style.borderLeft = '1px';
el.style.borderRight = '2px';
el.style.padding = '5px';
```

A more efficient way is to combine all the changes and apply them at once, modifying the DOM only once, by using `cssText`:

```js
var el = document.getElementById('content');
el.style.cssText = 'border-left: 1px; border-right: 2px; padding: 5px;';

/** or keep the existing styles */
el.style.cssText += 'border-left: 1px; border-right: 2px; padding: 5px;';
```

Another efficient way is to use class name to change styles of an element:

```js
var el = document.getElementById('content');

/** with a slight performance hit, but keeping the script free of presentation code, cleaner and more maintainable */
el.className = 'active';
```

##### 3.2.2 **Batching DOM Changes**

What if there are many changes applied to a DOM element, you can reduce reflows and repaints by following these steps:

1. Take the element off the document flow.
2. Apply multiple changes.
3. Bring the element back to the document.

This process will cause two reflows - one at step 1 and one at step 3.

When it comes to how, there are three basic ways to do it:

- Hide the elements, apply changes, and show it again.
- Use a document fragment to build a subtree outside of the live DOM and then copy it to the document.
- Copy the original element into an off-document node, modify the copy, and then replace the original once you've done.

Considering a list of links that must be updated by inserting two new links:

```html
<ul id="list__link">
    <li><a href="http://phpied.com">Stoyan</a></li>
    <li><a href="http://julienlecomte.com">Julien</a></li>
</ul>
```

```js
var data = [
    {
        name: 'Nicholas',
        url: 'http://nczonline.net'
    },
    {
        name: 'Ross',
        url: 'http://techfoolery.net'
    }
];

function appendDataToElement(appendToElement, data) {
    var a;
    var li;

    for (var i = 0, max = data.length; i < max; i++) {
        a = document.createElement('a');
        a.href = data[i].url;
        a.appendChild(document.createTextNode(data[i].name));

        li = document.createElement('li');
        li.appendChild(a);

        appendToElement.appendChild(li);
    }
}
```

Without worrying about reflows, we will complete this task as followed:

```js
var ul = document.getElementById('list__link');
appendDataToElement(ul, data);
```

However, when considering the expensive cost of reflows, we will optimize this with the three approaches mentioned above:

- Hide the elements, apply changes, and show it again.

    ```js
    var ul = document.getElementById('list__link');
    var previousDisplayStyle = ul.style.display;

    ul.style.display = 'none';
    appendDataToElement(ul, data);
    ul.style.display = previousDisplayStyle;
    ```

- Use a document fragment to build a subtree outside of the live DOM and then copy it to the document. (least amount of DOM manipulations and reflows, **Recommended**)

    ```js
    var fragment = document.createDocumentFragment();
    appendDataToElement(fragment, data);
    document.getElementById('list__link').appendChild(fragment);
    ```

- Copy the original element into an off-document node, modify the copy, and then replace the original once you've done.

    ```js
    var old = document.getElementById('list__link');
    var clone = old.cloneNode(true);

    appendDataToElement(clone, data);
    old.parentNode.replaceChild(clone, old);
    ```

#### 3.3 Avoid Reflows for Animations

Reflows sometimes affect only a small part of the render tree, but they can also affect a larger portion or even the whole tree. So, what a terrible disaster will appear, when an animation at the top of the page pushes down almost the whole pages. To avoid using this kind of animations, the followed steps are helpful for you:

1. Using absolute positioning to take elements out of flow of the page.
2. Animate the element. (Even if it expands, there will only be a reflow of a small part of the page.)
3. When the animation is done, restore the positioning, thereby pushing down the rest of the document only once.

#### 3.4 Avoid Using Pseudo Classes `:hover` of CSS

If you have a significant number of elements with a `:hover`, the responsiveness will degrade (降低).

For example, suppose that you have created a table with 500-1000 rows and 5 columns. For each row, you have also used `tr:hover` to highlight. You may find that the highlight is slow to apply, and the CPU usage increases to 80%-90%. So, please **avoid** it.

### 4. Event Delegation

Another performance problem has arisen when lots of elements have attached one or more event handlers. Most attachments have their attaching phase happened at the `onload` (or `DOMContentReady`) event, **resulting in more processing time for loading** pages. In addition, the bowser need to keep track of each event handler, which **takes up memory**. Actually, a great number of event handlers might never be needed. For instance, users only clicked one button or link, but not all of them.

Therefore, a simple and elegant technique for handling even delegation is to use event bubbling, to give this handler to their parents. It means that, you can attach only one handler on a wrapper element to handle all events that happen to the children.

According to the DOM standard, each event has three phase:

- Capturing
- At target
- Bubbling

Even though capturing is not supported by IE, bubbling is good enough for the purpose of delegation.

Considering the following case:

```html
<html>
<head></head>
<body>
    <div>
        <ul id="menu">
            <li>
                <a href="menu1.html">menu #1</a>
            </li>
            <li></li>
            <li></li>
            <!-- ... -->
        </ul>
    </div>
</body>
</html>
```

From the snippet code, we can se that a menu has included sort `li` elements, which has an `a` element for its child.

When the user click the link of `menu #1`, the click event is first received by this `a` element and then bubbles up to `li`, then `ul`, then `div`, and so on, all the way to the top of the document and even the `window`. Suppose that you want to do something before the clicked `a` element starts to reload the page, and you can attach a click event listener in the wrapper, which is the `ul` element here, then inspect this event:

```js
document.getElementById('menu').onclick = function (e) {
    /** x-browser target */
    e = e || window.event;
    var target = e.target || e.srcElement;

    /** only interested in `href` attribute, and exit when it's not the target you want to handle */
    if (target.nodeName !== 'A') {
        return;
    }

    /**
     *  do something
     *  ...
     */

    /** prevent default action and stop propagation of events */
    if (typeof e.preventDefault === 'function') {
        e.preventDefault();
        e.stopPropagation();
    } else {
        e.returnValue = false;
        e.cancleBubble = true;
    }
};
```

As you saw, the event delegation technique is quite simple, and what you should do is only to inspect events to see whether they come from elements you're interested in.

### 5. Summary

To reduce the performance cost related to DOM scripting, keep the following in mind:

- Minimize DOM access, and try to work as much as possible in JavaScript.
- Use local variable to store DOM references which you will use repeatedly.
- Cache HTML collections `length` into a local variable when it's small, or convert it into an array when it's large.
- Use faster APIs when available, such as `firstElementChild` or `querySelectorAll()`.
- Reduce cases of reflows and reprints.
- Using absolute positioning when animating
- Use event delegation to minimize the number of event handlers.
