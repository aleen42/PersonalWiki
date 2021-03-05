## Tree Shaking [Back](../webpack.md)

With large sizes of JavaScript codes, developers usually split them into modules, easily resulting in unused code. Tree shaking is a way to help us optimize bundles by eliminating any unreached code.

```js
/** util.js */
export function add(x, y) { return x + y; }
export function mul(x, y) { return x * y; }
```

For instance, if we only require certain methods like `add()` in the following snippet:

```js
import {add} from './util';
add(1, 2);
```

With tree shaking enabled, the final bundle will eliminate the implementation of `mul` methods. So how does tree shaking work?

Such a concept has been arisen during 1990s, but it has only been able to work with JavaScript since the introduction of ES modules. Why? Because it is not static within CommonJS modules, where `require()` syntax can be used dynamically:

```js
const resources = require(`locale_${type}`);
```

In other words, without running code, the bundle tools cannot determine which modules will be needed. In ES modules, `import()` syntax has made it static:

```js
/** cannot run import resources from `locale_${type}` */
import resources_en_US from 'locale_en_US';
import resources_zh_CN from 'locale_zh_CN';

const resources = this[`resources_${type}`];
```

However, tree shaking cannot entirely tell which code is really unused, as some code performs some actions like shimming or registering. It means that there is "side effects", which we need to work around manually by specifying. With webpack configurations, the following case can be considered:

```js
/** webpack.config.js */
module.exports = {
    /** ... */
    mode: 'production', /** enable tree shaking */
    sideEffects: [
        './src/polyfill/*.js', /** manual workarounds */
    ],
    /** ... */
};
```
