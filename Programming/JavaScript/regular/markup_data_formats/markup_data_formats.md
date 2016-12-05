## Markup and Data Formats [Back](./../regular.md)

This chapter mainly covers some regular expressions about markup languages and some data formats: HTML, XHTML, XML, CSV, and INI. However some of these formats can be surprisingly complex to process and manipulate accurately, at least using regular expressions.

### Basic rules for formats covered in this chapter

#### Hypertext Markup Language (HTML)

HTML is used to describe the structure, semantics, and appearances of billions of web pages and other documents. In this chapter, we'll only concentrate on the rule needed to process the key components of well-formed HTML: **elements (and the attributes they contain)**, **character references**, **comments**, and **document type declarations**.

#### Extensible Hypertext Markup Language (XHTML)

XHTML is designed as successor (接替者) to HTML 4.01, and migrated HTML from its SGML heritage (遺產) to an XML foundation. However, because development of HTML continued separately, XHTML5 is now being developed as part of the HTML5 specification, and will be the XML serialization of HTML5 rather than introducing new features of its own.

#### Extensible Markup Language (XML)

XML is a general-purpose language designed primarily for sharing structured data. It's used as the foundation to create a wde array of markup languages, including XHTML.

#### Comma-Separated Values (CSV)

CSV is an old but still very common file format used for spreadsheet-like data.

#### Initialization files (INI)

The lightweight INI file format is commonly used for configuration files. It is poorly defined, and as a result, there is plenty of variation in how different programs and systems interpret the format.

### Find XML-style tags

- **Problem**

    You may want to match any HTML, XHTML, or XML tags in a string, how?

- **Solution**
    - Quick and dirty:

        **/<[&#94;>]&#42;>/**

    - Allow `>` in attribute values:

        **/<(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;>/**

    - (X)HTML tags (loose):

        **/<\\/?([A-Za-z][&#94;\\s>\\/]&#42;)(?:=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;\\s>]+)|[&#94;>])&#42;(?:>|$)/**

    - (X)HTML tags (strict):

        **/<(?:([A-Z][-:A-Z0-9]&#42;)(?:\s+[A-Z][-:A-Z0-9]&#42;(?:\s&#42;=\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;"'`=<>\s]+))?)&#42;\s&#42;\\/?|\\/([A-Z][-:A-Z0-9]&#42;)\s&#42;)>/**

    - XML tags (strict):

        **/<(?:([_:A-Z][-.:\\w]&#42;)(?:\\s+[_:A-Z][-.:\\w]&#42;\\s&#42;=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'))&#42;\\s&#42;\\/?|\\/([_:A-Z][-.:\\w]&#42;)\\s&#42;)>/**

- **Discussion**

    If you want to sterilize (卸除) HTML from untrusted sources because you're worried about specially-crafted malicious HTML and cross-site scripting (XSS) attacks, your safest bet is to first convert all `<` and `>` and `&` characters to their corresponding named character references (`&lt;`, `&gt;`, `&amp;`), then bring back tags that are known to be safe (as long as they contain no attributes or only using approved attributes). For example, use the following code to bring back `<p>`, `<em>`, and `<strong>`:

    ```js
    subject = subject.replace(/&lt;(/?)(p|em|strong)&gt;/, '<$1$2>');
    ```

### Replace &lt;b&gt; tags with &lt;strong&gt;

- **Problem**

    How to replace all **&lt;b&gt;** tags in a string with corresponding **&lt;strong&gt;** tags?

- **Solution**

    ```js
    function replaceB(subject) {
        subject = subject.replace(/<(\/?)b\b((?:[^>"']|"[^"]*"|'[^']*')*)>/ig, '<$1strong$2>');
    }
    ```

- **Discussion**

    If you want to match any tag from a list of tag names, you can use the regex like this: **/<(\/?)([bi]|em|big)\b((?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;)>/ig**.

### Remove all XML-style tags except &lt;em&gt; and &lt;strong&gt;

- **Problem**

    You may want to remove all tags in a string except `<em>` and `<strong>`.

- **Solution**
    - Match tags except `<em>` and `<strong>`:

        ```js
        function replace(subject) {
            subject = subject.replace(/<\/?(?!(?:em|strong)\b)[a-z](?:[^>"']|"[^"]*"|'[^']*')*>/gi, '');
        }
        ```

    - Match tags except `<em>` and `<strong>`, and any tags that contain attributes:

        ```js
        function replace(subject) {
            subject = subject.replace(/<\/?(?!(?:em|strong)\s*>)[a-z](?:[^>"']|"[^"]*"|'[^']*')*>/gi, '');
        }
        ```

- **Discussion**

    Consider the case when you need to match all tags except `<a>`, `<em>`, and `<strong>`, with two exceptions:

    - Any `<a>` tags that have attributes other than `href` or `title` should be matched
    - Any `<em>` or `<strong>` tags with attributes

    ```js
    function replace(subject) {
        subject = subject.replace(/<(?!(?:em|strong|a(?:\s+(?:href|title)\s*=\s*(?:"[^"]*"|'[^']*'))*)\s*>)[a-z](?:[^>"']|"[^"]*"|'[^']*')*> /gi, '');
    }
    ```

### Convert plain text to HTML by adding &lt;p&gtp; and &lt;br&gtp; tags

- **Problem**

    Given a plain text string, you may want to convert it to an HTML fragment to display within a web page. Paragraphs, separated by two line breaks in a row, should be surrounded with `<p>...</p>`. Additional line breaks should be replaced with `<br>` tags.

- **Solution**
    - Step 1: replace HTML special characters with named character references

        ```js
        subject = subject.replace(/&/ig, '&amp;');
        subject = subject.replace(/</ig, '&lt;');
        subject = subject.replace(/>/ig, '&gt;');
        ```

    - Step 2: replace all line breaks with `<br>`

        ```js
        subject = subject.replace(/\r\n?|\n/g, '<br>');
        ```

    - Step 3: replace double `<br>` tags with `</p><p>`

        ```js
        subject = subject.replace(/<br>\s*<br>/g, '</p><p>');
        ```

    - Step 4: wrap the entire string with `<p>...</p>`

        ```js
        subject = '<p>' + subject + '</p>';
        ```

### Find a specific attribute in XML-style tags

- **Problem**

    How to find a specific attribute such as **id** within an (X)HTML or XML file?

- **Solution**
    - Tags that contain an id attribute (quick and dirty):

        **/<[&#94;>]+\\sid\\b[&#94;>]&#42;>/i**

    - Tags that contain an id attribute (more reliable):

        **/<(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')+?\\sid\\s&#42;=\\s&#42;("[&#94;"]&#42;"|'[&#94;']&#42;')(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;>/i**

    - `<div>` tags that contain an id attribute:

        **/<div\s(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;?\\bid\\s&#42;=\\s&#42;("[&#94;"]&#42;"|'[&#94;']&#42;')(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;>/i**

    - Tags that contain an id attribute with the value "my-id":

        **/<(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')+?\\sid\\s&#42;=\\s&#42;(?:"my-id"|'my-id')(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;>/i**

    - Tags that contain "my-class" within their class attribute value:

        ```js
        function match(subject) {
            var result = /^(?:[^>"']|"[^"]*"|'[^']*')+?\sclass\s*=\s*("[^"]*"|'[^']*')/gi.exec(subject) || [];
            var resultLen = result.length;
            var results = [];

            for (var i = 0; i < resultLen; i++) {
                results.concat(result[i].match(/["'\s]my-class["'\s]/i) || []);
            }
        }
        ```

### Add a cellspacing attribute to &lt;table&gt; tags that do not already include it

- **Problem**

    You may want to search through an (X)HTML file and add `cellspacing="0"` to all tables that do not already include a `cellspacing` attribute.

- **Solution**
    - Simplistic:

        ```js
        function insert(subject) {
            subject = subject.replace(/<table\b(?![^>]*?\scellspacing\b)([^>]*)>/i, '<table cellspacing="0"$1>');
        }
        ```

    - More reliable:

        ```js
        function insert(subject) {
            subject = subject.replace(/<table\b(?!(?:[^>"']|"[^"]*"|'[^']*')*?\scellspacing\b)((?:[^>"']|"[^"]*"|'[^']*')*)>/i, '<table cellspacing="0"$1>');
        }
        ```
