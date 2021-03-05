## Text [Back](./../HTML.md)

### 1. Structural Markup
- **six** levels of heading:  ```<h1>``` to ```<h6>```
- ```<p>``` is used for creating a paragraph.
- ```<b>``` is used for **bold** text.
- ```<i>``` is used for *italic* text.
- ```<sup>``` is used for superscript(上標)
- ```<sub>``` is used for subscript(下標)
- **White Space Collapsing**: It means that when the browser comes across two or more spaces next to each other, it only displays one space. Similarly if it comes across a line break, it treats that as a single space too.
- ```<br />``` is line breaks(**single** one).
- ```<hr />``` is used to create a break(horizonal rules) between themes(**single one).

### 2. Semantic Markup
- ```<strong>``` is used to emphasize something important like using ```<b>```.
- ```<em>``` is used to emphasize that subtly changes the meaning of a sentence like using ```<i>```.
- ```<blockquote>``` is used for longer quotes that take up an entire paragraph.
- ```<q>``` is used for shorter one.
	- ```Some one said, <q>Hello, man!</q>```
- ```<abbr>``` is used for specify some abbreviations or acronyms(縮寫).
	- ```<abbr title = "Professor">Prof</abbr>```
- ```<cite>``` is used for referencing a piece of work such as a **book**, **film** or **research paper**.
	- ```<cite>A Brief History of Time</cite>```
- ```<dfn>``` is used for explaining some new terminology(學術用語).
- ```<address>``` is used to contain **contact details** for the author of the page.
- ```<ins>``` is used for <ins>underline</ins>, ```<del>``` is used for ~~delete~~.
- ```<s>``` indicates something that is no longer accurate or relevant(but that should note be deleted).

```html
<p><s>was $995</s></p>
<p>now only $375</p>
```

<p><s>was $995</s></p>
<p>now only $375</p>

