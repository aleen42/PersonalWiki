## If-Else in JSX [Back](./../react.md)

In React, `if-else` is not work inside JSX.

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div id={if (condition) { 'msg' } }></div>,
    document.getElementById('conten')
)
{%endace%}