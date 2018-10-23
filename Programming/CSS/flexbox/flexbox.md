## Flexbox [Back](../CSS.md)

### 1. Basic Introduction

Before the Flexbox layout module, there were four layout modules:

- **Block**: for sections in a site
- **Inline**: for text
- **Table**: for two-dimensional table data
- **Positioned**: for explicit position of an element

With Flexbox layout module, we can easily define responsive layout without using `float` or `position`. However, since it was released by CSS3, it can only be used under IE11+.

In order to use such a flexible layout module, we should put elements into a flex container, which can be defined with `display: flex`:

<p>
<p data-height="316" data-theme-id="21735" data-slug-hash="oaPWrK" data-default-tab="css,result" data-user="aleen42" data-pen-title="oaPWrK" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/oaPWrK/">oaPWrK</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

As the article "[Display Module Level 3](https://www.w3.org/TR/css-display-3/)" mentioned, each value of `display` is actually described as a combination of two things: **an outer display model** and **an inner display model**. When we define a container with `display: flex`，it is actually defined as `display: block flex`, which means that the container will act like a block element while the inner elements are flexible.

Certainly, since we can defined as `flex`, we can also define the container with a value of `inline-flex`, so that the container can act like an inline element.

<p>
<p data-height="316" data-theme-id="21735" data-slug-hash="MPqowB" data-default-tab="css,result" data-user="aleen42" data-pen-title="MPqowB" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/MPqowB/">MPqowB</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

### 2. Direction

The direction of a defined flexible container can be specified with a CSS property, named `flex-direction`, which has the value of `row` by default. Other values for this property are:

- `column`
- `row-reverse`
- `column-reverse`

<p>
<p data-height="260" data-theme-id="21735" data-slug-hash="yRxXeE" data-default-tab="result" data-user="aleen42" data-pen-title="yRxXeE" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/yRxXeE/">yRxXeE</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Certainly, there are two axes of Flexbox: main axis and the cross axis. While using `flex-direction` to define the direction of a flexible container, what actually we specify is the main axis of this container. When we set the main axis along the row, with `row` value, the cross axis is down the columns, while we set the main axis down the column, the cross axis is along the row in fact.

When it comes to the order of a flexible container along the row, it depends on the writing mode of the system language. For instance, if we are working in a right-to-left language such as Arabic, like defined `direction: rtl`, the order should be from right towards left:

<p>
<p data-height="250" data-theme-id="21735" data-slug-hash="JmaJxX" data-default-tab="result" data-user="aleen42" data-pen-title="JmaJxX" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/JmaJxX/">JmaJxX</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Similarly, if we have defined the `writing-mode` property of the flexible container with the value `vertical-lr`, we should get a vertical column visualization even we set the container with `row`.

<p>
<p data-height="394" data-theme-id="21735" data-slug-hash="dgqREv" data-default-tab="result" data-user="aleen42" data-pen-title="dgqREv" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/dgqREv/">dgqREv</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Understanding the fact that a row or a column can run in different physical directions is helpful in understanding some of the terminology being used for Grid and Flexbox.

### 3. Alignment

As explained in [the Flexbox specification](https://www.w3.org/TR/css-flexbox-1/#alignment), any specification of the Box alignment will ultimately replace the alignment specification in the Flexbox.

#### 3.1 Main Axis Alignment

When it comes tom the alignment of the main axis, any CSS alignment property which begins with `justify-` prefix, like `justify-content`, then it should applies to the main axis of the flexible container. The initial value of `justify-content` for a flexible container is `flex-start`, and other values can be:

- `flex-end`
- `center`
- `space-around`
- `space-between`
- `space-evenly` (added in Box alignment)

<p>
<p data-height="376" data-theme-id="21735" data-slug-hash="Edevyy" data-default-tab="result" data-user="aleen42" data-pen-title="Edevyy" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/Edevyy/">Edevyy</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

*Note: `justify-content` can only affect **if there is spare space to distribute**.*

#### 3.2 Cross Axis Alignment

`align-items` CSS property is mainly used to defined the alignment of the cross axis of a flexible container, which is `stretch` by default. It means that the item will be stretched to fit the flexible container. Other values can be:

- `flex-start`
- `flex-end`
- `center`
- `baseline`

<p>
<p data-height="564" data-theme-id="21735" data-slug-hash="XxPazj" data-default-tab="css,result" data-user="aleen42" data-pen-title="XxPazj" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/XxPazj/">XxPazj</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Besides, we can also use `align-self` property to specify alignments for specific item in the flexible container, which has the same value of `align-items`.

*Note: why is there no `justify-self`? CSS Flexbox module only want to focus more on spare space distribution of a group of items, but not a specific one.*

#### 3.3 Multiple-line Alignment

When a flexible container have too many elements resulting in layouts with multiple lines, `align-content` property can help us specifying the alignment of each line.

Its default value is `stretch`, and other values can be:

- `flex-start`
- `flex-end`
- `center`
- `space-around`
- `space-between`
- `space-evenly` (added in Box alignment)

<p>
<p data-height="811" data-theme-id="21735" data-slug-hash="YJOYBj" data-default-tab="css,result" data-user="aleen42" data-pen-title="YJOYBj" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/YJOYBj/">YJOYBj</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

#### 3.4 Shorthand

In the Box alignment, there is a shorthand property `place-content`, which we can specify `justify-content` and `align-content` at once.

```css
.container {
    display: flex;
    place-content: stretch flex-start; /** <align-content> <justify-content> */  
}
```

The snippet above is same as:

```css
.container {
    display: flex;
    align-content: stretch;
    justify-content: flex-start;  
}
```

If we want to set both properties with the same value `flex-start`, the shorthand can be more simple like this:

```css
.container {
    display: flex;
    place-content: flex-start;
}
```

#### 3.5 Auto Margins

As we known that if a block has been centered in CSS, the margin set with `auto` will try to become as big as it can in the direction it has been set in. Auto margins works nicely in Flexbox to align items or groups of items on the main axis.

For the following snippet, the third item which has been set with `margin-left: auto`. It means that the item will try to get as much space as possible from the left side, which also means that the item will be aligned to the right.

<p>
<p data-height="184" data-theme-id="21735" data-slug-hash="VEGXLY" data-default-tab="css,result" data-user="aleen42" data-pen-title="VEGXLY" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/VEGXLY/">VEGXLY</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

#### 3.6 Fallback Alignment

What if I style a flexible container with `justify-content: space-between`, but there is only one element in that container? CSS has a fallback alignment of `flex-start` for such a situation, which means that it is same as `justify-content: flex-start`. In the case of `justify-content: space-around`, a fallback alignment of `center` is used.

### 4. Flexible Items

Finally, there are some CSS properties use to describe items in a flexible container, like `flex-grow`, `flex-shrink`, and `flex-basis`. While the `flex` property is a shorthand property for these three all.

*Note: the `flex` property has a default value as `0 1 auto`, and here we want to know what they really describe.*

Firstly, `flex-grow` means that the item in the flexible container will try to take up any available space in the container when it s set with a positive value. In addition, different positive value can be specified as the ratio of spaces which have been taken up.

<p>
<p data-height="230" data-theme-id="21735" data-slug-hash="JmayeO" data-default-tab="html,result" data-user="aleen42" data-pen-title="JmayeO" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/JmayeO/">JmayeO</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Secondly, `flex-shrink` means that the item will try to shrink itself before overflow the flexible container when it is specified with a positive value. This is a sensitive property when the `flex-basis` property is set with specified value, but not `auto`

<p>
<p data-height="278" data-theme-id="21735" data-slug-hash="gBdxVy" data-default-tab="css,result" data-user="aleen42" data-pen-title="gBdxVy" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/gBdxVy/">gBdxVy</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

Before knowing what `auto` means for `flex-basis`, you may need to know that the CSS Working Groups spend a lot of time figuring out what `auto` means in any context, as [this talk of spec editor Fantasai explains](https://vimeo.com/134597090).

When it comes to what `auto` means when used as a `flex-basis`, the term defined followed should help us know:

> "When specified on a flex item, the auto keyword retrieves the value of the main size property as the used `flex-basis`. If that value is itself auto, then the used value is `content`."

Taking the former part of the sentence above as a thinking, if our `flex-basis` is `auto`, Flexbox has a look at the defined main size property.

<p>
<p data-height="198" data-theme-id="21735" data-slug-hash="mzGBOZ" data-default-tab="result" data-user="aleen42" data-pen-title="mzGBOZ" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/mzGBOZ/">mzGBOZ</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>
</p>

In the example above, the main size property is itself auto, so the Flexbox actually has `content` as the value of the `flex-basis` property.

So what the spec says about the `content` keyword?

> "Indicates an automatic size based on the flex i tem's content. (It is typically equivalent to the max-content size, but with adjustments to handle aspect ratios, intrinsic sizing constraints, and orthogonal flows"

*Note: this value can only be supported under specific browsers, and please check [the compatibility tables](https://developer.mozilla.org/en-US/docs/Web/CSS/flex-basis#Browser_compatibility).*

When there are more items in the flexible container, resulting overflow, the item will break out of the flex container, as `flex-wrap`, another property has `nowrap` as its default value.

<p data-height="324" data-theme-id="21735" data-slug-hash="ReYBaa" data-default-tab="result" data-user="aleen42" data-pen-title="ReYBaa" class="codepen">See the Pen <a href="https://codepen.io/aleen42/pen/ReYBaa/">ReYBaa</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>) on <a href="https://codepen.io">CodePen</a>.</p>
<script async src="https://static.codepen.io/assets/embed/ei.js"></script>

### 5. References

1. "[What Happens When You Create A Flexbox Flex Container?](https://www.smashingmagazine.com/2018/08/flexbox-display-flex-container/)", Rachel Andrew, Smashing Magazine.
2. "[Everything You Need To Know About Alignment In Flexbox](https://www.smashingmagazine.com/2018/08/flexbox-alignment/)", Rachel Andrew, Smashing Magazine.
3. "[Flexbox: How Big Is That Flexible Box?](https://www.smashingmagazine.com/2018/09/flexbox-sizing-flexible-box/)", Rachel Andrew, Smashing Magazine.
