## How to detect squares in an image with OpenCV [Back](./qa.md)

- use the algorithm provided by *karlphillip*, which has been integrated in [**LightOpenCV**](https://github.com/aleen42/LightOpenCV)

#### Useage

- **Image** Class has provided the method *detectSquare*, and print the detected line on the image when giving a boolean value **true**.

```cpp
/* new an instance for Image */
Image img = Image();

/* read the image which is to be detected by giving the path */
img.readImage(imagePath);

/* DEBUG is an marco parameter */
img.detectSquare(DEBUG);

/* show the image */
img.showImage();
```
