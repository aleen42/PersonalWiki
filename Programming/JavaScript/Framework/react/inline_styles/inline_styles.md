## Inline Styles [Back](./../react.md)

In React, inline styles are not specified as a string, but an object like this:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
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
{%endace%}