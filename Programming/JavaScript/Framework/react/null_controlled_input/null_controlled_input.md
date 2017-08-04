## Value of null for Controlled Input [Back](./../react.md)

Specifying the `value` prop on a [controlled component](https://aleen42.github.io/PersonalWiki/Programming/JavaScript/Framework/react/forms/forms.html#controlled-components) prevents the user from changing the input unless you desire so.

In this case, you might have accidentally set value to `undefined` or `null`.

The snippet below shows this phenomenon; after a second, the text becomes editable.

{%ace edit=false, lang='jsx', theme='tomorrow'%}
ReactDOM.render(<input value="hi" />, mountNode);

setTimeout(function() {
    ReactDOM.render(<input value={null} />, mountNode);
}, 1000);
{%endace%}