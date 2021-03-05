## Resolve? [Back](../webpack.md)

As the title asks, what we need to resolve? In most cases, the answer in JavaScript is modules' paths. Webpack has provided us a configuration object, named with `resolve`, to support for Module Resolution. For instance, what if we want to require a module named `lodash` in our projects, we can specify this so-called `resolve` object to tell Webpack where to look for such a module, like the folder `node_modules`. More configuration details can be checked at [the official document](https://webpack.js.org/configuration/resolve), whil here I mainly aim to describe how we can use such a feature to work more in our projects.

### Differences since Webpack 2

`resolve` features have been supported since Webpack 1, and as Webpack 2 released, there are two main differences we may need to focus on. The one is that it has not been able to specify empty string as an extension in `resolve.extensions` since the Version 2.

```js
/** Webpack 1 */
/** webpack.config.js */
module.exports = {
    /** ... */
    resolve: {
        extensions: ['', '.js', '.css'],  
    },
};
````

After Webpack 2:

```js
/** Webpack 2 */
/** webpack.config.js */
module.exports = {
    /** ... */
    resolve: {
        extensions: ['.js', '.css'],  
    },
};
```

It means that you cannot resolve a module file with no extension name if you use Webpack 2 or a later version.

The second one is that `resolve.modulesDirectories` has been renamed as `resolve.modules` since Webpack 2.

### Enhancement with using `resolve`

As a module resolution feature provided by Webpack, `resolve` can lead us to enhance our projects especially when they are large. For example, using `resolve.alias` to create aliases for common used modules, the following snippet won't becomes a disaster:

```js
/** wow, so many dotted/ */
const Email = require('../../../../util/email');
const Html = require('../../../../util/html');
const Dialog = require('../../../../components/dialog');
const Loading = require('../../../../components/loading');
```

With the structure of folders growing deeper and deeper, it is extremely confusing to calculate the number of dotted accessing without any IDE helpers. How about creating two aliases for `util` and `components`? The script should be much more elegant than before:

```js
/** webpack.config.js */
module.exports = {
    alias: {
        util: `${root}/frameworks/util`,
        components: `${root}/src/components`,
    },
};
```

```js
const Email = require('util/email');
const Html = require('util/html');
const Dialog = require('components/dialog');
const Loading = require('components/loading');
```

However, as more and more aliases have been defined in the future, we may meat the case when there are so many aliases defined under a same folder.

```js
/** webpack.config.js */
module.exports = {
    alias: {
        util: `${root}/src/util`,
        components: `${root}/src/components`,
        view: `${root}/src/view`,
        widgets: `${root}/src/widgets`,
        configurations: `${root}/src/configurations`,
        /** more and more ... */
    },
};
```

To work around this, we can specify `resolve.modules` with an array to tell Webpack what directories should be searched when resolving modules, like `node_modules`:

```js
module.exports = {
    alias: {
        util: `${root}/src/util`,
    },
    modules: [`${root}/src/`, 'node_modules'],
};
```

And then, it acts like all defined aliases above. However, there are two coins for everything, and what we need to concern about is conflicts risen from same named folders. For example, some libraries will add `util@0.10.3` as their dependencies like `Karma` and `Webpack`. It means that, if you only specify local `util` with `resolve.modules`, Webpack won't look up the actual `util` for you as it may looks it up in `node_modules`. That's why we only specify it alone with `resolve.alias`.
