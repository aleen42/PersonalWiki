## JSX Gotchas [Back](./../react.md)

JSX looks like HTML but there are some important differences, and this chapter has introduced some.

#### HTML Entities

If we want to insert a literl text in HTML, you may write as followed:

```jsx
<div>First &middot; Second</div>
```

But if you want to display within dynamic content, you may find an issue that **React escapes all the strings you are displaying in order to prevent a wide range of XSS attacks by default**.

```jsx
/** bad display： "First &middot; Second" */
var div = <div>{'First &middot; Second'}</div>;
```

Solutions:

i. use UTF-8 and make sure the file is saved as UTF-8.

```jsx
var div = <div>{'First · Second'}</div>;
```

ii. find the unicode number corresponding to the entity.

```jsx
var div = <div>{'First \u00b7 Second'}</div>;
var div2 = <div>{'First ' + String.fromCharCode(183) + ' Second'}</div>;
```

iii. use mixed arrays with strings and JSX elements. Each JSX element in the array needs a unique key.

```jsx
var div = <div>{['First ', <span key="middot">&middot;</span>, ' Second']}</div>
```

iv. insert raw HTML directly.

```jsx
var div = <div dangerouslySetInnerHTML={ { __html: 'First &middot; Second' } }</div>
```

#### Custom HTML Attributes

If you pass properties to native HTML elements that do not exist in the HTML specification, React will not render them. If you want to use a custom attribute, you should prefix it with `data-`.

```jsx
var div = <div data-custom-attribute="foo" />;
```

However, arbitrary attributes are supported on custom elements (those with a hyphen(連字符) in the tag name or an `is="..."` attribute).

```jsx
var xMyComponent = <x-my-component custom-attribute="foo" />;
```

[Web Accessibility](http://www.w3.org/WAI/intro/aria) attributes starting with `aria-` will be rendered properly.

```jsx
var div = <div aria-hidden={true} />;
```