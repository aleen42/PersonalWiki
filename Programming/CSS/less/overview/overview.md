## Overview [Back](./../less.md)

### Variables

```less
@nice-blue: #5B83AD;
@light-blue: @nice-blue + #111;

#header {
    color: @light-blue;
}
```

```css
#header {
    color: #6c94be;
}
```

***Note that variables are actually "constants" in that they can only be defined once.***

### Mixins

Mixins are a way of including a bunch of properties from one rule-set into another rule-set.

```less
.bordered {
    border-top: dotted 1px black;
    border-bottom: solid 2px black;
}
```
