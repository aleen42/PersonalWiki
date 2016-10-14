## [轉載] Styling SVG &lt;use&gt; Content with CSS [Back](./../post.md)

> - Author: [Sara Soueidan](https://github.com/SaraSoueidan)
- Origin: http://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/
- Time: Jul, 16th, 2015

![](./StylingSVGuse.jpg)

One of the most common use cases for SVG graphics is icon systems, and one of the most commonly-used SVG spriting techniques is one that uses the [SVG &lt;use&gt; element to “instantiate” the icons](https://css-tricks.com/svg-sprites-use-better-icon-fonts/) anywhere they are needed in a document.

Instantiating icons or any other SVG element or image using the <use> element introduces some challenges when it comes to styling the instance of that element. The aim of this article is to give you an overview of some of the possible ways to work around the styling limitations introduced by `<use>`.

But before we get started, let’s take a quick look into SVG’s main structuring and grouping elements that will gradually take us into the world of use, the shadow of its DOM, and then bring us back into the light with CSS. We’ll go over why styling `<use>` content can be challenging and ways to work around that.