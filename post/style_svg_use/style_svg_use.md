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