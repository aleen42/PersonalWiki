## Variables [Back](./../less.md)

### 1. Variable Interpolation (內插)

How about using variables despite of only values, such as selector names, property names, URLS and `@import` statements.

#### 1.1 Selectors

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

#### 1.2 URLs

```less
/** Variables */
@images: '../img';

/** Usage */
.item {
    background-image: url('@{images}/white-sand.png');
}
```

#### 1.3 Import Statements

```less
/** Variables */
@themes: '../../src/themes';

/** Usage */
@import '@{themes}/tidal-wave.less';
```

#### 1.4 Properties

```less
/** Variables */
@property: color;

/** Usage */
.widget {
    @{property}: #0ee;
    background-@{property}: #999;
}
```

#### 1.5 Variable Names

```less
@fnord: "I am fnord.";
@var: "fnord";
content: @@var;
```
