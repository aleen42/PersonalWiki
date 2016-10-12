## Calibration Parameters (校正參數) for drawing a SVG file [Back](./../SVG.md)

Before drawing a SVG file, you need to read a SVG file with `FileReader` in JavaScript.

```js
var fileReader = new FileReader();
```

Then, `readAsText` is the method, supported by this Web API, for reading file with its content.

```js
fileReader.read(file);
```

Of course, if you want to complete a interaction of dragging and dropping a file into a box, you can also use 