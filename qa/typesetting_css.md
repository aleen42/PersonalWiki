## Something about typesetting in CSS [Back](./qa.md)

In the case when we need to present some text in a site, typesetting is a problem we may need when coding with CSS. In general, all the following attributes can affect the position of text, like `white-space`, `work-break`, or `word-wrap`, etc. This article mainly aims to figure out how they work, and how to set them in some situations.

### 1. Letter Spacing

The attribute `letter-spacing` is used to set the distance between each character in a string. It applies to the element itself, and also pseudo elements like `::first-line` and  `::first-letter`. Its initial value is `normal`, which means that there is no distance between each character.

```css
letter-spacing: normal;

letter-spacing: 0.3em;
letter-spacing: 3px;
letter-spacing: .3px;

letter-spacing: inherit;
```

### 2. Keeping in Line

When a container has too much texts, resulting in multiple lines to present such contents, we can use a attribute named `white-space` to decide whether to keep it in a single line. If keep it, then set it with `nowrap`:

```css
white-space: normal
white-space: nowrap
white-space: pre
white-space: pre-wrap
white-space: pre-line

white-space: inherit
```

- `normal` means that a series of white spaces will be merged into one, including the line-break character. At the same time, break contents into another line automatically if necessary.
- `nowrap` means to merge white spaces but not to break into another line.
- `pre` means that keep a series of white spaces and break into anther line if there is a line-break character or a `<br>` element.
- `pre-wrap` means that keep white spaces and break into another line in three cases: a line-break character, a `<br>` element, or necessary to break
- `pre-line` means to merge white spaces, and break into another line in three cases as the same as the previous one.

In order to enhance it, there is a table to show the differences between those values:

&nbsp;|Line-break characters|White Spaces|Breaking into new lines automatically
:-:|:-----------------|:-----------|:----------------------
`normal`|merged|merged|yes
`nowrap`|merged|merged|no
`pre`|keeped|keeped|no
`pre-wrap`|keeped|keeped|yes
`pre-line`|keeped|merged|yes

### 3. Word Wrapping

Word wrapping means whether to break a word into another line when this word is too long to fill in the container. If we want to break, we can set the attribute `word-wrap` or `overflow-wrap` with `break-word`. `word-wrap` is the original private attribute of Microsoft, and it has been renamed as `overflow-wrap` in CSS3.

Another attribute named `word-break` is used to specify how to break this word if it is too long to fill in. If we set it with `break-all`, the browser is allowed to break any character of CJK (Chinese/Japanese/Korean) contents into a new line. And if we set it with `kee-all`, the browser is not allowed to break any character of CJK contents.

<p>
<p data-height="694" data-theme-id="21735" data-slug-hash="mmBRZZ" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Word Breaking" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/mmBRZZ/">Word Breaking</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>
