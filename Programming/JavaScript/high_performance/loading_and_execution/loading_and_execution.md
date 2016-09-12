## Loading and Execution [Back](./../high_performance.md)

In fact, most browsers use a single process for both user interface (UI) updates and JavaScript execution, so only one can happen at any given moment in time. If we loaded JavaScript between a document, no matter using closed tag or `src` attribute, the browser has to block the user interaction to load and execute the script.

### Script Positioning

Traditionally, `<script>` tags that are used to load external JavaScript files have appeared in the `<head>`, along with `<link>` tags to load external CSS files and other metainformation(元信息s) about the page.

The theory was that it's best to **keep as many style and behavior dependencies together**, loading them first so that the page will come in looking and behaving correctly
