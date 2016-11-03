## [原創] How to draw in JavaScript? [Back](./../post.md)

<p align="center"><img width="70%" src="./preview.png" alt="draw in javascript" /></p>
<p align="center"><strong>Figure 1.1</strong> A simple preview</p>

Since my company has given me a requirement of drawing in a browser programmatically, simply shown as the figure 1.1 above, I would like to share some points with you about drawing in JavaScript. Actually, what we're going to draw? **Any kind of pictures**.

Note that this is a project which belongs to my company, and that's why I'm not going to *open* the source code in the public community.

At the beginning of the project, I was exactly inspired by the animation of drawing glowing line in [this article](./../../Programming/JavaScript/webgl/canvas/line_drawing/line_drawing.md). If you read it in details, you'll also find that before we draw any pictures, what we need is the data of paths, with which we are able to simulate the drawing. The format of those data should be like this:

```nginx
M 161.70443,272.07413
C 148.01517,240.84549 134.3259,209.61686 120.63664,178.38822
C 132.07442,172.84968 139.59482,171.3636 151.84309,171.76866
```

You may doubt that such data is only legal in an SVG element, named `path`, and how can we draw all kinds of pictures like JPG, PNG, or GIF. That's another topic going to be discussed later in this post. Before that, we can just simply draw an SVG file.

### Drawing an SVG file

What is SVG? Scalable Vector Graphics a.k.a SVG is an XML-based vector image format for two-dimensional graphics with support for interactivity and animation. In older IE browsers, such kind of files is not supported at all. If you're a designer, or an illustrator who usually used Adobe Illustration as one of your drawing tools, you may be already similar with those kinds of pictures. What the main difference is, an SVG is scalable and lossless, opposed to other formats of pictures.

#### Extracting data from an SVG file

As mentioned above, before drawing an SVG file, what you need to do is to read data from an SVG file. It's actually the duty of an object, named `FileReader` in JavaScript, of which the initialization code snippet should be look like this:

```js
if (FileReader) {
    /** if the browser support FileReader Objects */
    var fileReader = new FileReader();
}
```

As a Web API, `FileReader` has given you a chance to read local files, in which `readAsText` is one of methods supported for reading contents with text format. As it may trigger the `onload` event set before being called, we can exactly read the content inside an event handler. So, the code of reading contents should be:

```js
fileReader.onload = function (e) {
    /** contents of an SVG file */
    var contents = e.target.result;
};

fileReader.readAsText(file);
```
