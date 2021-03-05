## Overview [Back](./../less.md)

### 1. Variables

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

### 2. Mixins

Mixins are a way of including a bunch of properties from one rule-set into another rule-set.

```less
.bordered {
    border-top: dotted 1px black;
    border-bottom: solid 2px black;
}

#id {
    border: solid 1px black;
}
```

```less
#menu a {
    color: #111;
    .bordered;
}

.post a {
    color: red;
    .bordered;
    #id;
}
```

### 3. Nested Rules

Less gives you the ability to use nesting instead of, or in combination with cascading.

Like the following CSS:

```css
#header {
    color: black;
}
#header .navigation {
    font-size: 12px;
}
#header .logo {
    width: 300px;
}
```

We can code it with Less:

```less
#header {
    color: black;
    .navigation {
        font-size: 12px;
    }
    .logo {
        width: 30px;
    }
}
```

When bundling pseudo-selectors, you can use `&` to reference the current selector parent:

Like the following CSS:

```css
.clearfix {
    display: block;
    zoom: 1;
}

.clearfix:after {
    content: " ";
    display: block;
    font-size: 0;
    height: 0;
    clear: both;
    visibility: hidden;
}
```

We can code it with Less:

```less
.clearfix {
    display: block;
    zoom: 1;
    &:after {
        content: " ";
        display: block;
        font-size: 0;
        height: 0;
        clear: both;
        visibility: hidden;
    }
}
```

When it comes to directives like `@media` or `@keyframe`, we can also use this rule to nest them:

Like the following CSS:

```css
@media screen {
    .item {
        color: green;
    }
}

@media screen and (min-width: 768px) {
    .item {
        color: red;
    }
}

@media tv {
    .item {
        color: black;
    }
}
```

We can code it with Less:

```less
.item {
    @media screen {
        color: green;
        
        @media (min-width: 768px) {
            color: red;
        }
    }
    
    @media tv {
        color: black;
    }
}
```

Remaining non-conditional directives, for example `@font-face` or `@keyframes`, are bubbled up too. Their bodies do not change:

```less
#a {
    color: blue;
    
    @font-face {
        src: made-up-url;
    }
    
    padding: 2;
}
```

Will be converted into CSS like this:

```css
#a {
    color: blue;
}

@font-face {
    src: made-up-url;
}

#a {
    padding: 2;
}
```

### 4. Operations

Arithmetical operations `+`, `-`, `*`, `/` can operate on any number, color or variable. If possible, these operations will firstly convert them into numbers, like `px`, `cm`, or `%`.

```less
@conversion-1: 5cm + 10mm; /** => 6cm */
@conversion-2: 2 - 3cm - 5mm; /** => -1.5cm */

@incompatible-conversion: 2 + 5px - 3mm; /** => 4px */

/** variables */
@base: 5%;
@filter: @base * 2; /** => 10% */
@other: @base + @filter; /** => 15% */
```

Multiplication and division do not convert numbers, as it would not be meaningful in most cases.

```less
@base: 2cm * 3mm; /** => 6cm */
```

In the case when calculating color values, there should be cases in which values are bigger than `ff` or smaller than `00`. They will be rounded to either `ff` or `00`. Alpha values calculating is same as color values, like `1.1` will be rounded to `1.0`.

```less
@color: #224488 / 2; /** => 112244 */

.item {
    background-color: @color + #111; /** => 223355 */
}
```

### 5. Functions 

Less provides a variety of functions which transform colors, manipulate strings and do maths.

```less
@base: #f04615;
@width: 0.5;

.class {
    width: percentage(@width); /** => 50% */
    color: saturate(@base, 5%);
    background-color: spin(lighten(@base, 25%), 8);
}
```

### 6. Namespaces and Accessors

Sometimes, we can use Less to bundle some mixins and variables under a rule block like `#bundle` for later reuse:

```less
#bundle {
    .button {
        display: block;
        border: 1px solid black;
        background-color: grey;
        &:hover {
            background-color: white
        }
    }
    .tag {
        display: inline-block;
    }
}
```

Then if we want to reuse the rule of `.button`, we can code like this:

```less
.item {
    color: red;
    #bundle > .button;
}
```

### 7. Scope

Variables and mixins are first looked for locally, and if they aren't found, the compiler will look in the parent scope, and so on.

```less
@var: red;

#page {
    @var: white;
    #header {
        color: @var; /** => white */
    }
}
```

The difference is they do not have to be declared before being used:

```less
@var: red;

#page {
    #header {
        color: @var; /** => white */
    }
    @var: white;
}
```

### 8. Importing

Importing works pretty much as expected. You can import a `.less` file, and all the variables in it will be available.

```less
@import "library"; /** library.less */
@import "typo.css";
```
