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

### Test Whether a Regex Matches the entire Subject Text

- **Problem**

    What if I want to check whether a regular expression has matched the whole subject text?

- **Solution**

    ```js
    if (/^regex pattern$/.test(subject)) {
        /** successful match */
    } else {
        /** failed to match */
    }
    ```

- **Discussion**

    JavaScript does not have a function for testing whether a regex matches a string entirely, so we have to choose another solution by adding `^` and `&` at the start and the end of the regular expression. Notice that, when using them to solve problems, you should guarantee that you have not used '/m' mode, which will result in matching at line breaks.

### Retrieve the Matched Text

- **Problem**

    How to extract the text that was matched?

- **Solution**

    ```js
    var result = subject.match(/\d+/);
    result = result ? result[0] : '';
    ```

- **Discussion**

    `String.prototype.match()` has accepted a regular expression object as its only parameter, which will return `null` when failed to match. Or if successful, it will return an array with the detail of the match. Normally, the first item of the array will return what it matched, and following items will include the value of capturing groups if existed. Notice that, with `/g` flag, `String.prototype.match()` will behave differently.

### Determine the Position and Length of the Match

- **Problem**

    Instead of extracting the substring matched by the regular expression, we want to determine the starting position an length of the match.

- **Solution**

    ```js
    var matchStart = -1;
    var matchLen = -1;

    var match = /\d+/.exec(subject);

    if (match) {
        matchStart = match.index;
        matchStart = match[0].length;
    }
    ```

- **Discussion**

    Call the `exec()` method on a `RegExp` object will get an array with details about the match, if successful to match. This array has a few additional properties, in which `index` will stores the position in the subject string at which the regex match begins. Tshe first item in the array is what we match with a regular expression, and of course we can get the length of it.

    Notice that: try not to use `lastIndex` property of the array, as it's undefined, but defined in the `RegExp` object. Besides, it's not recommended to use it in a `RegExp` object, because of the reliability through different browsers. If we do want to determine the end position, we can just add the value of `index` property, and the value of `length` property in the first item in the array.

### Retrieve Part of the Matched Text

- **Problem**

    How to extract part of the matched text like extract **www.regexcookbook.com** from the string **Please visit http://www.regexcookbook.com**.

- **Soltion**

    ```js
    var result = '';
    var match = /http:\/\/([a-z9-9.-]+)/.exec(subject);

    if (match) {
        result = match[1];
    } else {
        result = '';
    }
    ```

- **Discussion**

    As explained in the previous recipe, the exec() method of a regular expression object returns an array with details about the match. Element zero in the array holds the overall regex match. Element one holds the text matched by the first capturing group, element two stores the second group’s match, etc. If nothing is matched, `RegExp.match()` will return `null`.

### Retrieve a List of All Matches

- **Problem**

    In many cases, a regular expression that partially matches a string can find another match in the remainder of the string. How?

- **Solution**

    ```js
    var list = subject.match(/\d+/g);
    ```

- **Discussion**

    The `\g` flag tells the `match()` method to iterate over all matches in the string and put them into an array. Notice that, if nothing is matched, the `match()` method will return a `null` as usual rather than an empty array.

### Iterate over All Matches

- **Problem**

    What if you want to iterate over all the matches

- **Solution**

    Remember to avoid the case of a regular expression yielding a zero-length match:

    ```js
    var regex = /\d+/g;
    var match = null;

    while (match = regex.exec(subject)) {
        /** Don't let browsers get stuck in an infinite loop */
        if (match.index === regex.lastIndex) {
            regex.lastIndex++;
        }

        /**
         * ...
         * Here you can process the match stored in the match variable
         */
    }
    ```

- **Discussion**

     `while (regexp.exec())` finds all numbers in the subject string when `regexp = /\d+/g`. If `regexp = /\d+/`, then `while (regexp.exec())` finds the first number in the string again and again, until your script crashes or is forcibly terminated by the browser.

     While using `\g`, the regular expression updates the `lastIndex` property of the `RegExp` object on which you're calling `exec()`. Next time when you call `exec()`, the match attempt will begin at `lastIndex`. If you assign a new value to `lastIndex`, the match attempt will begin at the position you specified.

     However, if you read the ECMA-262v3 standard for JavaScript literally, then `exec()` should set `lastIndex` to the first character after the match, which means that if the match is zero character long, it results in an infinite loop.

     To avoid this case of problem, what we should do is to increment `lastIndex` if the `exec()` has not already done this.

     Besides, we can also directly find out all the matched items with `String.prototype.match()`, and use `for` loop to iterate over the list.

### Validate Matches in Procedural Code

- **Problem**

    With iteration over a list of matches, of course you can also extract out what you really want. For example, I want to retain those that are an integer multiple of 13.

- **Solution**

    ```js
    var regex = /\d+/g;
    var match = null;
    var list = [];

    while (match = regex.exec(subject)) {
        /** Don't let browsers get stuck in an infinite loop */
        if (match.index === regex.lastIndex) {
            regex.lastIndex++;
        }

        if (match[0] % 13 === 0) {
            list.push(match[0]);
        }
    }
    ```
