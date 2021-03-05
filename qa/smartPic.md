## How to make a smart picture showing with css [Back](./qa.md)

- Here is a smart way to show a picture in a html web page. Only with some **CSS**, the picture will be displayed in a different way like the [**example**](http://aleen42.github.io/example/smartPic/index.html).

#### 1. have the html files

```html
<div class="pic-container">
    <!-- the link of the picture you want to jump into -->
    <a href="">
        <div class="over">
            <!-- set the over picture icon -->
            <div class="link-btn" style="background-image: url();"></div>
        </div>
    </a>
    <!-- set the picture src -->
    <div class="shop" style="background-image: url();"></div>
</div>
```

#### 2. set the css

```css
.pic-container {
	margin-top: 2%;
	display: inline-block;
	width: 75%;
	height: 300px;
	overflow: hidden;
	position: relative;
	cursor: pointer;
	z-index: 1;
}

.pic-container .shop {
	width: 100%;
	height: 100%;
	position: absolute;
	background-position: center;
	background-repeat: no-repeat;
	background-size: cover;
	transition: transform 1.5s;
	-webkit-transition: transform 1.5s;
}

.pic-container .over {
	position: absolute;
	width: 100%;
	height: 100%;
	background-color: rgba(0, 0, 0, 0.7);
	z-index: 2;
	opacity: 0;
	transition: opacity 0.4s;
	-webkit-transition: opacity 0.4s;
}

.pic-container .over .link-btn {
	width: 100%;
	height: 100%;
	position: absolute;
	background-position: center;
	background-repeat: no-repeat;
	background-size: auto 15%;
	z-index: 3;
}

.pic-container .over .product-name {
	color: #fff;
	position: absolute;
	bottom: 3%;
	text-align: center;
	width: 100%;
	font-size: 1.2em;
	overflow: hidden;
	white-space: nowrap;
	text-overflow: ellipsis;
}

.pic-container .over .product-price {
	color: #ffa200;
	position: absolute;
	top: 3%;
	right: 3%;
	font-size: 1.5em;
}

.pic-container .line {
	height: 1px;
	background-color: white;
	width: 40%;
	left: 30%;
	position: absolute;
	transition: transform 1.5s;
	-webkit-transition: transform 1.5s;
}

.pic-container .ln1 {
	top: 40%;
}

.pic-container .ln2 {
	bottom: 40%;
	transition-delay:  0.2s;
	-webkit-transition-delay:  0.2s;
}

.pic-container:hover .shop {
	transform: scale(1.04, 1.04);
	-webkit-transform: scale(1.04, 1.04);
}

.pic-container:hover .over {
	opacity: 1;
}

.pic-container:hover .line {
	transform: scale(0.2, 1);
	-webkit-transform: scale(0.2, 1);
}
```
