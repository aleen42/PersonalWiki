## DOM Scripting [Back](./../high_performance.md)

### DOM

The Document Object Method (DOM) is a language-independent application interface (API) for working with XML and HTML documents.

#### Inherently Slow

An excellent analogy is to think of DOM as a piece of land and JavaScript (meaning ECMAScript) as another piece of land, both connected with a toll(收費的) bridge.

Once you access to the DOM, you need to pay for it. **More you work, more you pay**.

### Dom Access and Modification

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

#### innerHTML vs DOM methods

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

#### Cloning Nodes

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

#### HTML collections

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

#### Walking the DOM

The DOM API has provided multiple methods for accessing specific parts of the overall document structure. In case when you can choose between those approaches, it's beneficial to use the most efficient one.

##### **Crawling (漫步於) the DOM**

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
        name = ch[count].nodeName.
    }

    return name;
}
```

These two approaches are mostly equal except in IE. In IE6, `nextSibling` is **16 times** faster than `childNodes`, while in IE7, it's **105 times** faster. Therefore, prefer to use `nextSibling` considering the older IE versions.

##### **Element nodes**

DOM properties such as `childNodes`, `firstChild` and `nextSibling` don't distinguish between element nodes and other node types, such as comments or text nodes, which are often just spaces between two tags. Due to this reason, when walking the DOM, you may have to check the type of node, in order to filter out non-element nodes. However, actually this checking is unnecessary DOM work, because most mordern browsers have offered APIs for you, and they are certainly better to be used. (**In IE6, it should be 24 times faster, while 124 times faster in IE7**, but older IE versions are only supported for `children` to access.)

Property|Use as replacement for
:-------|:---------------------
children|childNodes
childElementCount|childNodes.length
firstElementChild|firstChild
lastElementChild|lastChild
nextElementSibling|nextSibling
previousElementSibling|previousSibling

##### **The Selector API**

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

### Repaints and Reflows

Once the browser has downloaded all the components of a page, HTML, markup, JavaScript, CSS, or images, it sill parse through them and **create two internal data structures**:

- *A DOM tree*

    A representation of the page structure

- *A render tree*

    A representation of how the page should be displayed

Hidden DOM elements don't have a corresponding node in the render tree, and nodes in the render tree are called *frames* or *boxes* in accordance with (與 ...  相符) the CSS model that treats page elements as boxes with `margin`, `border`, `padding`, and position. With the DOM and the render tress constructed, the browser can display (or called 'paint') the elements on the page.

When a DOM change affects the geometry of an element (width or height), such as a change in the thickness of the border or adding more text to a paragraph, resulting in an additional line, the browser needs to recalculate the geometry of the element. With the calculated result, the browser will invalidate the part of the render tree that was affected by the change and reconstructs the render tree. This process is know as **Reflow (回流，亦称重排)**. With the reflow completed, the browser will redraw the affected parts of the screen in a process called **Repaint (重繪)**.
