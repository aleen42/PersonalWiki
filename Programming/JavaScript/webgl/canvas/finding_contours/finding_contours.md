## Finding Contours of a bitmap image [Back](./../canvas.md)

Here I want to talk about how to find contours of a bitmap image in Canvas, and documenting it so that we can check it later when it's required.

Firstly, the whole process of finding can be simply described as: **Gray Scale** -> **Gaussian Blur** -> **Canny Gradient** -> **Canny Non-maximum Suppression** -> **Canny Hysteresis** -> **Scanning**

### Gray Scale

Gray Scale in Wikipedia is defined as followed:

> In photography and computing, a **grayscale** or **greyscale** digital image is an image in which the value of each pixel is a single sample, that is, it carries only intensity information."

In this process, we will change the image data directly through Canvas:

```js
function runImg(canvas, size, fn) {
    for (var y = 0; y < canvas.height; y++) {
        for (var x = 0; x < canvas.width; x++) {
            var i = x * 4 + y * canvas.width * 4;
            var matrix = getMatrix(x, y, size);
            fn(i, matrix);
        }
    }

    function getMatrix(cx, cy, size) {
        /**
         * will generate a 2d array of size x size given center x,
         * center y, size, image width & height
         */
        if (!size) {
            return;
        }
        
        var matrix = [];
        
        for (var i = 0, y = -(size - 1) / 2; i < size; i++, y++) {
            matrix[i] = [];
            
            for (var j = 0, x = -(size - 1) / 2; j < size; j++, x++) {
                matrix[i][j] = (cx + x) * 4 + (cy + y) * canvas.width * 4;
            }
        }
        
        return matrix;
    }
}

function getRGBA(i, imgData) {
    return {
        r: imgData.data[start],
        g: imgData.data[start + 1],
        b: imgData.data[start + 2],
        a：imgData.data[start + 3]
    };
}

function getPixel(i, imgData) {
    if (i < 0 || i > imgData.data.length - 4) {
        return {
            r: 255,
            g: 255,
            b: 255,
            a: 255
        };
    } else {
        return getRGBA(i, imgData);
    }
}

function calculateGray(pixel) {
    return ((0.3 * pixel.r) + (0.59 * pixel.g) + (0.11 * pixel.b));
}

function grayscale(canvas) {
    var ctx = canvas.getContext('2d');

    var imageDataCopy = ctx.getImageData(0, 0, canvas.width, canvas.height);
    var grayLevel;
    
    runImg(canvas, null, function (current) {
        grayLevel = calculateGray(getPixel(current, imgDataCopy));
    });
};
```