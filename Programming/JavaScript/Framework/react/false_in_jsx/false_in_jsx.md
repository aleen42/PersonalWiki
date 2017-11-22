## False in JSX [Back](./../react.md)

In React, `false` renders different things in different situation:

as `id="false"`:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div id={false} />,
    document.getElementById('content')
);
{%endace%}

as string input value:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <input value={false} />,
    document.getElementById('content')
);
{%endace%}

as no child:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div>{false}</div>,
    document.getElementById('content')
);
{%endace%}

The reason why this one does not render as the string `"false"` or as a `div` child is to allow the more common use-case: `<div>{x > 1 && 'You have more than one item'}</div>`.