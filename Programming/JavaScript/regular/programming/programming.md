## Programming with Regular Expression [Back](./../regular.md)

This chapter mainly discusses about how to implement regular expressions with JavaScript.

### Literal Regular Expressions in Source Code

- **Problem**

    Assume that you have already had the solution regex "$"'\n\d/\\\\" to a problem, and how to hardcode it into our source code as a string constant or regular expression operator.

- **Solution**

    **/$"'\n\d/\\\\/**

- Discussion

    In JavaScript, we can just place our regular expression between two forward slashes (`/`), which will create a `RegExp` object from the string.

### Import the Regular Expression Library

- **Problem**

    How to import `XRegExp` as a library for the regular expression

- **Solution**
    - Using in the browser:

        ```html
        <script src="xregexp-all-min.js"/></script>
        ```

    - Using Node.js:

        ```js
        var XRegExp = require('xregexp').XRegExp;
        ```

- **Discussion**

    Actually, JavaScript's regular expression support is built-in and always available without any library for support.

### Create Regular Expression Objects

- **Problem**

    How to create a regular expression object in JavaScript

- **Solution**

    ```js
    var regexp = /regex pattern/;

    /** using new operator */
    var regexp = new RegExp('regex pattern');
    ```
- **Discussion**

    If we want to use a regular expression object repeatedly, we can store it into a variable. Except using forward slashes, we can also use the constructor of `RegExp()` to create one object.

### Set Regular Expression Options

- **Problem**

    How to set modes of regular expression in JavaScript?

- **Solution**

    ```js
    var regexp = /regex pattern/im;

    var regexp = new RegExp('regex pattern', 'im');
    ```

- **Discussion**

    In JavaScript, you can specify options by appending one or more single-letter flags to the `RegExp` literal, after the last forward slash. When using constructor, we can pass them as the second parameter.

| Single Letter    | Descriptions     |
| :------------- | :------------- |
| i       | Case insensitive       |
| m       | Search in multiple lines       |
| g       | Search globally with more than two results       |
| y       | Sticky mode       |

### Test if a Match Can Be Found Within a Subject string

- **Problem**

    How to test whether a regular expression has matched something within a subject text?

- **Solution**

    ```js
    if (/regex pattern/.test(subject)) {
        /** successful match */
    } else {
        /** failed to match */
    }
    ```

- **Discussion**

    To test whether a regular expression can match part of a string, we can call the `test()` method of a regular expression object, which accepts the subject text as the only one parameter.

    return `true` when successfully matching, while `false` when failed.
