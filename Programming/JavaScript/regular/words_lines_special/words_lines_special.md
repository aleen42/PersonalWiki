## Words, Lines, and Special Characters [Back](./../regular.md)

This chapter is mainly showing a variety of regular expression constructs and techniques in action, which may be helpful for you to solve specific problems you're facing.

### Find a specific word

- **Problem**

    Find all occurrences of the word **cat**, case insensitively, and do not match any longest words such as **hellcat**, **application**, or **Catwoman**.

- **Solution**

    **/\\bcat\\b/i**

- **Discussion**

    A problem can occur when working with international text in JavaScript, since this kind of regular expression flavors only consiers letters in the ASCII table to create a word boundary. In other words, word boundaries are found only at the positions between a match of **/[^A-Za-z0-9]|^/** and **/[A-Za-z0-9_]/**, or between **/[A-Za-z0-9_]/** and **/[^A-Za-z0-9_]|$/**. It means that `\b` is not helpful when searching within text that contains accented (異國的) letters or words that use non-Latin scripts.

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
