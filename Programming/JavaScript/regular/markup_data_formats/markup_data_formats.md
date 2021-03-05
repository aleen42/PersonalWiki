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

        **/&lt;[&#94;&gt;]&#42;&gt;/**

    - Allow `>` in attribute values:

        **/&lt;(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;&gt;/**

    - (X)HTML tags (loose):

        **/&lt;\\/?([A-Za-z][&#94;\\s&gt;\\/]&#42;)(?:=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;\\s&gt;]+)|[&#94;&gt;])&#42;(?:&gt;|$)/**

    - (X)HTML tags (strict):

        **/&lt;(?:([A-Z][-:A-Z0-9]&#42;)(?:\s+[A-Z][-:A-Z0-9]&#42;(?:\s&#42;=\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;"'`=&lt;&gt;\s]+))?)&#42;\s&#42;\\/?|\\/([A-Z][-:A-Z0-9]&#42;)\s&#42;)&gt;/**

    - XML tags (strict):

        **/&lt;(?:([_:A-Z][-.:\\w]&#42;)(?:\\s+[_:A-Z][-.:\\w]&#42;\\s&#42;=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'))&#42;\\s&#42;\\/?|\\/([_:A-Z][-.:\\w]&#42;)\\s&#42;)&gt;/**

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

    If you want to match any tag from a list of tag names, you can use the regex like this: **/&lt;(\/?)([bi]|em|big)\b((?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;)&gt;/ig**.

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

        **/&lt;[&#94;&gt;]+\\sid\\b[&#94;&gt;]&#42;&gt;/i**

    - Tags that contain an id attribute (more reliable):

        **/&lt;(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')+?\\sid\\s&#42;=\\s&#42;("[&#94;"]&#42;"|'[&#94;']&#42;')(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;&gt;/i**

    - `<div>` tags that contain an id attribute:

        **/&lt;div\s(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;?\\bid\\s&#42;=\\s&#42;("[&#94;"]&#42;"|'[&#94;']&#42;')(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;&gt;/i**

    - Tags that contain an id attribute with the value "my-id":

        **/&lt;(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')+?\\sid\\s&#42;=\\s&#42;(?:"my-id"|'my-id')(?:[&#94;&gt;"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;&gt;/i**

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
            subject = subject.replace(/<table\b(?![^>]*?\scellspacing\b)([^>]*)>/ig, '<table cellspacing="0"$1>');
        }
        ```

    - More reliable:

        ```js
        function insert(subject) {
            subject = subject.replace(/<table\b(?!(?:[^>"']|"[^"]*"|'[^']*')*?\scellspacing\b)((?:[^>"']|"[^"]*"|'[^']*')*)>/ig, '<table cellspacing="0"$1>');
        }
        ```

### Remove XML-style comments

- **Problem**

    You may want to remove comments from an (X)HTML or XML document.

- **Solution**

    ```js
    function removeComments(subject) {
        subject = subject.replace(/<!--[\s\S]*?-->/ig, '');
    }
    ```

- **Discussion**

    If we want to match valid XML comments, we can use the regular expression to solve it: **/&lt;!--[&#94;-]&#42;(?:-[&#94;-]+)&#42;--\s&#42;&gt;/ig**, while if we want to match valid HTML comments, we can use another regex: **/&lt;!--(?!-?&gt;)[&#94;-]&#42;(?:-[&#94;-]+)&#42;--&gt;/ig**.

### Find words within XML-style comments

- **Problem**

    How to find all occurrences of the word **TODO** within (X)HTML or XML comments?

- **Solution**

    **/\\bTODO\\b(?=(?:(?!&lt;!--)[\\s\\S])&#42;?--&gt;)/i**

### Change the delimiter (定界符) used in CSV files

- **Problem**

    You want to change all field-delimiting commas in a CSV file to tabs.

- **Solution**

    ```js
    function commas2Tabs(subject) {
        var regex = /(,|\r?\n|^)([^",\r\n]+|"(?:[^"]|"")*")?/g;
        var result = '';
        var match;

        while (match = regex.exec(subject)) {
            /** check the value of backreference 1 */
            if (match[1] === ',') {
                /**
                 * Add a tab (in place of the matched comma) and backreference 2 to the result.
                 * If backreference 2 is undefiend use an empty string instead.
                 */
                result += '\t' + (match[2] || '');
            } else {
                /** add the entire match to the result */
                result += match[0];
            }

            /**
             * If there is an empty match, prevent some browsers from getting stuck in an infinite loop
             */
            if (match.index === regex.lastIndex) {
                regex.lastIndex++;
            }
        }

        subject = result;
    }
    ```

### Extract CSV fields from a specific column

- **Problem**

    How to extract every field from the third column of a CSV file?

- **Solution**

    ```js
    function getCSVColumn(csv, index) {
        var regex = /(,|\r?\n|^)([^",\r\n]+|"(?:[^"]|"")*")?/g;
        var result = [];
        var columnIndex = 0;
        var match;

        while (match = regex.exec(csv)) {
            /**
             *  Check the value of backreference 1. If it's a comma,
             *  increment columnIndex. Otherwise, reset it to zero.
             */
            if (match[1] === ',') {
                columnIndex++;
            } else {
                columnIndex = 0;
            }

            if (columnIndex === index) {
                /** Add the field (backref 2) at the end of the result array */
                result.push(match[2]);
            }

            /**
             * If there is an empty match, prevent some browsers from getting
             * stuck in an infinite loop
             */
            if (match.index === regex.lastIndex) {
                regex.lastIndex++;
            }
        }

        csv = result;
    }
    ```

- **Discussion**

    Although using code to iterate over a string one CSV field at a time allows for extra flexibility, if you're using a text editor t get the job done, you may be limited to just search-and-replace:

    - Match a CSV record and capture the field in column 1 to backreference 1:

        ```js
        function replace(subject) {
            subject = subject.replace(/^([^",\r\n]+|"(?:[^"]|"")*")?(?:,(?:[^",\r\n]+|"(?:[^"]|"")*")?)*/m, '$1');
        }
        ```

    - Match a CSV record and capture the field in column 2 to backreference 1:

        ```js
        function replace(subject) {
            subject = subject.replace(/^(?:[^",\r\n]+|"(?:[^"]|"")*")?,([^",\r\n]+|"(?:[^"]|"")*")?(?:,(?:[^",\r\n]+|"(?:[^"]|"")*")?)*/m, '$1');
        }
        ```

    - Match a CSV record and capture the field in column 3 or higher to backreference 1

        ```js
        function replace(subject) {
            subject = subject.replace(/^(?:[^",\r\n]+|"(?:[^"]|"")*")?(?:,(?:[^",\r\n]+|"(?:[^"]|"")*")?){1},([^",\r\n]+|"(?:[^"]|"")*")?(?:,(?:[^",\r\n]+|"(?:[^"]|"")*")?)*/m, '$1');
        }
        ```

### Match INI section headers

- **Problem**

    You may want to match all section headers in an INI file.

- **Solution**

    **/^\\[[&#94;\\]\\r\\n]+]/m**

- **Discussion**

    If you only want to find a specific section header, that's even easier.

        **/^\\[Section1]/m**

### Match INI section blocks

- **Problem**

    You may need to match each complete INI section block in order to split up an INI file or process each block separately.

- **Solution**

    **/^\\[[&#94;\\]\\r\\n]+](?:\\r?\\n(?:[&#94;[\\r\\n].&#42;)?)&#42;/m**

### Match INI name-value pairs

- **Problem**

    You may want to match INI parameter name-value pairs (e.g., **item1=value1**), separating each match into two parts using capturing groups.

- **Solution**

    **/^([&#94;=;\\r\\n]+)=([&#94;;\\r\\n]&#42;)/m**
