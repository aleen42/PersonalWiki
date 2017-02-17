## How to compare the equality of two elements [Back](./../underscore.md)

In underscore, there is a method called `_.isEqual()` to judge whether an element is equal to another. Before analysing this more complicated function, which has been implemented with around hundreds of lines, I would like to discuss when an element is actually equal to another. For example, `1` should be equal to `new Number(1)`, and `[1]` is also equal to `[1]` even if they are two different arrays.

For the expression `a === b`, there are two situations resulting in `true`

