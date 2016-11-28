## Words, Lines, and Special Characters [Back](./../regular.md)

This chapter is mainly showing a variety of regular expression constructs and techniques in action, which may be helpful for you to solve specific problems you're facing.

### Find a specific word

- **Problem**

    Find all occurrences of the word **cat**, case insensitively, and do not match any longest words such as **hellcat**, **application**, or **Catwoman**.

- **Solution**

    **/\\bcat\\b/i**

- **Discussion**

    A problem can occur when working with international text in JavaScript, since this kind of regular expression flavors only consiers letters in the ASCII table to create a word boundary. In other words, word boundaries are found only at the positions between a match of **/[&#94;A-Za-z0-9]|^/** and **/[A-Za-z0-9_]/**, or between **/[A-Za-z0-9_]/** and **/[&#94;A-Za-z0-9_]|$/**. It means that `\b` is not helpful when searching within text that contains accented (異國的) letters or words that use non-Latin scripts.

    For example, **/\\büber\\b/** will find a match within **darüber**, but not within **dar über**.

    The problem occurs because **ü** is considered a non-word character, and a word boundary is therefore found between the two character **rü**, while no word boundary is found between a space character and **ü**, because that creates a contiguous (連續的) sequence of non-word characters.

    Due to this reason, we may have to consider a more complex way to work around the problem:

    ```js
    /** 8-bit-wide letter characters */
    var pL = 'A-Za-z\xAA\xB5\xBA\xC0-\xD6\xD8-\xF6\xF8-\xFF';
    var pattern = '([^{L}]|^)cat([^{L}]|$)'.replace(/{L}/g, pL);
    var regex = new RegExp(pattern, 'gi');

    /** replace cat with dog, and put back any additional matched characters */
    subject = subject.replace(regex, '$1dog$2');
    ```

### Find any of multiple words

- **Problems**

    How to find any one out of a list of words, without having to search through the subject string multiple times?

- **Solution**
    - The simplest way is to just alternate between the words you want to match:

        **/\\b(?:one|two|three)\\b/**

    - A reusable way is to define a function:

    ```js
    function matchWords(subject, words) {
        var regexMetachars = /[(){[*+?.\\^$|]/g;
        var wordLen = words.length;

        /**
         *  Any regex metacharacters within the accepted words are escaped
         *  with a backslash before searching.
         */
        for (var i = 0; i < wordLen; i++) {
            words[i] = words[i].replace(regexMetachars, '\\$&');
        }

        var regex = new RegExp('\\b(?:' + words.join('|') + ')\\b', 'gi');

        return subject.match(regex) || [];
    }

    matchWords(subject, ['one', 'two', 'three']);
    ```

- **Discussion**

    As the regex engine attempts to match each word in the list from left to right, you may find a slight performance gain by placing words that are most likely to be found in the subject text near the beginning of the list.

### Find similar words

- **Problems**

    There're several cases of finding similar words

- **Solution**
    - **Color or colour**

        **/\\bcolou?r\\b/i**

    - **Bat, cat, or rat**

        **/\\b[bcr]at\\b/i**

    - **Words ending with "phobia"**

        **/\\b\\w*phobia\\b/i**

    - **Steve, Steven, or Stephen**

        **/\\bSte(?:ven?|phen)\\b/i**

### Find all except a specific word

- **Problem**

    You may want to use a regular expression to match any word except **cat**.

- **Solution**

    You can use a negative lookahead in JavaScript:

    **/\\b(?!cat\\b)\\w+\\b/i**

- **Discussion**

    Certainly, if you're trying t match any word that does not contain **cat**, you may need to use a slightly different way: **/\\b(?:(?!cat)\\w)+\\b/i**.

### Find any word not followed by a specific word

- **Problem**

    You may want to match any word that is not immediately followed by the word **cat**.

- **Solution**

    **/\\b\\w+\\b(?!\\W+cat\\b)/i**

- **Discussion**

    If you want to only match words that are followed by **cat** without including **cat**, you can use another regular expression: **/\\b\w+\\b(?=\W+cat\\b)/i**.

### Find any word not preceded by a specific word

- **Problem**

    You may want to match any word that is not immediately preceded by the word **cat**.

- **Solution**

    In JavaScript, lookbehind is not supported and what we can do is just to simulate it:

    ```js
    var subject = 'My cat is fluffy';
    var mainRegex = /\b\w+/g;
    var lookbehind = /\bcat\W+$/i;
    var lookbehindType = false; /** false for negative, true for positive */
    var matches = [];
    var match;
    var leftContext;

    while (match = mainRegex.exec(subject)) {
        leftContext = subject.substring(0, match.index);

        if (lookbehindType === lookbehind.test(leftContext)) {
            matches.push(match[0]);
        } else {
            mainRegex.lastIndex = match.index + 1;
        }
    }

    console.log(matches);   /** => ["My", "cat", "fluffly"] */
    ```

- **Discussion**

    In JavaScript, we may need to use two different patterns to simulate the process of lookbehind. The first pattern inside the lookbehind is **/\\bcat\\W+/**, and the second pattern that  comes after it is **/\\b\\w+/**. If you're using the option `/m` for multiple line, you may prefer to use `$(?!\s)` rather than `$`, so that it can match only at the very end of the subject text.

    The `lookbehindType` variable controls whether we're emulating positive or negative lookbehind, while `true` for positive and `false` for negative.

    Once match, the part of the subject text before the match will be copied into a new string variable named `leftContext`.

    By comparing the result of the lookbehind test to `lookbehindType`, we can determine whether the match meets the complete criteria for a successful match. Then if it's a successful match, then store it with an array. If not, just change the position for a next coming matching.

### Find words near each other

- **Problem**

    How to search two words "word1" and "word2" near each other (less than five other words) with regular expressions?

- **Solution**

    **/\\b(?:word1\\W+(?:\\w+\\W+){0,5}?word2|word2\\W+(?:\\w+\\W+){0,5}?word1)\\b/i**

- **Discussion**

    If you simply want to test whether a list of words can be found anywhere in a subject string, you can use the regular expression: **/^(?=[\\s\\S]&#42;?\\bword1\\b)(?=[\\s\\S]&#42;?\\bword2\\b)[\\s\\S]&#42;/i**.

### Find repeated words

- **Problem**

    You're editing a document and would like to check it for any incorrectly repeated words. You want to find these doubled words despite capitalization differences, such as with "The the". Besides, you may also want to allow different amounts of whitespace between words, even if it causes the words to extend across more than one line.

- **Solution**

    **/\\b([A-Z]+)\\s+\\1\\b/i**

- **Discussion**

    `\s+` matches any whitespace characters, such as spaces, tabs, or line breaks. If you want to restrict them that can separate repeated words to horizontal whitespace without line breaks, replace the `\s` with `[ \t\xA0]`, in which `\xA0` matches a no-break space, a.k.a `&nbsp;`.

### Remove duplicate lines

- **Problem**

    You have a log file, database query output, or some other type of file or string with duplicate lines, and how to remove them?

- **Solution**

    There're three regex-based approaches that can be helpful:

    - **Option 1: sort lines and remove them**

    ```js
    function replaceDuplicate(content) {
        /**
         * sort the content
         * ...
         */

        /** remove with the following regular expression */
        content.replace(/^(.*)(?:(?:\r?\n|\r)\1)+/, '$1');
    }
    ```

    - **Option 2: Keep the last occurrence of each duplicate line in an unsorted file**

    ```js
    function replaceDuplicate(content) {
        /** remove with the following regular expression */
        content.replace(/^(.*)(?:\r?\n|\r)(?=[\s\S]*^\1$)/, '');
    }
    ```

    - **Option 3: Keep the first occurrence of each duplicate line in an unsorted file**

    ```js
    function replaceDuplicate(content) {
        /** remove with the following regular expression */
        content.replace(/^(.*)$([\s\S]*?)(?:(?:\r?\n|\r)\1$)+/, '$1$2');
    }
    ```

### Match complete lines that contain a word

- **Problem**

    You may want to match all lines that contain the word **error** anywhere within them. How?

- **Solution**

    **/^.&#42;\\berror\\b.&#42;$/i**

### Match complete lines that do not contain a word

- **Problem**

    You may want to match complete lines that do not contain the word **error**. How?

- **Solution**

    **/^(?:(?!\\berror\\b).)&#42;$/i**

- **Discussion**

    As you can see, the negative lookahead (`(?!)`) and a dot (`.`) are repeated together using a non-capturing group, which is in order to ensure that the regex `\berror\b` fails at every position in the line.

    > Testing a negative lookahead against every position in a line or string is rather inefficient, and when programming, it's more efficient to search through text line by line.

### Trim leading and trailing (結尾的) whitespace

- **Problem**

    How to remove leading and trailing whitespace from a string?

- **Solution**
    - Trim the leading one

        ```js
        function trimLeadingWhitespace(subject) {
            subject.replace('/^\s+/', '');
        }
        ```

    - Trim the trailing one:

        ```js
        function trimTrialingWhitespace(subject) {
            subject.replace('/\s+$/', '');
        }
        ```

- **Discussion**

    You may consider using `String.prototype.trim()` to complete the job for you, but for older browsers, you may also consider adding a polyfill for such a new method:

    ```js
    if (!String.prototype.trim) {
        String.prototype.trim = function () {
            return this.replace(/^\s+/, '').replace(/\s+$/, '');
        };
    }
    ```

    Certainly, there're also many other ways to trim a string, but the alternatives are usually slower than using two simple regular expression above.

    ```js
    function trim(subject) {
        subject.replace(/^\s+|\s+$/g);
    }
    ```

    ```js
    function trim(subject) {
        subject.replace(/^\s*([\s\S]*?)\s*$/, '$1');
    }
    ```

    ```js
    function trim(subject) {
        subject.replace(/^\s*([\s\S]*\S)?\s*$/, '$1');
    }
    ```

    ```js
    function trim(subject) {
        subject.replace(/^\s*(\S*(?:\s+\S+)*)\s*$/, '$1');
    }
    ```

### Replace repeated whitespace with a single space

- **Problem**

    How to replace all types of whitespaces with a single space, such as any tabs, line breaks or other whitespace.

- **Solution**
    - **Clean any whitespace characters**

    ```js
    function convert(subject) {
        subject.replace(/\s+/, ' ');
    }
    ```

    - **Clean horizontal whitespace characters**

    ```js
    function convert(subject) {
        subject.replace(/ \t\xA0/, ' ');
    }
    ```
