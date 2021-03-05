## Bundle Style [Back](../webpack.md)

Recently, I have met a requirement that using Webpack to bundle styles rather than using work-flow tools like Grunt, or Gulp to build through tasks. Why? As a project becomes larger and larger, we are always confused with managing style bundles as there are a lot of components. Using work-flow tools like Grunt, or Gulp, we can only simply build styles with pre-compiler style tools like Less, or Sass, into one large file, or split into several chunks and load it at first. It means that DOM rendering needs styles to be loaded at first, sometimes which is a quite big overload.

With Webpack bundling, we don't actually import any styles until certain components are mounted as user interactions. Here, I aim to note the process of migrating from using Gulp to using Webpack through this document.

Before that, there are some specific versions of dependencies around this project:


| Dependency                         | Version |
|:-----------------------------------|:--------|
| Webpack                            | 4.4.1   |
| less-loader                        | 4.1.0   |
| postcss-loader                     | 2.1.6   |
| postcss-opacity                    | 5.0.0   |
| autoprefixer                       | 8.2.0   |
| css-loader                         | 1.0.0   |
| style-loader                       | 0.21.0  |
| optimize-css-assets-webpack-plugin | 5.0.0   |
| mini-css-extract-plugin            | 0.4.1   |
| html-webpack-plugin                | 3.0.7   |

Now, here we are!

### 1. Structures

Before migrating, the most important thing I did was to adjust the structure of the project base on components, which was based on one folder before, named with `style`. It was really a mess that so many dotted to code, in order to access style of each module and component, when we put all styles into one folder named with `style`, even if we organized them with corresponding structure of modules and components. `../../../../xxx/style.less`, well, how many levels of folder we needed to know so that we could access the right file? In modern front-end developing, components are actually a helpful concept, especially when we use React, or Vue:

> src

>> components

>>> dialog

>>>> index.js

>>>> index.less

>>>> index.tpl.html

>>> table

>>> list

### 2. Loaders

Then, after adjustment, the first step to do is to configure loaders so that Webpack knows how to require styles and build them into bundles. Less was the CSS pre-compiler we chose before, and if we want to bundle in Webpack, `less-loader` is what we need. After parsing through this loader, I have set up a loader before `css-loader`, which is `postcss-loader`. This loader can provided us some tools for transformations of CSS. For instance, to feature opacity under IE8, we need `postcss-opacity` plugin to add corresponding `filter` property automatically during bundling. In additional, some CSS prefixers like `-webkit`, or `-ms` should be added to support crossing browser platforms, and I hope that such a task can be assigned to `autoprefixer` plugin.

`style-loader` is another helpful loader used for adding CSS to the DOM via appending `<style>` tag into HTML. However, the position of entry has resulted in a problem that injected styles has been appended after some static styles, like skin styles, which are still built by Gulp. It means that skin styles cannot overwrite the default style of some components. Fortunately, `style-loader` has provided us a useful option, named `insertAt`. (the option is mainly used for specifying the position where we want to inject styles bundled with Webpack)

### 3. FOUC

A flash of unstyled content ([FOUC](https://en.wikipedia.org/wiki/Flash_of_unstyled_content) , a.k.a flash of unstyled text or FOUT) is a common problem arisen when we use Webpack to bundle styles. As we load styles during entry, styles will be loaded asynchronously in order to not block the rendering of DOM. However, unstyled DOM should render with a messy structure during a flash of interval. To work around this problem, `mini-css-extract-plugin` was my choice, as we have used Webpack@4.x. If you are using Webpack@3.x or older, you can use `extract-text-webpack-plugin` instead. They are both functionally same when we use them to extract specific CSS. How to solve FOUC? Just extract styles of initial structure into a Less file, like `entry.less`, and require it with a single entry. And then, set up a configuration to bundle this entry alone with `MiniCSSExtractPlugin.loader`, replacing `style-loader`, and exclude this entry outside normal style bundling. After all, the most important thing is to use `html-webpack-plugin` to inject link for synchronous loading, via `jspf`.

```js
/** webpack.config.js */
const MiniCSSExtractPlugin = require('mini-css-extract-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const WebpackConfig = {
    entry: {
        entry_style: 'xxx/entry.js',
    },
    plugins: [
        new MiniCSSExtractPlugin({filename : '[name].css' }),
    ],
    module: {
        rules: [
            {
                test: 'entry\.less$',
                use: [MiniCSSExtractPlugin.loader, 'css-loader', 'postcss-loader', 'less-loader'],
            }, 
            {
                test: '\.less$',
                use: ['style-loader', 'css-loader', 'postcss-loader', 'less-loader'],
            }, 
        ],
    },
};

Object.entries(WebpackConfig.entry).forEach(([entryId, ]) => {
    WebpackConfig.plugins.push(new HtmlWebpackPlugin({
        filename: `${entryId.substr(1)}.jspf`,
        templateContent({webpack}) {
            // language=HTML
            // style entry
            // export <link /> directly
            if (entryId.endsWith('_style')) {
                return `<link rel="stylesheet" type="text/css" href="${webpack.publicPath}${entryId.substr(1)}.css" />`;
            }
        },        
    }));
});

module.exports = WebpackConfig;
```

Then, inject `jspf` via entry:

```html
<!doctype html>
<html lang="en">
<head>
    <%@ include file="/bundle/js/entry_style.jspf" %>
</head>
</html>
```
