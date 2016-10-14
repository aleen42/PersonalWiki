## [轉載] Styling SVG &lt;use&gt; Content with CSS [Back](./../post.md)

> - Author: [Sara Soueidan](https://github.com/SaraSoueidan)
- Origin: http://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/
- Time: Jul, 16th, 2015

![](./StylingSVGuse.jpg)

One of the most common use cases for SVG graphics is icon systems, and one of the most commonly-used SVG spriting techniques is one that uses the [SVG &lt;use&gt; element to “instantiate” the icons](https://css-tricks.com/svg-sprites-use-better-icon-fonts/) anywhere they are needed in a document.

Instantiating icons or any other SVG element or image using the `<use>` element introduces some challenges when it comes to styling the instance of that element. The aim of this article is to give you an overview of some of the possible ways to work around the styling limitations introduced by `<use>`.

But before we get started, let’s take a quick look into SVG’s main structuring and grouping elements that will gradually take us into the world of use, the shadow of its DOM, and then bring us back into the light with CSS. We’ll go over why styling `<use>` content can be challenging and ways to work around that.

### Quick Overview of SVG Structuring, Grouping and Referencing (Re-using) Elements in SVG

There are four main elements in SVG that are used to define, structure and reference SVG code within the document. These elements make reusing elements easy, while maintaining clean and readable code. Because of the nature of SVG, some of these elements have the same functionality as certain commands in graphics editors.

The four main SVG grouping and referencing elements are: `<g>`, `<defs>`, `<use>` and `<symbol>`.

The `<g>` element (short for “group”) is used for logically grouping together sets of related graphical elements. In terms of graphics editors, such as Adobe Illustrator, the `<g>` element serves a similar functionality as the Group Objects function. You can also think of a group as being similar to the concept of a layer in a graphics editor, since a layer is also a grouping of elements.

Grouping elements together is useful for when you want to apply a style and have that style be inherited by all the elements in the group, and is particularly useful for when you want to animate a group of elements while maintaining their spatial relationships with each other.

The `<defs>` element is used to define elements that you want to reuse later. Defining elements with `<defs>` is useful for when you want to create sort of a “template” that you want to use multiple times throughout the document. Elements defined inside a `<defs>` element are not rendered on the canvas except if you “call” them somewhere in the document.

`<defs>` is useful for defining many things, but one of the main use cases is defining patterns like gradients, for example, and then using those gradients as stroke fills on other SVG elements. It can be used to define any elements that you want to render anywhere on the canvas by reference.

The `<symbol>` element combines the benefits of both the `<defs>` and the `<g>` elements in that it is used to group together elements that define a template that is going to be referenced elsewhere in the document. Unlike `<defs>`, `<symbol>` is not usually used to define patterns, but is mostly used to define symbols such as icons, for example, that are referenced throughout the document.

The `<symbol>` element has an important advantage over the other two elements: it accepts a viewBox attribute which allows it to scale-to-fit inside any viewport it is rendered in.

The `<use>` element is the element you use to reference any element defined elsewhere in the document. It lets you reuse existing elements, giving you a similar functionality to the copy-paste functionality in a graphics editor. It can be used to reuse a single element, or a group of elements defined with the `<g>` element, the `<defs>` element, or a `<symbol>`.

To use an element you pass a reference to that element—an ID—inside the use‘s xlink:href attribute, and you position that element using x and y attributes. You can apply styles to the use element and those styles will cascade into the contents of the use element.

But what is the content of `<use>`? Where is it cloned? And how does the CSS cascade work with that content?

Before we answer these questions, and since we only covered a quick overview of SVG’s structuring and grouping elements, it’s worth mentioning a couple of articles to learn more about these elements and about the `viewBox` attribute used with `<symbol>`:

- [Structuring, Grouping, and Referencing in SVG — The `<g>`, `<use>`, `<defs>` and `<symbol>` Elements](http://sarasoueidan.com/blog/structuring-grouping-referencing-in-svg/)
- [Understanding SVG Coordinate Systems (Part 1): The Viewport, `viewBox` and `PreserveAspectRatio`](http://sarasoueidan.com/blog/svg-coordinate-systems)

### SVG &lt;use&gt; and The Shadow DOM

When you reference an element with `<use>`, the code might look something like this:

```html
<symbol id="my-icon" viewBox="0 0 30 30">
    <!-- icon content / shapes here -->
</symbol>

<use xlink:href="#my-icon" x="100" y="300" />
```

What is rendered on the screen is the icon whose content is defined inside `<symbol>`, but it’s not that content that got rendered, but rather the content of the `<use>`, which is a duplicate—or clone—of the `<symbol>`’s content.

But the `<use>` element is only one element and it is self-closing—there is no content somewhere between an opening and closing use tag, so where has the `<symbol>` content been cloned?

The answer to that is: **the Shadow DOM**. (Somehow the Shadow DOM always reminds me of the Batman. I don’t know why.)

#### What is the Shadow DOM?

The Shadow DOM is similar to the normal DOM except that, instead of being part of the main document subtree, nodes in the Shadow DOM belong to a document fragment which is basically just another subtree of nodes which are not as vulnerable to scripts and styles as normal DOM nodes are. This gives authors a way to encapsulate and scope styles and scripts when creating modular components. If you’ve ever used the HTML5 video element or the range input type and wondered where the video controls or range slider components came from, then you’ve already come across the Shadow DOM before.

In the case of the SVG `<use>` element, the contents of the referenced element are cloned into a document fragment that is “hosted” by `<use>`. `<use>`, in this case, is called a Shadow Host.

So, the contents of `<use>` (the clone or copy of whatever element it is referencing) are present inside a shadow document fragment.

In other words, they are there, but they are not visible. They are just like normal DOM content, but instead of being available in the “high-level” DOM which is accessible by CSS selectors and JavaScript in the main document, they are copied into a document fragment that is hosted by `<use>`.

Now, if you’re a designer, you might be thinking: “OK, I get it but is there a way to inspect that sub-document to actually see into its contents?” The answer is: Yes! You can preview the contents of the shadow DOM using Chrome’s developer tools. (Inspecting the contents of a shadow DOM is currently not possible in Firefox.) But in order to do that, you need to first enable shadow DOM inspection in the “General” tab inside the Settings panel that can be opened by clicking on the Cog icon. You can learn more about how to do that here.

Once you’ve enable shadow DOM inspection in the dev tools, you can see the cloned elements in the Elements panel, just like you would with normal DOM elements. The following image shows an example of a `<use>` element referencing the contents of a `<symbol>`. Notice the “#shadow-root” and the contents of that fragment when expanded—they are a copy of the contents of the `<symbol>`.

> ![](shadow-dom.jpg)

> Using Chrome’s developer tools, you can inspect the contents of the &lt;use&gt; element inside the shadow DOM (see the “#shadow-root” in grey). This screenshot inspects the Codrops logo from an example we will go over in the next section.

Looking at the inspected code, you can see that the shadow DOM is pretty much the same as the normal DOM, except that is has different characteristics when it comes to handling with CSS and JavaScript from the main document. There are also other differences between them, but the shadow DOM cannot possibly be covered in this section because it is too big of a concept, so if you want to read and learn more about it, I recommend the following articles:

- [Intro to Shadow DOM](http://code.tutsplus.com/tutorials/intro-to-shadow-dom--net-34966)
- [What the Heck is Shadow DOM?](http://glazkov.com/2011/01/14/what-the-heck-is-shadow-dom/)
- [Shadow DOM 101](http://www.html5rocks.com/en/tutorials/webcomponents/shadowdom/)
- [Introduction to Shadow DOM (Video)](http://webcomponents.org/articles/introduction-to-shadow-dom/)

For me, and considering how limited my interaction with the shadow DOM is, I think of it as being just like the normal DOM, except that it needs to be handled differently when it comes to accessing its elements for styling with CSS (and JavaScript). This is what matters to us as SVG developers: how the existence of the contents of `<use>` inside a shadow DOM affects that content when it comes to applying or changing styles, because we want to be able to style them. The whole point of using `<use>` is being able to create different “copies” of an element, and in a lot of cases, what we want is to be able to style each copy differently. For example, think about a logo with two styles (inverted color themes) or multi-coloured icons of which each has its own theme. So, it would only make sense for us to expect to be able to do that using CSS.
That being said, we mentioned earlier that the contents of the shadow DOM are not vulnerable to CSS like the normal DOM is. So how do we style its content? We cannot target a path descendant of `<use>` like this:

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

Since SVG elements can be styled using CSS using one of three different ways: external CSS styles (in an external style sheet), internal style blocks (`<style>` elements) and inline styles (in a style attribute), it only makes sense that the cascade governs how these styles are applied to these elements.

In addition to CSS properties, SVG elements can also be styled using presentation attributes. Presentation attributes are a shorthand for setting a CSS property on an element. Think of them as special style properties. Their nature is what makes them contribute to the style cascade, but maybe in a less expected way.

In the following code snippet which simply displays a pink circle with a yellow stroke, stroke, stroke-width, and fill are all presentation attributes.

```html
<svg viewBox="0 0 100 100">
    <circle fill="deepPink" stroke="yellow" stroke-width="5" cx="50" cy="50" r="10"></circle>
</svg>
```

In SVG, a subset of all CSS properties may be set by SVG attributes, and vice versa. This means that not all CSS properties can be specified on an SVG element as presentation attributes, and not all presentation attributes available in SVG (there are a lot of them!) can be specified in CSS.

The SVG specification lists the SVG attributes that may be set as CSS properties. Some of these attributes are shared with CSS (already available as CSS properties), such as opacity and transform, among others, while some are not, such as fill, stroke and stroke-width, among others.

In SVG 2, this list will include x, y, width, height, cx, cy and a few other presentation attributes that were not possible to set via CSS in SVG 1.1. The new list of attributes can be found in the SVG 2 specification.

If you’re like me, then you would expect presentation attributes to have a higher specificity than all other style declarations. I mean, after all, external styles are overridden by internal styles in style blocks, and style block declarations are overridden by inline styles in a style attribute.. so it seems as though the more “internal” the styles get, the more specificity they have, and so when a property gets its own attribute, it makes it more powerful and thus it would override all other style declarations. Although that still makes sense to me, this is not how it really works.

As a matter of fact, presentation attributes count as low-level “author style sheets” and are overridden by any other style definitions: external style sheets, document style sheets and inline styles. The only power presentation attributes have in the style cascade is over inherited styles. That is, presentation attributes can only override inherited styles on an element, and are overridden by any other style declaration.

Great, now that that’s been cleared up, let’s get back to the `<use>` element and its content.

We now know that we cannot set styles on the elements inside `<use>` using CSS selectors.

We also know that, just like with the `<g>` element, styles you apply to `<use>` will be inherited by all its descendants (those in the shadow DOM).

So a first attempt to change the fill color of an element inside `<use>` would be to apply that fill color to the `<use>` element itself and let inheritance and the cascade do its thing.

However, that brings up two issues:

1. The fill color will be inherited by all the descendants of `<use>`, even those you may not want to style. (If you have only one element inside `<use>`, then this won’t be an issue.)
2. If you’ve exported an SVG from a graphics editor and/or got an SVG from a designer who did that and for any reason you can’t touch the SVG code, then you’re likely to end up with SVG elements with presentation attributes applied (unless you explicitly specified that you don’t want this to happen upon exporting the SVG, but that’s another topic), and the values of these attributes are going to override any styles you apply on `<use>`. Now, I’m assuming that if you are specifying styles on `<use>` then you want those styles to be inherited by its descendants, so presentation attributes would be causing an inconvenience in this case.

And even if you do have access to the SVG code and you can get rid of the presentation attributes, **I highly recommend against that** because:

1. Removing the attributes used to set certain properties will reset those properties to their initial browser-default values—which, in most cases, is all black fills and strokes (if we’re talking about colors, for example).
2. By resetting all values you force yourself into specifying styles for all the properties set, so unless you want to do just that, then you don’t want to get rid of those presentation attributes.
3. The presentation attributes that are initially available are a great fallback mechanism for when the external styles you set are not applied for any reason. If the CSS fails to load because something was messed up, your icon will at least have some default nice styles to fall back to. I highly recommend keeping them.

OK so now we have those attributes but we also want to style different instances of our, say, icon, differently.

The way to do that is to make sure we force the presentation attributes into inheriting the styles set on `<use>` or find a way to work around them overriding those values. And in order to do that, we need to take advantage of the CSS cascade.

Let’s start with the simplest of examples and gradually move on to more complex scenarios.

### Overriding Presentation Attribute Values From CSS

Presentation attributes are overridden by any other style declaration. We can take advantage of this and have an external style declaration force the presentation attribute into overriding its value with the inherited value from use.

By using the CSS [inherit keyword](http://tympanus.net/codrops/css_reference/inherit), this becomes quite simple. Take a look at the following example where we have an ice cream icon made up of just one path whose fill color we want to change for different instances. The icon is Created by Erin Agnoli from the [Noun Project](http://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/thenounproject.com).

```html
<svg>
    <symbol id="ic">
        <path fill="#000" d="M81,40.933c0-4.25-3-7.811-6.996-8.673c-0.922-5.312-3.588-10.178-7.623-13.844  c-2.459-2.239-5.326-3.913-8.408-4.981c-0.797-3.676-4.066-6.437-7.979-6.437c-3.908,0-7.184,2.764-7.979,6.442  c-3.078,1.065-5.939,2.741-8.396,4.977c-4.035,3.666-6.701,8.531-7.623,13.844C22.002,33.123,19,36.682,19,40.933  c0,2.617,1.145,4.965,2.957,6.589c0.047,0.195,0.119,0.389,0.225,0.568l26.004,43.873c0.383,0.646,1.072,1.04,1.824,1.04  c0.748,0,1.439-0.395,1.824-1.04L77.82,48.089c0.105-0.179,0.178-0.373,0.225-0.568C79.855,45.897,81,43.549,81,40.933z   M49.994,11.235c2.164,0,3.928,1.762,3.928,3.93c0,2.165-1.764,3.929-3.928,3.929s-3.928-1.764-3.928-3.929  C46.066,12.997,47.83,11.235,49.994,11.235z M27.842,36.301c0.014,0,0.027,0,0.031,0c1.086,0,1.998-0.817,2.115-1.907  c0.762-7.592,5.641-13.791,12.303-16.535c1.119,3.184,4.146,5.475,7.703,5.475c3.561,0,6.588-2.293,7.707-5.48  c6.664,2.742,11.547,8.944,12.312,16.54c0.115,1.092,1.037,1.929,2.143,1.907c2.541,0.013,4.604,2.087,4.604,4.631  c0,1.684-0.914,3.148-2.266,3.958H25.508c-1.354-0.809-2.268-2.273-2.268-3.958C23.24,38.389,25.303,36.316,27.842,36.301z   M50.01,86.723L27.73,49.13h44.541L50.01,86.723z"/>
</symbol>
</svg>
```

The ice cream icon’s contents (the path) are defined in a `<symbol>` element, which means that they won’t be directly rendered on the SVG canvas.

Then, we render multiple instances of the icon using `<use>`.

```html
<svg class="icon" viewBox="0 0 100 125"> 
    <use class="ic-1" xlink:href="#ic" x="0" y="0" />
</svg>
<svg class="icon" viewBox="0 0 100 125"> 
    <use class="ic-2" xlink:href="#ic" x="0" y="0" />
</svg>
```

And we set the width and height of the icons from CSS. I am using the same dimensions as the viewBox dimensions but they don’t have to be identical. However, to avoid getting any excess white space inside the SVG, make sure you maintain the same aspect ratio between them.

```css
.icon {
    width: 100px;
    height: 125px;
}
```

Using the above code, you get the following result:

![](./Screen-Shot-2015-07-15-at-13.21.02.png)

Note that I have added a black border to the SVGs so you can see the boundaries of each one and to show you that the contents of the first SVG where we defined the icon contents are not rendered. This is to make a point here: **the SVG document where you define your symbols will still be rendered on the page, even if it contains no rendered shapes**. In order to avoid that, make sure you set display: none on the first SVG. If you don’t hide the SVG containing the icon definitions, it will be rendered even if you don’t explicitly set any dimensions for it—the browser will default to 300 pixels by 150 pixels, which is the default size for non-replaced elements in CSS, so you will end up with a white area on the page that you do not want.

Now let’s try to change the fill color for each icon instance:

```css
use.ic-1 {
    fill: skyblue;
}

use.ic-2 {
    fill: #FDC646;
}
```

The fill color of the icons still does not change because the inherited color values are being overridden by the fill="#000" on the path element. To prevent that from happening, let’s force the path into inheriting the color value:

```css
svg path {
    fill: inherit;
}
```

And voila!—the colors we set on the `<use>` elements are now applied to the path in each one. Check the live demo out and play with the values creating more instances and changing their colors as you go:

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/wzxWxR/?height=300&theme-id=21735&default-tab=result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/wzxWxR/'>wzxWxR</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

Now this technique is useful when you want to force the contents of `<use>` to inherit the styles you set on it. But in most cases, this may not be exactly what you want. There are other styling scenarios, so we’ll go over some of them next.

#### Styling `<use>` Content with the CSS `all` Property

A while back I was working on an icon referenced with use and I wanted one of the elements inside of it to inherit all the styles I set on `<use>` like `fill`, `stroke`, `stroke-width`, `opacity` and even `transform`. Basically, I wanted to be able to control all of those attributes from CSS while also keeping the presentation attributes in the markup as fallback.

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

Looking at the above snippet, you can see a pattern and it would only make sense for us to be able to combine all of those properties into one property and set that property’s value to inherit.


Fortunately, this is where the CSS all property helps. I have written about using the all property to style SVG `<use>` content in [property’s CSS Reference entry](http://tympanus.net/codrops/css_reference/all/), but it is worth a second look here since we’re in the right context.

Using the all property, we can do this: