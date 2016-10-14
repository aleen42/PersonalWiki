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
- Shadow DOM 101
- Introduction to Shadow DOM (Video)