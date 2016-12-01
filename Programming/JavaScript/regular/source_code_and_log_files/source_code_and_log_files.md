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
