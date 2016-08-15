## Expose Component Functions [Back](./../react.md)

There's another (uncommon) way of [communicating between components](./../communication_between_components/communication_between_components.md): **simply expose a method on the child component for the parent to call**.

Say a list of todos, which upon clicking get removed. If there's only one unfinished todo left, animate it:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
{%endace%}