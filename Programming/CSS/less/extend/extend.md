## Extend [Back](./../less.md)

Extend is a pseudo-class which means to merge selector to what it references. For example:

```less
.item1 {
    &:extend(.item2);
    background: red;
}

.item2 {
    color: red;
}
```

The snippet above will be converted into such a css style:

```css
.item1 {
    &:extend(.item2);
    background: red;
}

.item2,
.item1 {
    color: red;
}
```

### 1.1 Extend Syantax

```less
.a:extend(.b) {}

/** the above block does the same thing as the below block */
.a {
    &:extend(.b);
}
```

```less
.c:extend(.d all) {
    // extends all instances of ".d" e.g. ".x.d" or ".d.x"
}
.c:extend(.d) {
    // extends only instances where the selector will be output as just ".d"
}
```

Despite of these syntax, you can also contain more than one selectors with comma as separators:


```less
.e:extend(.f, .g) {}
```
