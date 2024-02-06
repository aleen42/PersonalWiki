## Shorthand for Specifying Pixel Values in style props [Back](./../react.md)

When specifying a pixel value for your inline `style` prop, React automatically appends the string "px" for you after your number value, so this works:

```jsx
/** rendered as "height:10px" */
var divStyle = {height: 10};
ReactDOM.render(
    <div style={divStyle}>Hello World!</div>,
    document.getElementById('content')
);
```

Sometimes you **do** want to keep the CSS properties unitless. Here's a list of properties that won't get the automatic "px" suffix:

- animationIterationCount
- boxFlex
- boxFlexGroup
- boxOrdinalGroup
- columnCount
- fillOpacity
- flex
- flexGrow
- flexPositive
- flexShrink
- flexNegative
- flexOrder
- fontWeight
- lineClamp
- lineHeight
- opacity
- order
- orphans
- stopOpacity
- strokeDashoffset
- strokeOpacity
- strokeWidth
- tabSize
- widows
- zIndex
- zoom
