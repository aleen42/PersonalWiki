## Strict Mode [Back](./../JavaScript.md)

Strict Mode(嚴格模式) is a way in ES5 to *opt in* to a restricted variant of JavaScript.Browsers not supporting strict mode will run strict mode code with different behavior from browsers that do, so don't rely on strict mode without feature-testing for support for the relevant aspects of strict mode.

Strict Mode has made some changes to normal semantics:
- Strict mode eliminates(消除) some JavaScript silent errors by changing them to throw errors.
- Strict mode fixes mistakes that make it difficult for JavaScript engines to perform optimization: strict mode code can sometimes be made to run faster than identical code that's not strict mode.
- Strict mode prohibits(禁止) some syntax likely to be defined in future versions of ECMAScript.

#### Use Strict Mode in a script

Just add a line of `use strict;` like:

```js
"use strict";
/** ... */
```
### Usages

#### Converting mistakes into errors

First, strict mode makes it impossible to accidentally create global variables. In normal JavaScript mistyping a variable in an assignment creates a new property on the global object and continues to "work" (although future failure is possible: likely, in modern JavaScript). Assignments which would accidentally create global variables instead throw in strict mode:

```js
"use strict";
mistypedVaraible = 17;  /** 
                         * Assuming a global variable mistypedVariable exists
                         * this line throws a ReferenceError due to the 
                         * misspelling of variable
                         */
```

Second, strict mode makes assignments which would otherwise silently fail throw an exception.

```js
"use strict";

/** Assignment to a non-writable property */
var obj1 = {};
Object.defineProperty(obj1, "x", {
    value: 42,
    writable: false
});
/** throws a TypeError */
obj1.x = 9;

/** Assignment to a getter-only property */
var obj2 = {
    get x() { return 17; }
};
/** throws a TypeError */
obj2.x = 5;

/** Assignment to a new property on a non-extensible object */
var fixed = {};
Object.preventExtensions(fixed);
/** throws a TypeError */
fixed.newProp = 'ohai';
```

Third, strict mode makes attempts to delete undeletable properties throw (where before the attempt would simply have no effect):

```js
"use strict";
/** throws a TypeError */
delete Object.prototype;
```

Fourth, strict mode prior to Gecko 34 requires that all properties named in an object literal be unique. (No longer the case in ES6: [bug 1041128](https://bugzilla.mozilla.org/show_bug.cgi?id=1041128))

```js
"use strict";
/** throws a SyntaxError */
var obj = {
    p: 1,
    p: 2
};
```

Fifth, strict mode requires that function parameter names be unique.

```js
/** throws a SyntaxError */
function duplicate(a, b, a) {
    "use strict";
    return a + b + a;
}
```

Sixth, strict mode in ECMAScript 5 forbids octal syntax. Octal syntax isn't part of ECMAScript 5, but it's supported in all browsers by prefixing the octal number with a zero: 0644 === 420 and "\045" === "%". In ECMAScript 6 Octal number is supported by prefixing a number with "0o". i.e.

```js
/** supported in ES6 */
var a = 0o10;
```

Seventh, strict mode in ECMAScript 6 forbids setting properties on primitive values:

```js
"use strict";
/** throws a TypeError */
false.true = '';
/** throws a TypeError */
(14).sell = true;
/** throws a TypeError */
'abc'.what = 'what';
```

#### Simplifying variable uses

First, strict mode prohibits `with`. The problem with with is that any name inside the block might map either to a property of the object passed to it, or to a variable in surrounding (or even global) scope, at runtime: it's impossible to know which beforehand. Strict mode makes with a syntax error, so there's no chance for a name in a `with` to refer to an unknown location at runtime:


