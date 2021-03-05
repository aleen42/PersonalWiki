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
### Changes

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

```js
"use strict";
var x = 17;
/** throws a SyntaxError */
with (obj) {
    console.log(x); /** 
                     * If this weren't strict mode, would this be var x, or
                     * would it instead be obj.x?  It's impossible in general
                     * to say without running the code, so the name can't be
                     * optimized.
                     */
}
```

Second, [eval of strict mode code does not introduce new variables into the surrounding scope](http://whereswalden.com/2011/01/10/new-es5-strict-mode-support-new-vars-created-by-strict-mode-eval-code-are-local-to-that-code-only/). In normal code `eval("var x;")` introduces a variable x into the surrounding function or the global scope. In strict mode `eval` creates variables only for the code being evaluated, so `eval` can't affect whether a name refers to an outer variable or some local variable:

```js
var x = 17;
var evalX = eval('"use strict"; var x = 42; x');
console.assert(x === 17);
console.assert(evalX === 42);
```

Strict mode passing:

```js
function strict1(str) {
    "use strict";
    /** str will be treated as strict mode code */
    return eval(str);
}

function strict2(f, str) {
    "use strict";
    return f(str);  /**
                     * not eval(...): str is strict if and only
                     * if it invokes strict mode
                     */
}

function nonstrict(str){
    return eval(str);   /**
                         * str is strict if and only 
                         * if it invokes strict mode
                         */
}

strict1("'Strict mode code!'");
strict1("'use strict'; 'Strict mode code!'");
strict2(eval, "'Non-strict code.'");
strict2(eval, "'use strict'; 'Strict mode code!'");
nonstrict("'Non-strict code.'");
nonstrict("'use strict'; 'Strict mode code!'");
```

Third, strict mode forbids deleting plain names. delete name in strict mode is a syntax error:

```js
"use strict";

var x;
/** throws a SyntaxError */
delete x;
/** throws a SyntaxError */
eval("var y; delete y;");
```

#### Making `eval` and `arguments` simpler

First, the names `eval` and `arguments` can't be bound or assigned in language syntax. All these attempts to do so are syntax errors.

```js
"use strict";
/** throws a SyntaxError */
var eval;
/** throws a SyntaxError */
try { } catch (arguments) { }
```

Second, strict mode code doesn't alias properties of `arguments` objects created within it. In normal code within a function whose first argument is `arg`, setting `arg` also sets `arguments[0]`, and vice versa (unless no arguments were provided or `arguments[0]` is deleted). `arguments` objects for strict mode functions store the original arguments when the function was invoked. `arguments[i]` does not track the value of the corresponding named argument, nor does a named argument track the value in the corresponding `arguments[i]`.

```js
function f(a) {
    "use strict";
    a = 42;
    return [a, arguments[0]];
}

var pair = f(17);
console.assert(pair[0] === 42);
console.assert(pair[1] === 17);
```

Third, `arguments.callee` is no longer supported.

```js
"use strict";
var f = function () {
    return arguments.callee;
};
/** throws a TypeError */
f();
```

#### "Securing" Javascript

Strict mode makes it easier to write "secure" JavaScript.

First, the value passed as `this` to a function in strict mode is not forced into being an object (a.k.a. "boxed"). For a normal function, `this` is always an object: either the provided object if called with an `object-valued` this; the value, boxed, if called with a `Boolean`, `string`, or `number` this; or the global object if called with an `undefined` or `null` this. (Use [call](https://developer.mozilla.org/en-US/Web/JavaScript/Reference/Global_Objects/Function/call), [apply](https://developer.mozilla.org/en-US/Web/JavaScript/Reference/Global_Objects/Function/apply), or [bind](https://developer.mozilla.org/en-US/Web/JavaScript/Reference/Global_Objects/Function/bind) to specify a particular `this`.) Not only is automatic boxing a performance cost, but exposing the global object in browsers is a security hazard(危害), because the global object provides access to functionality that "secure" JavaScript environments must restrict.

```js
"use strict";
function fun() { return this; }
console.assert(fun() === undefined);
console.assert(fun.call(2) === 2);
console.assert(fun.apply(null) === null);
console.assert(fun.call(undefined) === undefined);
console.assert(fun.bind(true)() === true);
```

That means, among other things, that in browsers it's no longer possible to reference the `window` object through `this` inside a strict mode function.

Second, in strict mode it's no longer possible to "walk" the JavaScript stack via commonly-implemented extensions to ECMAScript. In normal code with these extensions, when a function `fun` is in the middle of being called, `fun.caller` is the function that most recently called `fun`, and `fun.arguments` is the arguments for that invocation of `fun`.

```js
function restricted() {
    "use strict";
    /** throws a TypeError */
    restricted.caller;
    /** throws a TypeError */
    restricted.arguments;
}

function privilegedInvoker() {
    return restricted();
}

privilegedInvoker();
```

Third, arguments for strict mode functions no longer provide access to the corresponding function call's variables. In some old ECMAScript implementations `arguments.caller` was an object whose properties aliased variables in that function. This is a security hazard because it breaks the ability to hide privileged values via function abstraction; it also precludes(阻斷) most optimization. For these reasons no recent browsers implement it. Yet because of its historical functionality, `arguments.caller` for a strict mode function is also a non-deletable property which throws when **set** or **retrieved**:

```js
"use strict";
function fun(a, b) {
    "use strict";
    var v = 12;
    /** throws a TypeError */
    return arguments.caller;
}

/** doesn't expose v (or a or b) */
fun(1, 2);
```

#### Paving the way(鋪路) for future ECMAScript versions

Future ECMAScript versions will likely introduce new syntax, and strict mode in ECMAScript 5 applies some restrictions to ease the transition.

First, in strict mode a short list of identifiers become reserved keywords. These words are `implements`, `interface`, `let`, `package`, `private`, `protected`, `public`, `static`, and `yield`. In strict mode, then, you can't name or use variables or arguments with these names.

Second, [strict mode prohibits function statements not at the top level of a script or function](http://whereswalden.com/2011/01/24/new-es5-strict-mode-requirement-function-statements-not-at-top-level-of-a-program-or-function-are-prohibited/). In normal code in browsers, function statements are permitted "everywhere". This is not part of ES5 *(or even ES3)!* It's an extension with incompatible semantics in different browsers. Future ECMAScript editions will hopefully specify new semantics for function statements not at the top level of a script or function. [Prohibiting such function statements in strict mode](http://wiki.ecmascript.org/doku.php?id=conventions:no_non_standard_strict_decls) "clears the deck" for specification in a future ECMAScript release:

```js
"use strict";
if (true) {
    /** throws a SyntaxError */
    function f() { }
    f();
}

for (var i = 0; i < 5; i++){
    /** throws a SyntaxError */
    function f2() { }
    f2();
}

/** kosher(合理的) */
function baz() {
    /** kosher(合理的) */
    function eit() { }
}
```

### See Also

- [Where's Walden? » New ES5 strict mode support: now with poison pills!](http://whereswalden.com/2010/09/08/new-es5-strict-mode-support-now-with-poison-pills/)
- [Where's Walden? » New ES5 strict mode requirement: function statements not at top level of a program or function are prohibited](http://whereswalden.com/2011/01/24/new-es5-strict-mode-requirement-function-statements-not-at-top-level-of-a-program-or-function-are-prohibited/)
- [Where's Walden? » New ES5 strict mode support: new vars created by strict mode eval code are local to that code only](http://whereswalden.com/2011/01/10/new-es5-strict-mode-support-new-vars-created-by-strict-mode-eval-code-are-local-to-that-code-only/)
- [JavaScript "use strict" tutorial for beginners.](http://qnimate.com/javascript-strict-mode-in-nutshell/)
- [John Resig - ECMAScript 5 Strict Mode, JSON, and More](http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/)
- [ECMA-262-5 in detail. Chapter 2. Strict Mode.](http://dmitrysoshnikov.com/ecmascript/es5-chapter-2-strict-mode/)
- [Strict mode compatibility table](http://kangax.github.io/compat-table/es5/#Strict_mode)
- [Transitioning to strict mode](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Strict_mode/Transitioning_to_strict_mode)