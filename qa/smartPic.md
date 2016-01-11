## a smart way to show a picture [Back](./qa.md)

- Here is a smart way to show a picture in a html web page. Only with some **CSS**, the picture will be displayed in a different way like the [**example**]().

#### 1. have the html files

```html
<div class="pic-container">
    <!-- the link of the picture you want to jump into -->
    <a href="">
        <div class="over">
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
    width: 100%;
    height: 150px;
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
    transition: transform 4s;
    -webkit-transition: transform 4s;
    transition-timing-function: ease-in-out;
    -webkit-transition-timing-function: ease-in-out;
}

.pic-container .over {
    position: absolute;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.7);
    z-index: 2;
    opacity: 0;
    transition: opacity 0.8s;
    -webkit-transition: opacity 0.8s;
    transition-timing-function: ease-in-out;
    -webkit-transition-timing-function: ease-in-out;
}

.pic-container .over .link-btn {
    width: 100%;
    height: 100%;
    position: absolute;
    background-position: center;
    background-repeat: no-repeat;
    background-size: auto 50%;
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

.pic-container:hover .shop {
    transform: scale(1.4, 1.4);
    -webkit-transform: scale(1.4, 1.4);
}

.pic-container:hover .over {
    opacity: 1;
}
```

<a href="#" style="left:200px;"><img src="./../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
