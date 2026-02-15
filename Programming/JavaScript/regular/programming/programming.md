## Programming with Regular Expression [Back](./../regular.md)

This chapter mainly discusses about how to implement regular expressions with JavaScript.

### Literal Regular Expressions in Source Code

- **Problem**

    Assume that you have already had the solution regex "$"'\n\d/\\\\" to a problem, and how to hardcode it into our source code as a string constant or regular expression operator.

- **Solution**

    **/$"'\n\d/\\\\/**

- **Discussion**

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

### Find a Match Within Another Match

- **Problem**

    Supposed that we want to match all numbers marked as bold, and you need to match all of them separately.

- **Solution**

    ```js
    var result = [];
    var outerRegex = /<b>([\s\S]*?)<\/b>/g;
    var innerRegex = /\d+/g;

    var outerMatch;
    var innerMatches;

    while (outerMatch = outerRegex.exec(subject)) {
        if (outerMatch.index === outerRegex.lastIndex) {
            outerRegex.lastIndex++;
        }

        innerMatches = outerMatch[1].match(innerRegex);

        if (innerMatches) {
            result = result.concat(innerMatches);
        }
    }
    ```

- **Discussion**

    If you try to combine both regexes into one, you'll end up with something rather different like **/\d+(?=(?:(?!&lt;b&gt;).)*&lt;\/b&gt;)/g**. Though the regular expression just shown is a solution to the problem, it's hardly intuitive (直觀的).

### Replace All Matches

- **Problem**

    Replace all **before** with the replacement text **after**.

- **Solution**

    ```js
    result = subject.replace(/before/g, 'after');
    ```

- **Discussion**

    To search and replace through a string using a regular expression, call the `replace()` method of that string.

### Replace Matches Reusing Parts of the Match

- **Problem**

    How to run a search and replace that reinserts parts of the regex match back into the replacement. For example, match pairs of words delimited by an equals sign, and swap those words in the replacement.

- **Solution**

    ```js
    result = subject.replace(/(\w+)=(\w+)/g, '$2=$1');
    ```

### Replace Matches with Replacements Generated in Code

- **Problem**

    Actually, we can also replace a string with something generated by code. For example, we want to double all matched numbers.

- **Solution**

    ```js
    result = subject.replace(/\d+/g, function (match) {
        return 2 * match;
    });
    ```

- **Discussion**

    In JavaScript, a function is really just another object that can be assigned to a variable. Instead of passing a literal string or a variable that holds a string to the `String.prototype.replace()` function, we can pass a function that returns a string. This function is then called each time a replacement needs to be made.

    If a regular expression has one capturing group or more, you can pass more parameters to catch it. For example, the second parameter you passed will match the first capturing group's value.

### Replace All Matches Within the Matches of Another Regex

- **Problem**

    What if we want to replace all matches within the matches of another regex? For example, replace all **before** marked as bold, with **after**.

- **Solution**

    ```js
    result = subject.replac(/<b>.*?<\/b>/g, function (match) {
        return match.replace(/before/g, 'after');
    });
    ```

### Replace All Matches Between the Matches of Another Regex

- **Problem**

    Considering about replace straight double quotes with smart double quotes, but only the string outside of HTML tags. For example, convert **"text" &lt;span class="middle"&gt;"text"&lt;/span&gt; "text"** into **“text” &lt;span class="middle"&gt;“text”&lt;/span&gt; “text”**.

- **Solution**

    ```js
    var result = '';

    var outerRegex = /<[^<>]*>/g;
    var innerRegex = /"([^"]*)"/g;

    var outerMatch = null;
    var lastIndex = 0;

    while (outerMatch = outerRegex.exec(subject)) {
        if (outerMatch.index === outerRegex.lastIndex) {
            outerRegex.lastIndex++;
        }

        /** search and replace through the text between this match */
        var textBetween = subject.slice(lastIndex, outerMatch.index);
        result += textBetween.replace(innerRegex, '\u201C$1\u201D');

        lastIndex = outerMatch.index + outerMatch[0].length;

        /** append unchanged part */
        result += outerMatch[0];
    }

    /** search and replace through the remainder after the last regex match */
    var textAfter = subject.slice(lastIndex);
    result += textAfter.replace(innerRegex, '\u201C$1\u201D');
    ```

### Split a string

- **Problem**

    How to split a string using a regular expression? For example, splitting **I like &lt;b&gt;bold&lt;/b&gt; and &lt;i&gt;italic&lt;/i&gt; fonts** should result in an array of **I like**, **bold**, **and**, **italic**, **and fonts**.

- **Solution**

    In JavaScript, you can directly use `String.prototype.split()` to split a string, which will accept a string or a regex.

    ```js
    result = subject.split(/<[^<>]*>/);
    ```

- **Discussion**

    In JavaScript, call the `split()` method on the string you want to split. The second optional parameter can be accepted to specify the maximum number of strings that you want to have in the returned array, and the number should be positive. If you pass a negative number, the string will be split as many times as possible. In addition, setting the `/g` flag for the regex makes no difference.

    Since the method has had problems in older browsers, it's recommended to redefine it with a polyfill:

    ```js
    /*!
     * Cross-Browser Split 1.1.1
     * Copyright 2007-2012 Steven Levithan <stevenlevithan.com>
     * Available under the MIT License
     * ECMAScript compliant, uniform cross-browser split method
     */

    /**
     * Splits a string into an array of strings using a regex or string separator. Matches of the
     * separator are not included in the result array. However, if `separator` is a regex that contains
     * capturing groups, backreferences are spliced into the result each time `separator` is matched.
     * Fixes browser bugs compared to the native `String.prototype.split` and can be used reliably
     * cross-browser.
     * @param {String} str String to split.
     * @param {RegExp|String} separator Regex or string to use for separating the string.
     * @param {Number} [limit] Maximum number of items to include in the result array.
     * @returns {Array} Array of substrings.
     * @example
     *
     * // Basic use
     * split('a b c d', ' ');
     * // -> ['a', 'b', 'c', 'd']
     *
     * // With limit
     * split('a b c d', ' ', 2);
     * // -> ['a', 'b']
     *
     * // Backreferences in result array
     * split('..word1 word2..', /([a-z]+)(\d+)/i);
     * // -> ['..', 'word', '1', ' ', 'word', '2', '..']
     */
    var split;

    // Avoid running twice; that would break the `nativeSplit` reference
    split = split || function (undef) {
        var nativeSplit = String.prototype.split;
        var compliantExecNpcg = /()??/.exec("")[1] === undef; // NPCG: nonparticipating capturing group
        var self;

        self = function (str, separator, limit) {
            // If `separator` is not a regex, use `nativeSplit`
            if (Object.prototype.toString.call(separator) !== "[object RegExp]") {
                return nativeSplit.call(str, separator, limit);
            }

            var output = [];
            var flags = (separator.ignoreCase ? "i" : "") +
                        (separator.multiline  ? "m" : "") +
                        (separator.extended   ? "x" : "") + // Proposed for ES6
                        (separator.sticky     ? "y" : ""); // Firefox 3+
            var lastLastIndex = 0;
            // Make `global` and avoid `lastIndex` issues by working with a copy
            var separator = new RegExp(separator.source, flags + "g");
            var separator2, match, lastIndex, lastLength;

            str += ""; // Type-convert

            if (!compliantExecNpcg) {
                // Doesn't need flags gy, but they don't hurt
                separator2 = new RegExp("^" + separator.source + "$(?!\\s)", flags);
            }

            /* Values for `limit`, per the spec:
             * If undefined: 4294967295 // Math.pow(2, 32) - 1
             * If 0, Infinity, or NaN: 0
             * If positive number: limit = Math.floor(limit); if (limit > 4294967295) limit -= 4294967296;
             * If negative number: 4294967296 - Math.floor(Math.abs(limit))
             * If other: Type-convert, then use the above rules
             */
            limit = limit === undef ?
                -1 >>> 0 : // Math.pow(2, 32) - 1
                limit >>> 0; // ToUint32(limit)
            while (match = separator.exec(str)) {
                // `separator.lastIndex` is not reliable cross-browser
                lastIndex = match.index + match[0].length;
                if (lastIndex > lastLastIndex) {
                    output.push(str.slice(lastLastIndex, match.index));
                    // Fix browsers whose `exec` methods don't consistently return `undefined` for
                    // nonparticipating capturing groups
                    if (!compliantExecNpcg && match.length > 1) {
                        match[0].replace(separator2, function () {
                            for (var i = 1; i < arguments.length - 2; i++) {
                                if (arguments[i] === undef) {
                                    match[i] = undef;
                                }
                            }
                        });
                    }
                    if (match.length > 1 && match.index < str.length) {
                        Array.prototype.push.apply(output, match.slice(1));
                    }
                    lastLength = match[0].length;
                    lastLastIndex = lastIndex;
                    if (output.length >= limit) {
                        break;
                    }
                }
                if (separator.lastIndex === match.index) {
                    separator.lastIndex++; // Avoid an infinite loop
                }
            }
            if (lastLastIndex === str.length) {
                if (lastLength || !separator.test("")) {
                    output.push("");
                }
            } else {
                output.push(str.slice(lastLastIndex));
            }
            return output.length > limit ? output.slice(0, limit) : output;
        };

        // For convenience
        String.prototype.split = function (separator, limit) {
            return self(this, separator, limit);
        };

        return self;
    }();
    ```

### Search Line by Line

- **Problem**

    How to search line by line with a regular expression?

- **Solution**

    Create an array for storing lines of a subject text:

    ```js
    var lines = subject.split(/\r?\n/);
    ```

    Then, iterate over this array:

    ```js
    var regex = /regex pattern/;
    for (var i = 0; i < regex.length; i++) {
        if (linex[i].match(regex)) {
            /** match something */
        } else {
            /** failed to match */
        }
    }
    ```

> Internet Explorer 8 and prior do not follow the JavaScript standard that requires nonparticipating groups to be `undefined` in the match object. IE8 stores empty strings for nonparticipating groups, making it impossible to distinguish between a group that did not participate, and one that participated and captured a zero-length string. This means the JavaScript solution will not work with IE8 and prior. This bug was fixed in Internet Explorer 9.
