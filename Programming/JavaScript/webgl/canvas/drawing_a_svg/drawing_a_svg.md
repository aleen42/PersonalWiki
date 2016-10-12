## Drawing a SVG file [Back](./../canvas.md)

This document is to talk about hw to draw a SVG file with canvas in JavaScript.

### Read data from a SVG file

Before drawing a SVG file, you need to read data from a SVG file with `FileReader` in JavaScript. 
 
```js 
var fileReader = new FileReader(); 
``` 
 
`FileReader` is a Web API, which has given some methods for you to read a file.`readAsText` is one of methods, supported by this Web API, for reading file with its contents, and `onload` is the event triggered when a file has been read: 
 
```js 
fileReader.onload = function (e) {
    /** contents of a SVG file */
    var contents = e.target.result;
}; 
 
fileReader.read(file); 
``` 
 
Of course, if you would like to complete a interaction of dragging and dropping a file into a canvas to read a SVG file, you can set up a event handler for listening to the `drop` event of this canvas like this: 
 
```js 
/** Drop Event Handler */ 
canvas.addEventListener('drop', function (e) { 
    /** e is where we can extract out the `file` objecj */ 
    var file = e.dataTransfer.files[0]; 
}) 
```

### Find out what we can draw

In a SVG file, many kinds of tags has been defined for rendering vector shapes like `circle`, `rect`, `polyline`, `line`, `path`, etc. `path` elements are actually what we are going to draw, because any shape/primitive in a SVG is able to be converted into `path`. Later posts will mention how to do this in JavaScript.

Since we are going to draw `path`s, data of these `path`s in a SVG file should be extracted firstly:

```js
var paths = contents.match(/<path([\s\S]+?)\/>/g);
```

Generally, the attribute `d` is represented as data of a `path.