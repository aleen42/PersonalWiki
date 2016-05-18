## Strict Mode [Back](./../JavaScript.md)

Strict Mode(嚴格模式) is a way in ES5 to *opt in* to a restricted variant of JavaScript.Browsers not supporting strict mode will run strict mode code with different behavior from browsers that do, so don't rely on strict mode without feature-testing for support for the relevant aspects of strict mode.

Strict Mode has made some changes to normal semantics:
- Strict mode eliminates(消除) some JavaScript silent errors by changing them to throw errors.
- Strict mode fixes mistakes that make it difficult for JavaScript engines to perform optimization: strict mode code can sometimes be made to run faster than identical code that's not strict mode.
- Strict mode prohibits(禁止) some syntax likely to be defined in future versions of ECMAScript.

#### Use Strict Mode in a script

Just add a line of `use strict;` like:

```js

```
