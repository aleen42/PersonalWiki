## Variables [Back](./../less.md)

### 1. Variable Interpolation (內插)

How about using variables despite of only values, such as selector names, property names, URLS and `@import` statements.

For selectors, we can code like this:

```less
/** Variables */
@my-selector: banner;

/** Usage */
.@{my-selector} {
    font-weight: bold;
    line-height: 40px;
    margin: 0 auto;
}
```

As for URLs:

```less
/** Variables */
@images: '../img';

/** Usage */
.item {
    background-image: url('@{images}/white-sand.png');
}
```

When it comes to `@import` statements:

```less
/** Variables */
@themes: '../../src/themes';

/** Usage */
@import '@{themes}/tidal-wave.less';
```
