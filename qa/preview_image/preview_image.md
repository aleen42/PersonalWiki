## How to preview an image after uploaded with file input and FileReader [Back](./../qa.md)

```js
var path = '';
var FileReader = window.FileReader;
var clip = document.getElementById('imgContent');

var file = document.getElementById('file');

file.addEventListener('change', function (e) {
    if (FileReader) {
        var reader = new FileReader();
        var file = this.files[0];
        
        reader.onload = function (e) {
            clip.attr('src', e.target.result);
        };
        
        reader.readAsDataURL(file);
    }
}, false);
```
