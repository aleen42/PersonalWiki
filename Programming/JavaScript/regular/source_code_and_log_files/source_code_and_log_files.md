## Source Code and Log Files [Back](./../regular.md)

Regular expressions are an excellent solution for tokenizing input while constructing a parser for a custom file format or scripting languages. This chapter mainly discuss some recipes for matching syntactic elements that are commonly used in programming languages and other text-based file formats.

In addition, the chapter will also show you how to extract information from log files.

### Keywords

- **Problem**

    Extract some reserved keywords such as "**end**", "**in**", "**inline**", "**inherited**", "**item**", and "**object**".

- **Solution**

    **/\\b(?:end|in|inline|inherited|item|object)\\b/i**

- **Discussion**

    There is another way when making our regex match both keywords and strings by using: **/\\b(end|in|inline|inherited|item|object)\\b|'[&#94;'\\r\\n]&#42;(?:''[&#94;'\\r\\n]&#42;)&#42;'/i**.

### Identifiers

- **Problem**

    How to use a regular expression to match any identifier in a source code?

- **Solution**

    **/\\b[a-z_][0-9a-z_]{0,31}\\b/i**

### Operators

- **Problem**

    You may need a regular expression that matches any of characters that can be used as operators in the programming language.

- **Solution**

    **/[+-&#42;\\/=<>$&^|!~?/]/**

### Single-line comments

- **Problem**

    You may want to match a comment that starts with **//** and runs until the end of the line.

- **Solution**

    **/\\/\\/.&#42;/**

### Multiline comments

- **Problem**

    What if comments you want to match is a multiline comment which starts with **/&#42;** and ends with **&#42;/**?

- **Solution**

    **/\\/\\&#42;[\\s\\S]&#42;?\\&#42;\\//**

### All comments

- **Problem**

    Combine both single-line and multiline comments.

- **Solution**

    **/\\/\\/.&#42;|\\/\\&#42;[\\s\\S]&#42;?\\&#42;\\//**

### Strings

- **Problem**

    Match string literal wrapped with **""** or **''**.

- **Solution**

    **/"[&#94;"\\r\\n]&#42;(?:""[&#94;"\\r\\n]&#42;)&#42;"|'[&#94;'\\r\\n]&#42;(?:''[&#94;'\\r\\n]&#42;)&#42;'/**

- **Discussion**

    If strings can include line breaks, simply remove them from the negated character classes: **/"[&#94;"]&#42;(?:""[&#94;"]&#42;)&#42;"|'[&#94;']&#42;(?:''[&#94;'']&#42;)&#42;'/**.
