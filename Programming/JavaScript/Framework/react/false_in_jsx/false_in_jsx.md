## False in JSX [Back](./../react.md)

In React, `false` renders different things in different situation:

as `id="false`:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(
    <div id={false} />,
    document.getElementById('content')
);
{%endace%}