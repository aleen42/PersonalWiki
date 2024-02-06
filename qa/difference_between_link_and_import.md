## Differences between &lt;link&gt; and &#64;import [Back](./qa.md)

`<link>` is a XHTML tag, which can include CSS, as well as define RSS or define rel, while `@import` can only use in CSS to include CSS.

When a page is loading, the CSS included by `<link>` will be loaded **at the same time**, while the CSS included with `@import` should stay **behind the whole page loading completely**.

`@import` is supported upper CSS2.1, and can't be handled under IE5, while `<link>` has no any compatibility problem.

