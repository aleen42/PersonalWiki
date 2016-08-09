## Shorthand for Specifying Pixel Values in style props [Back](./../react.md)

When specifying a pixel value for your inline `style` prop, React automatically appends the string "px" for you after your number value, so this works:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
/** rendered as "height:10px" */
var divStyle = {height: 10};
ReactDOM.render(
    <div style={divStyle}>Hello World!</div>,
    document.getElementById('content')
);
{%endace%}

