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
