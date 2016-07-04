## JSX Gotchas [Back](./../react.md)

JSX looks like HTML but there are some important differences, and this chapter has introduced some.

#### HTML Entities

If we want to insert a literl text in HTML, you may write as followed:

```html
<div>First &middot; Second</div>
```

But if you want to display within dynamic content, you may find an issue that **React escapes all the strings you are displaying in order to prevent a wide range of XSS attacks by default**.

```js
/** bad display： "First &middot; Second" */
var div = <div>{'First &middot; Second'}</div>;
```

Solutions:

i. use UTF-8 and make sure the file is saved as UTF-8.

```js
var div = <div>{'First · Second'}</div>;
```

ii. find the unicode number corresponding to the entity:

```js
var div = <div>{'First \u00b7 Second'}</div>;
var div2 = <div>{'First ' + String.fromCharCode(183) + ' Second'}</div>;
```