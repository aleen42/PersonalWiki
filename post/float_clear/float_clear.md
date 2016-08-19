## [原創] Something about float and clear in CSS [Back](./../post.md)

### Description

As we all know that, a `div` element is a block element, which will occupy the whole line.

<br />

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/vKrgbZ/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/vKrgbZ/'>vKrgbZ</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

### Float

Normally, We'll suppose that all those `div` elements have been in a normal standard flow (標準流).

CSS have provided an attribute named `float` to allow you to design block elements into a same line. If you set `float` to a `div`, you will find that this element will get rid of the original standard flow, and as following example, you will see that `div2` has get rid of the standard flow, and `div3` has been moved uppper following behind `div1`.

<br/>

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/wWkJwQ/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wWkJwQ/'>wWkJwQ</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br/>

`float` attribute can be set as `left` or `right`, that means you can float this element to the left or right. For example, if we set `float: right;` to `div3`, you will find that this element has been moved to the right side.

<br />

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/oLOkxG/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/oLOkxG/'>oLOkxG</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

Assume that if we set `float: right;` to both `div2` and `div3`, see what happens now? We will found that the order of those elements are from right to left, while left to write for both setting with `float: left;`.

<br />

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/jARBAg/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/jARBAg/'>jARBAg</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

### Clear

`clear` attribute means that a element can clear floated elements in the left or right, or both.

Before adding `clear`, we can see that a `div4`has `div3` floated in the left side, and `div2` floated in the right.

<br />

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/KrYmwN/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/KrYmwN/'>KrYmwN</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

If we set `clear: right;` to `div4`, you'll find that `div4` will follow behind `div2`.

<br />

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/AXzRvb/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/AXzRvb/'>AXzRvb</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

### Summary

For front-end developer, the difficulty of layout is to put different types of elements into one li
