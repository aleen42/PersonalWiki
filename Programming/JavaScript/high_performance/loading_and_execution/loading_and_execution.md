## Loading and Execution [Back](./../high_performance.md)

In fact, most browsers use a single process for both user interface (UI) updates and JavaScript execution, so only one can happen at any given moment in time. If we loaded JavaScript between a document, no matter using closed tag or `src` attribute, the browser has to block the user interaction to load and execute the script.

### Script Positioning

Traditionally, `<script>` tags that are used to load external JavaScript files have appeared in the `<head>`, along with `<link>` tags to load external CSS files and other metainformation(元信息s) about the page.

The theory was that it's best to **keep as many style and behavior dependencies together**, loading them first so that the page will come in looking and behaving correctly.

```html
<html>
    <head>
        <title>Script Example</title>
        
        <!-- Example of inefficient script positioning -->
        <script type="text/javascript" src="file1.js"></script>
        <script type="text/javascript" src="file2.js"></script>
        <script type="text/javascript" src="file3.js"></script>
        <link rel="stylesheet" type="text/css" href="style.css"></link>
    </head>
</html>
```

Because scripts block downloading of all resource types on the page, it's recommended **to place all `<script>` tags as close to the bottom of the `<body>` tag as possible** so as not to affect the download of the entire page.

```html
<html>
    <head>
        <title>Script Example</title>
        <link rel="stylesheet" type="text/css" href="style.css"></link>
    </head>
    <body>
        <p>Hello World!</p>
        
        <!-- Example of recommended script positioning -->
        <script type="text/javascript" src="file1.js"></script>
        <script type="text/javascript" src="file2.js"></script>
        <script type="text/javascript" src="file3.js"></script>
    </body>
</html>
```

### Grouping Scripts

Since each `<script>` tag blocks the page from rendering during initial download, it's helpful **to limit the total number of `<script>` tags** contained in the page. This applies to both inline scripts as well as those in external files. That's **to reduce the delay while the code is executed**.

> **Never putting an inline script after a `<link>` tag**, because Steve Souders has found that an inline script placed after a `<link>` tag referencing an external stylesheet caused the browser to block while waiting for the stylesheet to download.

Therefore, if a large website or web application has several required JavaScript files, you can use a build tool to concatenate these files together into a single file and import it. 

Yahoo! User Interface (YUI) has given you a way to pull in any nubmer of JavaScrpit files by using **a combo-handled URL** like: http://yui.yahooapis.com/combo?2.7.0/build/yahoo/yahoo-min.js&2.7.0/build/event/event-min.js

### Nonblocking Scripts

The secret to nonblocking scripts is to load the JavaScript source code after the page has finished loading. In technical terms, this means downloading the code after the `load` event of the `window` object has been triggered.

#### Deferred Scripts

HTML 4 defines an additional attribute for the `<script>` tag called `defer`

