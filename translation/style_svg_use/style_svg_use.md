## Styling SVG &lt;use&gt; Content with CSS - 使用 CSS 来制定 SVG 中 &lt;use&gt; 标签内容的样式 [**Back**](./../translation.md)

> * 原文链接 : [Styling SVG &lt;use&gt; Content with CSS](http://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/)
* 原文作者 : [Sara Soueidan](https://github.com/SaraSoueidan)
* 译者 : [aleen42](https://github.com/aleen42)
* 校对者 : 暂无
* 状态 : 翻译中

![](./StylingSVGuse.jpg)

图标体系（icon system）是 SVG 图形其中一个最为常用的例子。除此之外，使用 [SVG 元素来“实例化”文档中任何所需实例化的图标](https://css-tricks.com/svg-sprites-use-better-icon-fonts/)，也是 SVG 所常用的 Sprite 技术其其中的一种用法。

由于使用 `<use>` 元素所实例的图标或任何其他 SVG 元素或图像，在制定元素实例的样式时总会遇到部分的问题。因此，书写本文的目的在于为你提供部分可行的方法来突破 `<use>` 元素所带来的局限。

然而，在开始之前，我们来一起快速审视一下 SVG 的主要结构以及用于编组的元素。然后，逐渐地去深入了解 `use` 元素，即其影子 DOM。最后，我们才回到如何使用 CSS 去指定样式的话题上。除此之外，本文还会带你仔细地查看制定过程中所遇到的种种问题及其解决办法。

### 关于 SVG 结构化、编组以及引用（重用）元素的概述

在 SVG 中主要有四种元素用于文档中 SVG 节点的定义、结构化和引用。它们使重用变得更为简单的同时，保持了代码的整洁性及可阅性。由于 SVG 的特性（nature），部分元素与图形编辑器中的一些命令都提供有相似的功能。

这四种用于编组及引用的主要元素分别是：`<g>`、`<defs>`、`<use>` 和 `<symbol>`.

`<g>` 元素（简称“编组（group）”）是用于逻辑上归类相关图形元素的集合。对应于像 Adobe Illustrator 这样的图形编辑器，`<g>` 元素所提供的服务类似于“编组对象（Group Objects）”的功能。此外，由于在 AI 中，一个图层就是一组的元素。因此，你也可以把编组理解成图层的概念

把元素编在一组当中，有利于把样式制定于组中的所有元素，尤其当你想为组中的元素制定动画，而同时保持之间的空间关系时，尤为有效。

`<defs>` 元素是用于*定义*未来希望被重用的元素。其有助于你创建“模板（template）”并在文档中使用多遍。值得注意的是，定义在 `<defs>` 中的元素并不会被渲染于画布上。除非，你在文档的某处“召唤”了它。

虽然，`<defs>` 可用于定义大量的元素，但是，其最主要的用途之一是去定义像斜率这样的范式（pattern）。举个例子，该范式可被引用到其他 SVG 元素的笔画及填充当中。除此之外，该范式还能被运用到画布上任何需要渲染的引用元素其定义当中。

`<symbol>` 元素集 `<defs>` 和 `<g>` 两者之大成。不仅能定义文档中随处可被引用的模板，还能将这些模板编组在一起。与 `<defs>` 不同的是，`<symbol>` 并不常用于定义范式。其主要用途在于定义像图标这样的符号，且可在文档中被引用。

与前两者相比，`<symbol>` 元素有着一个重要的优势：它可接受一个 `viewBox` 属性，使得所引用的元素可缩放以适合视窗（viewport）的大小。

`<use>` 元素则是用于引用文档中任何已经被定义的元素。它使得你可以重用任何已存在的元素，并让你可以像在图形编辑器中复制粘贴某个元素。也就是说，它可以用于重用一个单一元素或一组由 `<g>`、`<defs>` 或 `<symbol>` 所定义的元素。

为了重用某特定元素，你需要把元素的 ID 传至 `use` 的 `xlink:href` 属性当中，并通过 `x` 和 `y` 属性来放置。除此之外，你也可以把样式应用于该 `use` 元素中。而该样式同时会被应用于 `use` 元素中的内容。

可 `use` 元素中的内容到底是指什么呢？这些内容被克隆到哪里？以及 CSS 是如何把样式应用到这些内容上？

在我们回答这些问题之前，这里有一些文章值得我们先去阅读一下。通过阅读，我们可以对上述元素有着更为充分的了解，以及关于 `<symbol>` 元素中所使用到的 `viewBox` 属性：

- [SVG 中的结构化、编组和引用 —— `<g>`、`<use>`、`<defs>` 和 `<symbol>` 元素](http://sarasoueidan.com/blog/structuring-grouping-referencing-in-svg/)
- [了解 SVG 的坐标系（第一部分）： 视窗、`viewBox` 属性和 `PreserveAspectRatio` 属性](http://sarasoueidan.com/blog/svg-coordinate-systems)

### SVG 中的 &lt;use&gt; 元素及影子 DOM（The Shadow DOM）

当你使用 `<use>` 来引用一个元素时，代码可能会看起来像这样：

```html
<symbol id="my-icon" viewBox="0 0 30 30">
    <!-- icon content / shapes here -->
</symbol>

<use xlink:href="#my-icon" x="100" y="300" />
```

在屏幕中所渲染的是一个图标。虽然，它的内容被定义在 `<symbol>` 里面，但所渲染的并非*该*内容，而是 `<use>` 元素中的一份拷贝内容。

可我们只看到一个自闭元素 —— 其开闭标记内并没有任何的相关内容，那么，从 `<symbol>` 所拷贝出来的内容在哪里呢？

答案是：**影子 DOM**。（有时，我也不知道为什么影子 DOM 总会让我想起蝙蝠侠。)

#### 影子 DOM 为何物？

影子 DOM 大体与普通的 DOM 相似。不同处在于，普通的 DOM 是作为主文档子树（the main document subtree）中的一部分所存在，而影子 DOM 中的节点则是属于特定的一个*“文档片段（document fragment）”*。该片段大体上就是另一棵用于存放节点的子树。只不过，该子树下的节点并不能像普通的节点一样，轻易被脚本和样式所访问。这就为编程人员在创建模块化组件时，封装和指定脚本及样式的作用域提供了一种方法。若您曾经使用过 HTML5 的 `video` 元素或范围型 `input` 元素如 `input[type="number"]`，那么你应该会想视频的控制区或范围的选取组件到底是来自哪里？然后，你也许就会交叉地接触到影子 DOM。

在 `<use>` 元素这种情况中，所引用的元素其内容就是被克隆至一段文档片段当中，而该片段的“主人”就是相关的 `<use>` 元素。所以，`<use>` 元素有时亦被称作为一名*影子主人（Shadow Host）*。

所以至此，我们知道 `<use>` 的内容（包括所引用元素的任何克隆或拷贝）是被展现于一个影子的文档片段当中。

换句话说，他们是在*彼处*，可却无法被看见。宛如普通 DOM 的内容，而又无法被主文档中“高级”的 DOM，以 CSS 选择器及 JavaScript 的方式所触及。这是因为，它们被拷贝到了一份独立的文档片段当中，而该片段的主人就是 `<use>` 元素。

如今，若您是一位设计师，那么你也许会想：“好的，我清楚这点。但是否有一种方式可以去审查该子文档，并真正地*看到*它们的内容呢？”答案是：可以的！你可以通过使用 Chrome 浏览器的开发工具去预览影子 DOM 的内容。但是，你需要先在审查工具的设置面板中的“（一般）General” 选项中允许影子 DOM 的审查。（可通过点击齿轮图标）在此，若找不到选项，可查一下如何去允许。（Firefox 浏览器暂未支持）

一旦你在开发工具中允许了影子 DOM 的审查，你就可以像审查普通 DOM 元素一样，在元素面板中看到所克隆的元素。以下图片所展示的就是 `<use>` 元素引用 `<symbol>` 元素内容的一个例子。需要注意的是，“#shadow-root” 所展开的片段内容就是 `<symbol>` 元素的一份拷贝。

> ![](./shadow-dom.jpg)

> 通过使用 Chrome 的开发者工具，你可以审查到影子 DOM 中的 &lt;use&gt; 元素（请查看一下灰色字的“#shadow-root”）。该截图中所审查的 Codrops 商标就是来自我们下一节的一个例子。

看一下审查的代码，我们可以发现影子 DOM 与普通的 DOM 太过于相似，而其不同只存在于处理从主文档所引用的 CSS 和 JavaScript 文件时，所呈现的不同特征。当然，它们两者之前还有其他的不同之处，但在此处我们并不能涵盖到每一点。这是因为，影子 DOM 实在是一个太大的概念。而如果你想阅读并学习更多的相关知识，我可以推荐您阅读一下这些文章：

- [谈影子 DOM ](http://code.tutsplus.com/tutorials/intro-to-shadow-dom--net-34966)
- [影子 DOM 到底是何方神圣？](http://glazkov.com/2011/01/14/what-the-heck-is-shadow-dom/)
- [影子 DOM 101](http://www.html5rocks.com/en/tutorials/webcomponents/shadowdom/)
- [关于影子 DOM 的介绍（视频）](http://webcomponents.org/articles/introduction-to-shadow-dom/)

For me, and considering how limited my interaction with the shadow DOM is, I think of it as being just like the normal DOM, except that it needs to be handled differently when it comes to accessing its elements for styling with CSS (and JavaScript). This is what matters to us as SVG developers: how the existence of the contents of `<use>` inside a shadow DOM affects that content when it comes to applying or changing styles, because we want to be able to style them. The whole point of using `<use>` is being able to create different "copies" of an element, and in a lot of cases, what we want is to be able to style each copy differently. For example, think about a logo with two styles (inverted color themes) or multi-coloured icons of which each has its own theme. So, it would only make sense for us to expect to be able to do that using CSS.
That being said, we mentioned earlier that the contents of the shadow DOM are not vulnerable to CSS like the normal DOM is. So how *do* we style its content? We cannot target a path descendant of `<use>` like this:

```css
use path#line {
    stroke: #009966;
}
```

because we cannot access the shadow DOM using regular CSS selectors.

There are a couple of special selectors that allow you to penetrate the shadow DOM boundaries to apply styles to nodes inside of it, but those selectors are not only not well supported, but they are limited compared to the long list of selectors provided in CSS for selecting and styling regular DOM elements.

Moreover, we want a simpler way to style the contents of an SVG `<use>` without having to get our hands dirty with shadow DOM specifics—using simple CSS and SVG only.

In order to achieve that and get a little more control over styling the contents of `<use>`, we need to think from a different angle, and start by leveraging the CSS cascade and taking advantage of its inheritance capabilities.

### The Style Cascade

Since SVG elements can be styled using CSS using one of three different ways: external CSS styles (in an external style sheet), internal style blocks (`<style>` elements) and inline styles (in a `style` attribute), it only makes sense that the cascade governs how these styles are applied to these elements.

In addition to CSS properties, SVG elements can also be styled using *presentation attributes*. Presentation attributes are a shorthand for setting a CSS property on an element. Think of them as special style properties. Their nature is what makes them contribute to the style cascade, but maybe in a less expected way.

In the following code snippet which simply displays a pink circle with a yellow stroke, `stroke`, `stroke-width`, and `fill` are all presentation attributes.

```html
<svg viewBox="0 0 100 100">
    <circle fill="deepPink" stroke="yellow" stroke-width="5" cx="50" cy="50" r="10"></circle>
</svg>
```

In SVG, a subset of all CSS properties may be set by SVG attributes, and vice versa. This means that not all CSS properties can be specified on an SVG element as presentation attributes, and not all presentation attributes available in SVG (there are *a lot* of them!) can be specified in CSS.

The SVG specification lists the SVG attributes that may be set as CSS properties. Some of these attributes are shared with CSS (already available as CSS properties), such as `opacity` and `transform`, among others, while some are not, such as `fill`, `stroke` and `stroke-width`, among others.

In SVG 2, this list will include `x`, `y`, `width`, `height`, `cx`, `cy` and a few other presentation attributes that were not possible to set via CSS in SVG 1.1. The new list of attributes can be found in the SVG 2 specification.

If you're like me, then you would expect presentation attributes to have a higher specificity than all other style declarations. I mean, after all, external styles are overridden by internal styles in style blocks, and style block declarations are overridden by inline styles in a style attribute.. so it seems as though the more "internal" the styles get, the more specificity they have, and so when a property gets its own attribute, it makes it more powerful and thus it would override all other style declarations. Although that *still* makes sense to me, this is not how it really works.

As a matter of fact, presentation attributes count as low-level "author style sheets" and are overridden by any other style definitions: external style sheets, document style sheets and inline styles. The only power presentation attributes have in the style cascade is over inherited styles. That is, presentation attributes can only override inherited styles on an element, and are overridden by any other style declaration.

Great, now that that's been cleared up, let's get back to the `<use>` element and its content.

We now know that we cannot set styles on the elements inside `<use>` using CSS selectors.

We also know that, just like with the `<g>` element, styles you apply to `<use>` will be inherited by all its descendants (those in the shadow DOM).

So a first attempt to change the `fill` color of an element inside `<use>` would be to apply that fill color to the `<use>` element itself and let inheritance and the cascade do its thing.

However, that brings up two issues:

1. The fill color will be inherited by *all* the descendants of `<use>`, even those you may not want to style. (If you have only one element inside `<use>`, then this won't be an issue.)
2. If you've exported an SVG from a graphics editor and/or got an SVG from a designer who did that and for any reason you can't touch the SVG code, then you're likely to end up with SVG elements with presentation attributes applied (unless you explicitly specified that you don't want this to happen upon exporting the SVG, but that's another topic), and the values of these attributes are going to override any styles you apply on `<use>`. Now, I'm assuming that if you are specifying styles on `<use>` then you *want* those styles to be inherited by its descendants, so presentation attributes would be causing an inconvenience in this case.

And even if you *do* have access to the SVG code and you *can* get rid of the presentation attributes, **I highly recommend against that** because:

1. Removing the attributes used to set certain properties will reset those properties to their initial browser-default values—which, in most cases, is all black fills and strokes (if we're talking about colors, for example).
2. By resetting all values you force yourself into specifying styles for all the properties set, so unless you want to do just that, then you don't want to get rid of those presentation attributes.
3. The presentation attributes that are initially available are a great fallback mechanism for when the external styles you set are not applied for any reason. If the CSS fails to load because something was messed up, your icon will at least have some default nice styles to fall back to. I highly recommend keeping them.

OK so now we have those attributes but we also want to style different instances of our, say, icon, differently.

The way to do that is to make sure we *force* the presentation attributes into inheriting the styles set on `<use>` or find a way to work around them overriding those values. And in order to do *that*, we need to take advantage of the CSS cascade.

Let's start with the simplest of examples and gradually move on to more complex scenarios.

### Overriding Presentation Attribute Values From CSS

Presentation attributes are overridden by any other style declaration. We can take advantage of this and have an external style declaration force the presentation attribute into overriding its value with the inherited value from `use`.

By using the CSS [`inherit` keyword](http://tympanus.net/codrops/css_reference/inherit), this becomes quite simple. Take a look at the following example where we have an ice cream icon made up of just one path whose fill color we want to change for different instances. The icon is Created by Erin Agnoli from the [Noun Project](http://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/thenounproject.com).

```html
<svg>
    <symbol id="ic">
        <path fill="#000" d="M81,40.933c0-4.25-3-7.811-6.996-8.673c-0.922-5.312-3.588-10.178-7.623-13.844  c-2.459-2.239-5.326-3.913-8.408-4.981c-0.797-3.676-4.066-6.437-7.979-6.437c-3.908,0-7.184,2.764-7.979,6.442  c-3.078,1.065-5.939,2.741-8.396,4.977c-4.035,3.666-6.701,8.531-7.623,13.844C22.002,33.123,19,36.682,19,40.933  c0,2.617,1.145,4.965,2.957,6.589c0.047,0.195,0.119,0.389,0.225,0.568l26.004,43.873c0.383,0.646,1.072,1.04,1.824,1.04  c0.748,0,1.439-0.395,1.824-1.04L77.82,48.089c0.105-0.179,0.178-0.373,0.225-0.568C79.855,45.897,81,43.549,81,40.933z   M49.994,11.235c2.164,0,3.928,1.762,3.928,3.93c0,2.165-1.764,3.929-3.928,3.929s-3.928-1.764-3.928-3.929  C46.066,12.997,47.83,11.235,49.994,11.235z M27.842,36.301c0.014,0,0.027,0,0.031,0c1.086,0,1.998-0.817,2.115-1.907  c0.762-7.592,5.641-13.791,12.303-16.535c1.119,3.184,4.146,5.475,7.703,5.475c3.561,0,6.588-2.293,7.707-5.48  c6.664,2.742,11.547,8.944,12.312,16.54c0.115,1.092,1.037,1.929,2.143,1.907c2.541,0.013,4.604,2.087,4.604,4.631  c0,1.684-0.914,3.148-2.266,3.958H25.508c-1.354-0.809-2.268-2.273-2.268-3.958C23.24,38.389,25.303,36.316,27.842,36.301z   M50.01,86.723L27.73,49.13h44.541L50.01,86.723z"/>
</symbol>
</svg>
```

The ice cream icon's contents (the `path`) are defined in a `<symbol>` element, which means that they won't be directly rendered on the SVG canvas.

Then, we render multiple instances of the icon using `<use>`.

```html
<svg class="icon" viewBox="0 0 100 125">
    <use class="ic-1" xlink:href="#ic" x="0" y="0" />
</svg>
<svg class="icon" viewBox="0 0 100 125">
    <use class="ic-2" xlink:href="#ic" x="0" y="0" />
</svg>
```

And we set the width and height of the icons from CSS. I am using the same dimensions as the `viewBox` dimensions but they don't have to be identical. However, to avoid getting any excess white space inside the SVG, make sure you maintain the same aspect ratio between them.

```css
.icon {
    width: 100px;
    height: 125px;
}
```

Using the above code, you get the following result:

![](./Screen-Shot-2015-07-15-at-13.21.02.png)

Note that I have added a black border to the SVGs so you can see the boundaries of each one and to show you that the contents of the first SVG where we defined the icon contents are not rendered. This is to make a point here: **the SVG document where you define your `symbol`s will still be rendered on the page, even if it contains no rendered shapes**. In order to avoid that, make sure you set `display: none` on the first SVG. If you don't hide the SVG containing the icon definitions, it will be rendered even if you don't explicitly set any dimensions for it—the browser will default to 300 pixels by 150 pixels, which is the default size for non-replaced elements in CSS, so you will end up with a white area on the page that you do not want.

Now let's try to change the fill color for each icon instance:

```css
use.ic-1 {
    fill: skyblue;
}

use.ic-2 {
    fill: #FDC646;
}
```

The fill color of the icons still does not change because the inherited color values are being overridden by the `fill="#000"` on the `path` element. To prevent that from happening, let's force the `path` into inheriting the color value:

```css
svg path {
    fill: inherit;
}
```

And voila!—the colors we set on the `<use>` elements are now applied to the `path` in each one. Check the live demo out and play with the values creating more instances and changing their colors as you go:

<br />

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/wzxWxR/?height=300&theme-id=21735&default-tab=result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wzxWxR/'>wzxWxR</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

Now this technique is useful when you want to force the contents of `<use>` to inherit the styles you set on it. But in most cases, this may not be exactly what you want. There are other styling scenarios, so we'll go over some of them next.

#### Styling `<use>` Content with the CSS `all` Property

A while back I was working on an icon referenced with `use` and I wanted one of the elements inside of it to inherit all the styles I set on `<use>` like `fill`, `stroke`, `stroke-width`, `opacity` and even `transform`. Basically, I wanted to be able to control all of those attributes from CSS while also keeping the presentation attributes in the markup as fallback.

If you find yourself in such a scenario as well, you will probably find it time-consuming to have to do this in the CSS:

```css
path#myPath {
    fill: inherit;
    stroke: inherit;
    stroke-width: inherit;
    transform: inherit;
    /* ... */
}
```

Looking at the above snippet, you can see a pattern and it would only make sense for us to be able to combine *all* of those properties into one property and set that property's value to `inherit`.


Fortunately, this is where the CSS `all` property helps. I have written about using the `all` property to style SVG `<use>` content in [property's CSS Reference entry](http://tympanus.net/codrops/css_reference/all/), but it is worth a second look here since we're in the right context.

Using the `all` property, we can do this:

```css
path#myPath {
    all: inherit;
}
```

This works great in all browsers that support the `all` property (see property's entry for details), however there is something important to keep in mind: **this declaration will set literally *all* of the properties on the element to inherit their values from their ancestor**, even those you might not have wanted to target. So unless you want to style *all* the properties of your element from your CSS, then you do not want to use this—it is **an extreme measure** and is particularly useful for when you want to "bare-bone" your element and have complete control over its styling properties in CSS, which may not be too often. If you use this declaration and don't specify values for all of the properties in your CSS, they will go up and cascade until they find a value to inherit, which in most cases will be the default browser styles from the default user agent style sheet.

Note that this will only affect the attributes that can be set in CSS, not the SVG-only attributes. So if an attribute can be set as a CSS property, it will be set to `inherit`, otherwise it won't.

---

Being able to force the presentation attributes to inherit from `<use>` styles is powerful, but what if you have an icon with multiple elements and you *don't* want *all* of those elements to inherit the same `fill` color from `use`? What if you want to apply multiple different fill colors to different `use` descendants? Setting one style on `use` no longer suffices. We need something else to help us cascade the right colors to the right elements.

### Using the CSS `currentColor` Variable For Styling `<use>` Content

Using the CSS [`currentColor` variable ](http://tympanus.net/codrops/css_reference/color_value/#section_currentColor)in conjunction with the above technique, we can specify two different colors on an element, instead of just one. Fabrice Weinberg [wrote about this technique on his Codepen blog](http://codepen.io/FWeinb/blog/quick-tip-svg-use-style-two-colors) a little less than a year ago.

The idea behind this technique is to use both the `fill` and the `color` properties on `<use>`, and then have these colors cascade into the contents of `<use>` by taking advantage of the variable nature of `currentColor`. Let's jump right into a code example to see how this works.

Suppose we want to style this minimal Codrops logo using two colors—one for the front drop and one for the back drop—for every instance of that logo.

![](./StylingSVGuse_codropsdrops.png)

First, let's start with the code for the above screenshot: we have the `symbol` containing our icon definition and then three `<use>` instances creating the three logo instances.

```html
<svg style="display: none;">
<symbol id="codrops" viewBox="0 0 23 30">
    <path class="back" fill="#aaa" d="M22.63,18.261c-0.398-3.044-2.608-6.61-4.072-9.359c-1.74-3.271-3.492-5.994-5.089-8.62l0,0   c-1.599,2.623-3.75,6.117-5.487,9.385c0.391,0.718,0.495,1.011,0.889,1.816c0.143,0.294,0.535,1.111,0.696,1.43   c0.062-0.114,0.582-1.052,0.643-1.162c0.278-0.506,0.54-0.981,0.791-1.451c0.823-1.547,1.649-2.971,2.469-4.33   c0.817,1.359,1.646,2.783,2.468,4.33c0.249,0.47,0.513,0.946,0.791,1.453c1.203,2.187,2.698,4.906,2.96,6.895   c0.292,2.237-0.259,4.312-1.556,5.839c-1.171,1.376-2.824,2.179-4.663,2.263c-1.841-0.084-3.493-0.887-4.665-2.263   c-0.16-0.192-0.311-0.391-0.448-0.599c-0.543,0.221-1.127,0.346-1.735,0.365c-0.56-0.019-1.095-0.127-1.599-0.313   c1.448,3.406,4.667,5.66,8.447,5.78C19.086,29.537,23.469,24.645,22.63,18.261z"/>
    <path class="front" fill="#ddd" d="M6.177,11.659c0.212,0.367,0.424,0.747,0.635,1.136c0.164,0.303,0.333,0.606,0.512,0.927   c0.683,1.225,1.618,2.898,1.755,3.937c0.144,1.073-0.111,2.056-0.716,2.769c-0.543,0.641-1.315,1.014-2.186,1.067   c-0.87-0.054-1.643-0.43-2.186-1.067c-0.604-0.713-0.858-1.695-0.715-2.771c0.137-1.036,1.072-2.712,1.755-3.936   c0.18-0.32,0.349-0.623,0.513-0.927C5.752,12.404,5.964,12.026,6.177,11.659 M6.177,5.966L6.177,5.966   c-1.02,1.649-2.138,3.363-3.247,5.419c-0.932,1.728-2.344,3.967-2.598,5.88c-0.535,4.014,2.261,7.09,5.846,7.203   c3.583-0.113,6.379-3.189,5.845-7.203c-0.255-1.912-1.666-4.152-2.598-5.88C8.314,9.329,7.196,7.617,6.177,5.966L6.177,5.966z"/>
</symbol>
</svg>
<svg height="90px" width="69px">
    <use xlink:href="#codrops" class="codrops-1"/>
</svg>
<svg height="90px" width="69px">
    <use xlink:href="#codrops" class="codrops-2"/>
</svg>
<svg height="90px" width="69px">
    <use xlink:href="#codrops" class="codrops-3"/>
</svg>
```

If we were to set the `fill` color on the `<use>` element for each instance, that color would be inherited by both paths (drops) and they would both end up having the same color—which is not what we want.

So instead of specifying only the `fill` color and having it cascade the default way, we are going to use the `currentColor` variable to make sure the small drop in the front gets a different color value: the value specified using the `color` property.

First, we need to insert the `currentColor` where we want that color value to be applied; it goes into the markup where the icon contents are defined, inside the `<symbol>`. So the code looks like this:

```html
<svg style="display: none;">
	<symbol id="codrops" viewBox="0 0 23 30">
		<path class="back" fill="#aaa" d="..."/>
		<path class="front" fill="currentColor" d="..."/>
	</symbol>
</svg>
```

Next we need to remove the `fill` presentation attribute from the other drop, and let it inherit the `fill` color from `use` without using the `inherit` technique.

If we were to use the `inherit` keyword to force the presentation attributes into inheriting their values from `use`, both paths will inherit the same value and the `currentColor` will no longer have an effect. So, in this technique, we do need to remove the attribute we want to set in CSS, and only keep the one whose value we want to set using `currentColor`.

```html
<svg style="display: none;">
	<symbol id="codrops" viewBox="0 0 23 30">
		<path class="back" d="..."/>
		<path class="front" fill="currentColor" d="..."/>
	</symbol>
</svg>
```

Now, using `fill` and `color` properties on `<use>`, we style the drops:

```css
.codrops-1 {
    fill: #4BC0A5;
    color: #A4DFD1;
}
.codrops-2 {
    fill: #0099CC;
    color: #7FCBE5;
}
.codrops-3 {
    fill: #5F5EC0;
    color: #AEAFDD;
}
```

Each `<use>` element gets its own `fill` and `color` values. For each one, the `fill` color cascades and is inherited by the first path which does not have a `fill` attribute, and the value of the `color` property is used as a value for the `fill` attribute on the second path.

So what happened here is that the current color value was *leaked* into the innards of the `<use>` element, using the `currentColor` variable. Pretty neat, right?

Here is the live demo for the above code:

<br />

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/vXaKvR/?height=300&theme-id=21735&default-tab=result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/vXaKvR/'>vXaKvR</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

This two-color variation technique is quite useful for simple bicoloured logos. In Fabrice's article, he created three different variations of the Sass logo by changing the color of the text versus that of the background.

The `currentColor` keyword is the only available CSS variable in CSS today. However, if we had more variables, wouldn't it make it possible for us to distribute and leak even more values into the `<use>` content? Yes, it would. Amelia Bellamy-Royds introduced this very concept in [a Codepen blog post](http://codepen.io/AmeliaBR/thoughts/customizable-svg-icons-css-variables) a little less than a year ago as well. Let's take a look at how that works.

### The Future: Styling &lt;use&gt; Content with CSS Custom Properties a.k.a CSS Variables

Using [CSS Custom Properties (a.k.a CSS Variables)](http://www.w3.org/TR/css-variables/), you can style the contents of `<use>` without having to force the browser into overriding any presentation attribute values.

As [defined on MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/Using_CSS_variables), CSS Variables are entities defined by authors, or users, of Web pages to contain specific values throughout a document. They are set using custom properties and are accessed using a specific functional notation `var()`. They are very similar to CSS preprocessor (like Sass) variables, but are more flexible and [can do things preprocessor variables can't](http://www.sitepoint.com/css-variables-can-preprocessors-cant/). (An entry on CSS Variables will soon be added to the Codrops CSS Reference, so stay tuned.)

Variables, be it CSS variables or preprocessor variables, can have many usage examples, but theming (colors) is one of the most common use cases. And in this section we'll go over how that can be done when styling SVGs.

We'll start with one image defined in a `symbol` and instantiated with `use` and apply this technique to one image only; the concepts applied to style the contents of `<use>` in this example can be applied to as many `<use>` elements as you want.

So, suppose we have the following cute hipster robot illustration [designed by Freepik](http://www.freepik.com/free-vector/cute-vector-hipster-robot-character_714905.htm).

<a href="./1.png"><img style="max-width: 400px;position: relative;display: block;margin: 10px auto;text-align: center;height: auto;" src="./1.png" alt="Screen Shot 2015-07-15 at 22.32.43" width="776" height="1186" class="alignnone size-full wp-image-24468" srcset="./1.png 776w, ./1_1.png 196w" sizes="(max-width: 776px) 100vw, 776px"></a>

The code for the robot contains the colors that make it up.

```html
<svg style="display: none">
    <symbol id="robot" viewBox="0 0 340 536">
        <path d="..." fill="#fff" />
        <path d="..." fill="#D1312C" />
        <path d="..." fill="#1E8F90" />
        <path d="..." fill="#1E8F90" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" />
        <path d="..." fill="#1E8F90"  />
        <path d="..." fill="#6A4933" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" />
        <path d="..." fill="#F2B42B" />
        <path d="..." fill="#fff" />

        <!-- rest of the shapes -->
    </symbol>
</svg>
```

Now, we are *not* going to use the CSS Variables as values for the `fill` attribute of each path; instead, we're going to use them as fill color values using the CSS `fill` *property*, and we're going to keep the `fill` attributes in place. **The attributes will be used as a fallback for browsers that don't support CSS Variables**, so the image will still look as it initially did if the variables fail to work in those browsers.

With the variables added, the above code will look like so:

```html
<svg style="display: none">
    <symbol id="robot" viewBox="0 0 340 536">
        <path d="..." fill="#fff" />
        <path d="..." fill="#D1312C" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color)" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color)" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color)" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color)" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color)" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color)" />
        <path d="..." fill="#F2B42B" style="fill: var(--secondary-color)" />
        <path d="..." fill="#fff" />

        <!-- rest of the shapes -->
    </symbol>
</svg>
```

Since inline `style` tags override presentation attributes, browsers that support CSS Variables will use those variables as fill colors for the shapes. Browsers that do not support CSS variables will use the `fill` attribute values instead.

Next, we need to define the values for the variables in CSS. First, the illustration will be instantiated using `use`:

```html
<svg width="340" height="536">
    <use xlink:href="#robot" id="robot-1" />
</svg>
```

Then, the variables will be defined on `use` so that they cascade into its contents. The colors you choose for the variables will make up the color scheme of the contents of your illustration. So, for the above robot, there were three main colors making up the graphic, so I named them primary, secondary and tertiary.

```css
#robot-1 {
    --primary-color: #0099CC;
    --secondary-color: #FFDF34;
    --tertiary-color: #333;
}
```

You can still use the `fill` and `color` properties alongside these variables, but you may not need to or simply not want to. So, given the above colors defined for the variables, the robot now looks like this:

<a href="./2.png"><img style="max-width: 400px;position: relative;display: block;margin: 10px auto;text-align: center;height: auto;" src="./2.png" alt="Screen Shot 2015-07-15 at 22.54.53" width="796" height="1202" class="alignnone size-full wp-image-24471" srcset="./2.png 796w, ./2_1.png 199w" sizes="(max-width: 796px) 100vw, 796px"></a>

You can have as many copies of the image as you want, and for each `use` define a set of different colors to be used, and end up with different themes. This is particularly useful for when you want to style a logo in different ways depending on the context, or for any other similar use cases.

Now, we mentioned that browsers that don't support CSS Variables are going to fall back to the initial styles defined in the presentation attributes, and browsers that do support the variables will use the variables in the `fill` properties to override the attributes. Great. But what happens if the browser *does* support CSS Variables but the author fails to provide them with a value for a specific variable or if the value they provided is invalid?

For our hipster robot here, we defined three variables, and only a few elements inside of the image did not get any variables because the colors used were complimentary and would go with pretty much any color theme used. So, if you display the above code in a browser that supports CSS variables (currently only Firefox) and remove the variable declarations from the CSS, you will end up with this:

<a href="./3.png"><img style="max-width: 400px;position: relative;display: block;margin: 10px auto;text-align: center;height: auto;" src="./3.png" alt="Screen Shot 2015-07-15 at 22.59.37" width="772" height="1178" class="alignnone size-full wp-image-24472" srcset="./3.png 772w, ./3_1.png 197w" sizes="(max-width: 772px) 100vw, 772px"></a>

If the values provided for the variables are either not set or invalid, the browser will default to its own colors, which is usually black for fill and stroke colors in SVG.

A way to avoid that is to provide **another fallback color for supporting browsers**. Indeed, the CSS variables syntax comes with a way to do just that: instead of providing only the variable name inside the `var()` function as an argument, you provide two comma-separated arguments: the variable name and a fallback color value—which in this case is the value we have in the presentation attributes.

So, going over the above code for the robot, it will look like this:

```html
<svg style="display: none">
    <symbol id="robot" viewBox="0 0 340 536">
        <path d="..." fill="#fff" />
        <path d="..." fill="#D1312C" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color, #1E8F90)" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color, #1E8F90)" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color, #6A4933)" />
        <path d="..." fill="#1E8F90" style="fill: var(--primary-color, #1E8F90)" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color, #6A4933)" />
        <path d="..." fill="#fff" />
        <path d="..." fill="#6A4933" style="fill: var(--tertiary-color, #6A4933)" />
        <path d="..." fill="#F2B42B" style="fill: var(--secondary-color, #F2B42B)" />
        <path d="..." fill="#fff" />

        <!-- rest of the shapes -->
    </symbol>
</svg>
```

And that's it. For any variable that fails to load its defined value or that does not have one, the browser will fall back to the initial color defined in the markup. Wonderful.

Using this technique, you can now reference the robot anywhere you want on the page with `<use>`, and for every new instance define a set of variable values in the CSS, and you'll have a different color theme per instance.

You can play with the above demo, create as many copies of the robot as you want and assign different variable values to them in this live demo, just make sure you use Firefox at this time because it's the only browser supporting CSS Variables at the time of writing of this article:

<br />

<iframe height='495' scrolling='no' src='//codepen.io/aleen42/embed/rrArWW/?height=495&theme-id=21735&default-tab=result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/rrArWW/'>rrArWW</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

<br />

If you view the demo in Firefox, you will see the blue + yellow version of the robot that we defined with CSS variables. Make sure you check the demo in Chrome to see how it falls back to the initial colors (green version), and try removing the variable declarations from the CSS in Firefox to also see how the fallback works.

### Summing Up

Phew. That was a lot.

By taking advantage of the CSS cascade, styling the contents of `<use>`—though in a shadow DOM—can become less complicated. And with CSS variables (be it `currentColor` alone or the custom properties) we can penetrate the lines of the shadow DOM and customize our graphics to our liking while also providing very good fallback for when anything goes wrong.

Personally, I am incredibly excited about the CSS Variables + SVG combination. I love how powerful they are together, especially given the great fallback mechanism we have with it. **They are currently only supported in Firefox, as we mentioned, but if you want to see them get wider support you can start by voting for them in other browsers such as on the [MS Edge User Voice forums](https://wpdev.uservoice.com/forums/257854-internet-explorer-platform/suggestions/6261292-css-variables)**.

We may even get other ways to style `use` content in the future as well since there are already discussions going on about using CSS Variables as SVG parameters; so this article, though long, might have not covered everything there is to know about this topic. If you have any other ideas, please feel free to share them in the comments below.

Dealing with the contents of re`use`d SVG elements has been one of those SVG topics that many people seem to find some hardship with, because of the nature of how the cloned code behaves and where it is cloned to. There are a lot more topics to cover that are related to that, but those are topics for other articles.

I hope you enjoyed this article and found it useful. Thank you for reading.
