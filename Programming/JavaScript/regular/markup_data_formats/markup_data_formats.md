## Markup and Data Formats [Back](./../regular.md)

This chapter mainly covers some regular expressions about markup languages and some data formats: HTML, XHTML, XML, CSV, and INI. However some of these formats can be surprisingly complex to process and manipulate accurately, at least using regular expressions.

### Basic rules for formats covered in this chapter

#### Hypertext Markup Language (HTML)

HTML is used to describe the structure, semantics, and appearances of billions of web pages and other documents. In this chapter, we'll only concentrate on the rule needed to process the key components of well-formed HTML: **elements (and the attributes they contain)**, **character references**, **comments**, and **document type declarations**.

#### Extensible Hypertext Markup Language (XHTML)

XHTML is designed as successor (接替者) to HTML 4.01, and migrated HTML from its SGML heritage (遺產) to an XML foundation. However, because development of HTML continued separately, XHTML5 is now being developed as part of the HTML5 specification, and will be the XML serialization of HTML5 rather than introducing new features of its own.

#### Extensible Markup Language (XML)

XML is a general-purpose language designed primarily for sharing structured data. It's used as the foundation to create a wde array of markup languages, including XHTML.

#### Comma-Separated Values (CSV)

CSV is an old but still very common file format used for spreadsheet-like data.

#### Initialization files (INI)

The lightweight INI file format is commonly used for configuration files. It is poorly defined, and as a result, there is plenty of variation in how different programs and systems interpret the format.

### Find XML-style tags

- **Problem**

    You may want to match any HTML, XHTML, or XML tags in a string, how?

- **Solution**
    - Quick and dirty:

        **/<[&#94;>]&#42;>/**

    - Allow `>` in attribute values:

        **/<(?:[&#94;>"']|"[&#94;"]&#42;"|'[&#94;']&#42;')&#42;>/**

    - (X)HTML tags (loose):

        **/<\\/?([A-Za-z][&#94;\\s>\\/]&#42;)(?:=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;\\s>]+)|[&#94;>])&#42;(?:>|$)/**

    - (X)HTML tags (strict):

        **/<(?:([A-Z][-:A-Z0-9]&#42;)(?:\s+[A-Z][-:A-Z0-9]&#42;(?:\s&#42;=\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'|[&#94;"'`=<>\s]+))?)&#42;\s&#42;\\/?|\\/([A-Z][-:A-Z0-9]&#42;)\s&#42;)>/**

    - XML tags (strict):

        **/<(?:([_:A-Z][-.:\\w]&#42;)(?:\\s+[_:A-Z][-.:\\w]&#42;\\s&#42;=\\s&#42;(?:"[&#94;"]&#42;"|'[&#94;']&#42;'))&#42;\\s&#42;\\/?|\\/([_:A-Z][-.:\\w]&#42;)\\s&#42;)>/**
