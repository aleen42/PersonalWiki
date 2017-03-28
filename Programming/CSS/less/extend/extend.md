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
