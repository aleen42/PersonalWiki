## Loading and Execution [Back](./../high_performance.md)

In fact, most browsers use a single process for both user interface (UI) updates and JavaScript execution, so only one can happen at any given moment in time. If we loaded JavaScript between a document, no matter using closed tag or `src` attribute, the browser has to block the user interaction to load and execute the script.

### Script Positioning


