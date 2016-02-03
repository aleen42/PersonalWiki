## How to detect squares in an image with OpenCV [Back](./qa.md)

- use the algorithm provided by *karlphillip*, which has been integrated in [**LightOpenCV**](https://github.com/aleen42/LightOpenCV)

#### Useage

- **Image** Class has provided the method *detectSquare*, and print the image when giving a boolean value **true**.

```cpp
Image img = Image();

	img.readImage(imagePath);

	img.detectSquare(DEBUG);

	img.showImage();
}
```


<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
