## this.props.children undefined [Back](./../react.md)

You can't access the children of your component through `this.props.children`, which should only be the children being passed onto your component by the owner:

{%ace edit=false, lang='jsx', theme='tomorrow'%}

{%endace%}
