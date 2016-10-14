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