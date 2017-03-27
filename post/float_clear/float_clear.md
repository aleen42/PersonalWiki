## [原創] Something about float and clear in CSS [Back](./../post.md)

### Description

As we all know that, a `div` element is a block element, which will occupy the whole line.

<p>
<p data-height="672" data-theme-id="21735" data-slug-hash="vKrgbZ" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="vKrgbZ" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/vKrgbZ/">vKrgbZ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Float

Normally, We'll suppose that all those `div` elements have been in a normal standard flow (標準流).

CSS have provided an attribute named `float` to allow you to design block elements into a same line. If you set `float` to a `div`, you will find that this element will get rid of the original standard flow, and as following example, you will see that `div2` has get rid of the standard flow, and `div3` has been moved uppper following behind `div1`.

<p>
<p data-height="585" data-theme-id="21735" data-slug-hash="wWkJwQ" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="wWkJwQ" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/wWkJwQ/">wWkJwQ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

`float` attribute can be set as `left` or `right`, that means you can float this element to the left or right. For example, if we set `float: right;` to `div3`, you will find that this element has been moved to the right side.

<p>
<p data-height="421" data-theme-id="21735" data-slug-hash="oLOkxG" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="oLOkxG" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/oLOkxG/">oLOkxG</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

Assume that if we set `float: right;` to both `div2` and `div3`, see what happens now? We will found that the order of those elements are from right to left, while left to write for both setting with `float: left;`.

<p>
<p data-height="421" data-theme-id="21735" data-slug-hash="jARBAg" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="jARBAg" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/jARBAg/">jARBAg</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Clear

`clear` attribute means that a element can clear floated elements in the left or right, or both.

Before adding `clear`, we can see that a `div4`has `div3` floated in the left side, and `div2` floated in the right.

<p>
<p data-height="427" data-theme-id="21735" data-slug-hash="KrYmwN" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="KrYmwN" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/KrYmwN/">KrYmwN</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

If we set `clear: right;` to `div4`, you'll find that `div4` will follow behind `div2`.

<p>
<p data-height="439" data-theme-id="21735" data-slug-hash="AXzRvb" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="AXzRvb" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/AXzRvb/">AXzRvb</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Self-clear

When we have set float elements in a container, the container will not automatically responsive to these elements. To make the container self-clear, even in an older version of browser, we may have to clear fix for them:

```css
.clearfix:after {
    display: block;
    content: " ";
    clear: both;
    /** try to hide this additional element */
    visibility: hidden;
    height: 0;
    font-size: 0;
}

* html .clearfix {
    /** IE7 */
    zoom: 1;
}

*:first-child + html .clearfix {
    /** IE6 */
    zoom: 1;
}
```

### Summary

For front-end developer, the difficulty of layout is to put different types of elements into one line. Both `float` and `clear` have provided you a way to handle it.
