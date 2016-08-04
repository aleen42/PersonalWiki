## If-Else in JSX [Back](./../react.md)

In React, `if-else` is not work inside JSX.

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div id={if (condition) { 'msg' } }></div>,
    document.getElementById('conten')
)
{%endace%}

If we code a JSX like the below one, you will find that the converted JavaScript will have something wrong.

{%ace edit=false, lang='js', theme='tomorrow'%}
ReactDOM.render(
    React.createElement('div', { id: if (condition) { 'msg' } }),
    document.getElementById('conten')
)
{%endace%}

A ternary expression (三角表達式) will be a good choice to solve this problem:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div id={condition ? 'msg' : ''}></div>,
    document.getElementById('conten')
)
{%endace%}

If we code a JSX like the below one, you will find that the converted JavaScript will have something wrong.

{%ace edit=false, lang='js', theme='tomorrow'%}
ReactDOM.render(
    React.createElement('div', { id: condition ? 'msg' : '' }),
    document.getElementById('conten')
)
{%endace%}
