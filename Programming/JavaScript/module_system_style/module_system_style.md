## Modular System Style [Back](./../JavaScript.md)

Today's websites are evolving into web apps:

- More and more JavaScript is being used.
- Modern browsers are offering a wider range of interfaces.
- Fewer full page reloads → even more code in a page.

As a result there is **a lot of code** on the client side!

Module systems offer the option to split your code base into modules.

### Style

There are multiple standards for how to define dependencies and export modules:

- `<script>`-tag style (without a modular system)
- CommonJS
- AMD
- ES Harmony
- ...

#### 1. `<script>`-tag style

```html
<script src="module1.js"></script>
<script src="module2.js"></script>
<script src="libraryA.js"></script>
<script src="module3.js"></script>
```

Modules export an interface to the global object, i.e. the `window` object.

**Cons**

- Conflicts in the global object
- Order of loading can be refusing
- Hard to manage dependencies

#### 2. CommonJS: synchronous `require`

Use a synchronous `require` method to load a dependency and return an exported interface. A module can be exported by adding properties to the `exports` object or setting the value of `module.exports`.

```js
require('module');
require('./../file.js');
module.exports = {};
exports.doStuff = function () {};

/** require this module */
var DoStuff = require('./../doSuff.js').doStuff;
```

**Pros**

- Server-side modules can be reused
- Many existed modules (npm)
- Simple and easy to use

**Cons**

- Blocking calls do not apply well in networks.
- No parallel require of multiple modules

#### 3. AMD: aynchronous require

```js
require(['module', './../files.js'], function (module, file) {
    /** ... */
});

define('myModule', ['dependency1', 'dependency2'], function (d1, d2) {
    /** ... */
    return {};
});
```

**Pros**

- Fits the asynchronous request style in networks
- Parallel loading of multiple modules

**Cons**

- Coding overhead. Hard to read or write.

#### 4. ES Harmony

```js
import 'module';
export function doStuff() {}
module myModule {}
```

**Pros**

- [Static analysis](#static-analysis) is easy
- Futre-proof as ES standard

**Cons**

- Native browser support will take time
- Few existed module in this style

------

#### Static Analysis

Static Analysis means to find dependencies when compiling modules.

------

More details can read this [article](./../../../post/modular_js_with_style/modular_js_with_style.md).
