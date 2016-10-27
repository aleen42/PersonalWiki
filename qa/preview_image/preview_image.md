## How to preview an image after uploaded with file input and FileReader [Back](./../qa.md)

```js
var path = '';
var FileReader = window.FileReader;
var clip = document.getElementById('imgContent');

var file = document.getElementById('file');
var fileHandler = function (e) {
    if (FileReader) {
        var reader = new FileReader();
        var file = this.files[0];
        
        reader.onload = function (e) {
            clip.setAttribute('src', e.target.result);
        };
        
        reader.readAsDataURL(file);
    } else {
        path = e.target.value;
        
        if (/"\w\W"/.test(path)) {
            path = path.slice(1, -1);
        }
        
        clip.setAttribute('src', path);
    }
};

file.addEventListener('change', fileHandler, false);
```
