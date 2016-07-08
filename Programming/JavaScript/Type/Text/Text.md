## Text [Back](./../Type.md)
### Overview

- a **string** is an immutable value with 16 ordered bits, each of which represents a **Unicode** character.
- the **length** of a string is the number of 16-bit values it contains.
- some Unicode characters whose codepoints do not fit in 16 bits are encoded following the rules of **UTF-16** as a sequence of two 16-bit values.

```js
var p = "π";	//π is 1 character with 16-bit codepoint 0x03c0
var e = "e"	//e is 1 character with 17-bit codepoint 0x1d452
p.length	// => 1
e.length 	// => 2
```
- we can use `\n` to include a newline character, `\` to break a string literal across multiple lines.

```js
"two\nlines"	//there are 2 lines
"one\		//there is only 1 line.
line\		
only"
```
- when combining JavaScript and HTML, it is a good idea to use one style of quotes for JavaScript, and the other style of HTML.

`<button onclick="alert('Aloha')">Click me</button>`

### Escape Sequence(轉義字符)
Sequence|Character represented
:--:|---
\0|The NUL character(\u0000)
\b|Backspace(\u0008)
\t|Horizontal Tab(\u0009)
\v|Vertical Tab(\u000B)
\n|Newline(\u000A)
\"|Double quote(\u0022)
\'|Apostrophe(單引號) or single quote(\u0027)
\\|Backslash(反斜杠)(\u005c)

### Pattern Matching
- create objects that reptresent textual patterns with `RegExp()`.

```js
var text = "testing: 1, 2, 3";
var pattern = /\d+/g
pattern.test(text)	// => true
text.search(pattern)	// => 9: position of first match
text.match(pattern)	// => [ "1", "2", "3"]: array of all matches
text.replace(pattern, "#")	// => "testing: #, #, #"
text.split(/\D+/);	// => [ "", "1", "2", "3"]: split on non-digits
```
