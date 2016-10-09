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

$$Speed = \frac {\frac 1{t_{innerHTML}} - \frac 1{t_{DOM}}}{\frac 1{t_{DOM}}}$$

Browsers|IE 6|IE 7|IE 8|Firefox 3|Firefox 3.5|Safari 3.2
:----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Speed|3.62x|1.75x|1.64x|1.28x|1.17x|1.06x

Browsers|Safari 4|Chrome 2|Chrome 3|Opera 9.64|Opera 10
:-----:|:-----:|:-----:|:-----:|:-----:|:-----:
Speed|-1.13x|1.35x|-1.15x|1.19x|0.00x
