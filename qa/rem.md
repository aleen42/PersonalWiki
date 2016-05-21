## How to use powerful rem with responsive web app development [Back](./qa.md)

### What is rem? and the difference between em?

**rem(font size of the root element)** is a relative unit of font size in the root element. In an other words, If the root element `html` in a HTML document has set the attribute `font-size` as follow:

```css
html {
    font-size: 100px;
}
```

then, 1 rem means 100px and 0.5 rem of course means 50px.

**em(font size of the element)** is also a relative unit of font size. The variety from rem is that em is relative to its parent elements. For example:

```html
<div class="box box__parent">
    <div class="box box__children">
    </div>
</div>
```

```css
.box__parent {
    font-size: 100px;
}
```

what you can see is that the font size of the parent box is 100x, and then 0.5em should be 50px for the children box.

### Powerful value in developing web app

Currently, there are many solutions about the problem of responsive web in a mobile. Some will directly set a absolute value of width in an element, and some will use percent value to set width and the height will be a fixed value. Anyway, here I will have a short description of these methods and have a comparison with rem.

#### Flow Layout

Set width with percent values and set height with fixed values

```css
.box__element {
    width: 28%;
    height: 20px;
}
```

Shortcut:

This solution will result in plenty of responsive problems, and limit the designers' design. With different width of screen, elements in this way should be scaled with different width, but have the same height. Therefore, designers should only consider about elemnts that can be stretched transversely.