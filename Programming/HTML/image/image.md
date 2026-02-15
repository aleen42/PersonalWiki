## Image [Back](./../HTML.md)

- images you want to add to a web page may be a **logo**, **photograph**, **illustration**, **diagram** or **chart**.
- **stock images** are images you pay to use.
- ```<img>``` is used to add an image.
	- ```<img src="images/home.jpg" alt="a home" title="a home"/>```
	- src: where to find this image
	- alt: a description for this image shown when you cannnot see it(**alt text** should have an accurate description, used by people with visual impairments and search engines. It should be left empty but still be used even if it has no meanings.)
	- title: a description for this image shown when you hover over the image
	- height: to specify the height of this image in pixels(**px**)
	- width: to specify the width of this image
	- align: to indicate how the other parts of a page should flow around the image(it is not supported by HTML5)
		- horizonal
			- left
			- center
			- right
		- vertical
			- top
			- middle
			- bottom
- images can be put **before a paragraph**, **inside the start of a paragraph** or **in the middle of a paragraph**.
- **3** rules for creating images
	- 1. save images in the right **format**.
		- JPEG: a picture which has many different colors.
		- GIF/PNG: a picture with few colors or large areas of the same color, like **Logos**, **illustrations** or **diagrams**.(Or an image that is **transparency**)
	- 2. save iamges at the right **size**.
		- image will look **blurry** when its size increases from the original size, except for **vector images**.
	- 3. use the correct **resolution(分辨率)**.
- ```<figure>``` is used to containn images and their caption(題目). (supported by HTML5)
- ```<figcaption>``` is used to contain the caption. (supported by HTML5)

```html
<figure>
	<img src="images/home.jpg" alt="a home" title="a home"/>
	<br />
	<figcaption>Home</figcaption>
</figure>
```

