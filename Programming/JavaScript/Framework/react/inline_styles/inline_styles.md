## Inline Styles [Back](./../react.md)

In React, inline styles are not specified as a string, but an object like this:

```jsx
var divStyle = {
    color: 'black',
    backgroundImage: 'url(' + imgUrl + ')',
    WebkitTransition: 'all',
    msTransition: 'all'
};

ReactDOM.render(
    <div style={divStyle} >Hello World!</div>,
    document.getElementById('content')
);
```

Style keys are **camelCased** in order to be consistent with accessing the properties on DOM nodes from JS. However, Vendor prefixes [other than `ms`](http://www.andismith.com/blog/2012/02/modernizr-prefixed/) should begin with a capital letter. This is why `WebkitTransition` has an uppercase **"W"**.