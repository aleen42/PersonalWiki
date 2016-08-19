## [原創] Something about float and clear in CSS [Back](./../post.md)

### Description

As we all know that, a `div` element is a block element, which will occupy the whole line.

<p data-height="498" data-theme-id="21735" data-slug-hash="vKrgbZ" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/vKrgbZ/">vKrgbZ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>

### Float

Normally, We'll suppose that all those `div` elements have been in a normal standard flow (標準流).

CSS have provided an attribute named `float` to allow you to design block elements into a same line. If you set `float` to a `div`, you will find that this element will get rid of the original standard flow, and as following example, you will see that `div2` has get rid of the standard flow, and `div3` has been moved uppper following behind `div1`.

<br/>

<p data-height="493" data-theme-id="21735" data-slug-hash="wWkJwQ" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/wWkJwQ/">wWkJwQ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>

<iframe height='409' scrolling='no' src='//codepen.io/aleen42/embed/wWkJwQ/?height=409&theme-id=21735&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wWkJwQ/'>wWkJwQ</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br/>

`float` attribute can be set as `left` or `right`, that means you can float this element to the left or right. For example, if we set `float: right;` to `div3`, you will find that this element has been moved to the right side.

<br />

<p data-height="403" data-theme-id="21735" data-slug-hash="oLOkxG" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/oLOkxG/">oLOkxG</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>

<br />

Assume that if we set `float: right;` to both `div2` and `div3`, see what happens now? We will found that the order of those elements are from right to left, while left to write for both setting with `float: left;`.

<br />

<p data-height="409" data-theme-id="21735" data-slug-hash="jARBAg" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/jARBAg/">jARBAg</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>

<br />