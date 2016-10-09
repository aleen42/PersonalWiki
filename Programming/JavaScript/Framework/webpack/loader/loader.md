## Loader [Back](./../webpack.md)

### Description

Loaders are transformations that are applied on a resource file of your app. For example, you can use loaders to tell webpack to load CoffeeScript or JSX

### Usage

There are some ways to use loaders:

- explicit in the require statement
- configured via configuration
- configured via CLI

Loader can be passed query parameters via a query string (just like in the web). The query string is appended to the loader with `?`. i.e. `url-loader?mimetype=image/png`.

#### Loaders in require

> **Note:**A void using this, if at all possible, if you intend your scripts to be environment agnostic (node.js and browser). Use the configuration convention for specifying loaders.

Just separate loaders from resource with `!`. Each part is resolved relative to the current directory.

```js
require("./loader!./dir/file.txt");
// => uses the file "loader.js" in the current directory to transform
//    "file.txt" in the folder "dir".

require("jade!./template.jade");
// => uses the "jade-loader" (that is installed from npm to "node_modules")
//    to transform the file "template.jade"
//    If configuration has some transforms bound to the file, they will still be applied.

require("!style!css!less!bootstrap/less/bootstrap.less");
// => the file "bootstrap.less" in the folder "less" in the "bootstrap"
//    module (that is installed from github to "node_modules") is
//    transformed by the "less-loader". The result is transformed by the
//    "css-loader" and then by the "style-loader".
//    If configuration has some transforms bound to the file, they will not be applied.

require("url-loader?mimetype=image/png!file.png");
```

#### Configuration

```js
module.exports = {
    entry: './src/app.js',
    output: {
        path: './bin',
        filename: 'app.bundle.js'
    },
    module: {
        loaders: [
            { test: /\.jade$/, loader: "jade" },
            // => "jade" loader is used for ".jade" files

            { test: /\.css$/, loader: "style!css" },
            // => "style" and "css" loader is used for ".css" files
            // Alternative syntax:
            { test: /\.css$/, loaders: ["style", "css"] },

            { test: /\.png$/, loader: "url-loader?mimetype=image/png" },
            /** or */
            {
                test: /\.png$/,
                loader: "url-loader",
                query: { mimetype: "image/png" }
            }
        ]
    }
};
```

#### CLI

```bash
webpack --module-bind jade --module-bind 'css=style!css' --module-bind "png=url-loader?mimetype=image/png"
```

### Lists of Loaders

#### basic

* [`json`](https://github.com/webpack/json-loader): Loads file as JSON
* [`hson`](https://github.com/kentcdodds/hson-loader): Loads HanSON file (JSON for Humans) as JSON object
* [`raw`](https://github.com/webpack/raw-loader): Loads raw content of a file (as utf-8)
* [`val`](https://github.com/webpack/val-loader): Executes code as module and consider exports as JavaScript code
* [`to-string`](https://github.com/gajus/to-string): Executes code as a module, casts output to a string and exports it
* [`imports`](https://github.com/webpack/imports-loader): Imports stuff to the module
* [`exports`](https://github.com/webpack/exports-loader): Exports stuff from the module
* [`expose`](https://github.com/webpack/expose-loader): Expose exports from a module to the global context
* [`script`](https://github.com/webpack/script-loader): Executes a JavaScript file once in global context (like in script tag), requires are not parsed.
* [`apply`](https://github.com/mogelbrod/apply-loader): Executes a exported JavaScript function, optionally with arguments, and exports its return value.
* [`callback`](https://github.com/Kreozot/callback-loader): Parses your JS, calls specified functions (which you implement in webpack context) and replaces them with the results
* [`if-loader`](https://github.com/friskfly/if-loader): This is a preprocesser for the webpack module bundler. It support the `if` directive,similar to C `#ifdef` .
* [`ifdef-loader`](https://github.com/nippur72/ifdef-loader): Preprocessor for .js/.ts files that allows conditional compilation via `// #if` and `// #endif`, while preserving sourcemaps.
* [`source-map`](https://github.com/webpack/source-map-loader): Extract `sourceMappingURL` comments from modules and offer it to webpack
* [`checksum`](https://github.com/naturalatlas/checksum-loader): Computes the checksum of a file
* [`null`](https://github.com/webpack/null-loader): Emits an empty module.
* [`cowsay`](https://github.com/nelix/cowsay-loader): Emits a module with a cowsay header.
* [`dsv`](https://github.com/wbkd/dsv-loader): Loads csv/tsv files.
* [`glsl`](https://github.com/makio64/shader-loader): Loads glsl files and support glsl-chunks.
* [`render-placement`](https://github.com/zackify/render-placement-loader): Adds React.render to your component for you (not very practical in most cases)
* [`xml`](https://github.com/gisikw/xml-loader): Loads XML as JSON.
* [`svg-react`](https://github.com/jhamlet/svg-react-loader): Load SVG files as JSX-ified React.createClass declarations.
* [`svg-url`](https://github.com/bhovhannes/svg-url-loader): Loads SVG file as utf-8 encoded data:URI string.
* [`svg-as-symbol`](https://github.com/bhovhannes/svg-as-symbol-loader): Wraps content of root element of source SVG file  inside `symbol` element and returns resulting markup.
* [`base64`](https://github.com/antelle/base64-loader): Loads file content as base64 string
* [`ng-annotate`](https://github.com/huston007/ng-annotate-loader): A loader to annotate dependency injections in `Angular.js` applications.
* [`node`](https://github.com/webpack/node-loader): Loads `.node` files that are produced using node-gyp.
* [`required`](https://www.npmjs.com/package/required-loader): Require a whole directory of trees in bulk. Require JS, Import CSS and imports stuff in it.
* [`icons`](https://www.npmjs.com/package/icons-loader) Generates iconfont from .svg files (uses gulp-iconfont)
* [`markup-inline`](https://www.npmjs.com/package/markup-inline-loader) Inline SVGs to HTML. It's very useful when applying icon font or applying CSS animation to SVG.
* [`block-loader`](https://www.npmjs.com/package/block-loader) Generic loader for rewriting only parts of files, based on content start/end delimiters.
* [`bundler-configuration`](https://www.npmjs.com/package/bundler-configuration-loader) Bundler configuration loader, a tool to include bundler configuration in the resulting build.
* [`console`](https://github.com/eedrah/console-loader): Prints the resolved require of webpack to the console.
* [`solc`](https://github.com/uzyn/solc-loader): Compiles Solidity code (`.sol`) and returns JavaScript objects with Application Binary Interface (ABI) and bytecode ready for deployment to Ethereum.
* [`web3`](https://github.com/uzyn/web3-loader): Deploys Ethereum VM bytecode and returns ready-to-use JS instances of deployed smart contracts. Also returns initialized Web3 object.
* [`includes`](https://github.com/hujinglin/includes-loader): Load any text file and support nested includes
* [`combine`](https://github.com/elliottsj/combine-loader): Combine results from multiple loaders into one object
* [`regexp-replace`](https://github.com/EventMobi/regexp-replace-loader): Replace RegExp matches with a string

#### packaging

* [`file`](https://github.com/webpack/file-loader): Emits the file into the output folder and returns the (relative) url.
* [`url`](https://github.com/webpack/url-loader): The url loader works like the file loader, but can return a Data Url if the file is smaller than a limit.
* [`extract`](https://github.com/peerigon/extract-loader): Prepares HTML and CSS modules to be extracted into a separate file (lean alternative to the ExtractTextWebpackPlugin).
* [`worker`](https://github.com/webpack/worker-loader): The worker loader creates a WebWorker for the provided file. The bundling of dependencies of the Worker is transparent.
* [`shared-worker`](https://github.com/mrtnbroder/shared-worker-loader): Like the worker loader, but for [Shared Workers](https://developer.mozilla.org/de/docs/Web/API/SharedWorker).
* [`serviceworker`](https://github.com/markdalgleish/serviceworker-loader): Like the worker loader, but designed for [Service Workers](http://www.w3.org/TR/service-workers).
* [`bundle`](https://github.com/webpack/bundle-loader): Wraps request in a `require.ensure` block (callback)
* [`promise`](https://github.com/gaearon/promise-loader): Wraps request in a `require.ensure` block (promise)
* [`async-module`](https://github.com/NekR/async-module-loader): Same as `bundle`, but provides a way to handle script loading errors. Wraps request in a `require.ensure` block (callback, errback)
* [`react-proxy`](https://github.com/webpack/react-proxy-loader): Code Splitting for react components.
* [`react-hot`](https://github.com/gaearon/react-hot-loader): Allows to live-edit React components while keeping them mounted and preserving their state.
* [`image`](https://github.com/tcoopman/image-webpack-loader): Compresses your images. Ideal to use together with `file` or `url`.
* [`img`](https://github.com/thetalecrafter/img-loader): Load and compress images with imagemin.
* [`base64-image`](https://www.npmjs.com/package/base64-image-loader): Load image as base64 string src
* [`responsive`](https://github.com/herrstucki/responsive-loader): Create multiple resized images for use with `srcset` and CSS media queries
* [`svgo`](https://github.com/pozadi/svgo-loader): Compresses SVG images using [svgo](https://github.com/svg/svgo) library
* [`svg-sprite`](https://github.com/kisenka/svg-sprite-loader): Like style-loader but for SVG: it creates a single SVG sprite from a set of images, appends it to DOM and returns relative `symbol` url to be used with svg's `<use>`.
* [`svg-fill`](https://github.com/kisenka/svg-fill-loader): Changes colors in SVG images. Useful when you embed SVG in CSS as background image and don't want to produce tons of identical files which only differ in their `fill` attributes.
* [`line-art`](https://github.com/tptee/line-art-loader): Inlines SVG files, converting all of its nodes to paths. Useful for line art animations in React components.
* [`baggage`](https://github.com/deepsweet/baggage-loader): Automatically require any resources related to the required one
* [`polymer`](https://github.com/JonDum/polymer-loader): Process HTML & CSS with preprocessor of choice and `require()` Web Components like first-class modules.
* [`uglify`](https://github.com/bestander/uglify-loader): Uglify contents of a module. Unlike uglify plugin you can minify with mangling only your application files and not the libraries
* [`html-minify`](https://github.com/bestander/html-minify-loader): Minifies HTML using [minimize](https://github.com/Moveo/minimize)
* [`vue`](https://github.com/vuejs/vue-loader): Load single-file Vue.js components as modules, with loader-support for preprocessors.
* [`tojson`](https://github.com/timoxley/tojson-loader) Serialize module exports as JSON. Cache generated static data as JSON at build time.
* [`zip-it`](https://github.com/bmagnantb/zip-it-loader) Convert files and directories to zip. Great with `file`.
* [`lzstring`](https://github.com/nickdeis/lzstring-loader) Compresses large strings inline using lz-string, and decompresses them at runtime
* [`modernizr`](https://github.com/peerigon/modernizr-loader) Get your modernizr build bundled with webpack
* [`s3`](https://github.com/benderTheCrime/s3-loader "s3-loader") Pull assets from s3 based on filename, path, and desired environment.
* [`path-replace`](https://github.com/cvgellhorn/path-replace-loader) Replace a given base path with another path for dynamic module loading
* [`react-intl`](https://github.com/danilobuerger/react-intl-loader) Loads react-intl locale data via `require.ensure`
* [`font-subset`](https://github.com/dematerializer/font-subset-loader): Loads a transformed font resource that contains only a specified subset of glyphs with all other glyphs stripped out.
* [`w3c-manifest`](https://github.com/mariusGundersen/w3c-manifest-loader): Loads a WebApp manifest.json file.
* [`web-app-manifest`](https://www.npmjs.com/package/web-app-manifest-loader): Load images referenced in the icons and splash_screens fields in a Web App Manifest.
* [`manifest-scope`](https://www.npmjs.com/package/manifest-scope-loader): Sets the scope of a web app manifest to the public path.

#### dialects (方言)

* [`coffee`](https://github.com/webpack/coffee-loader): Loads coffee-script like JavaScript
* [`coffee-jsx`](https://github.com/jsifalda/coffee-jsx-loader): Loads coffee-script with JSX like JavaScript
* [`coffee-redux`](https://github.com/webpack/coffee-redux-loader): Loads coffee-script like JavaScript
* [`json5`](https://github.com/webpack/json5-loader): Like json, but not so strict.
* [`es6`](https://github.com/shama/es6-loader): Loads ES6 modules. (old)
* [`esnext`](https://github.com/conradz/esnext-loader): Transpile ES6 code using [esnext](https://github.com/esnext/esnext).
* [`babel`](https://github.com/babel/babel-loader): Turn ES6 code into vanilla ES5 using [Babel](https://github.com/babel/babel).
* [`regenerator`](https://github.com/pjeby/regenerator-loader): Use ES6 generators via Facebook's [Regenerator](http://facebook.github.io/regenerator/) module.
* [`livescript`](https://github.com/appedemic/livescript-loader): Loads LiveScript like JavaScript
* [`sweetjs`](https://github.com/jlongster/sweetjs-loader): Use sweetjs macros.
* [`traceur`](https://github.com/jupl/traceur-loader): Use future JavaScript features with [Traceur](https://github.com/google/traceur-compiler).
* [`ts`](https://github.com/TypeStrong/ts-loader): Loads TypeScript like JavaScript.
* [`typescript`](https://github.com/andreypopp/typescript-loader): Loads TypeScript like JavaScript.
* [`awesome-typescript`](https://github.com/s-panferov/awesome-typescript-loader): Loads TypeScript like JavaScript with watching support. **Works with TypeScript 1.5-alfa**
* [`webpack-typescript`](https://github.com/denvned/webpack-typescript): Loads TypeScript like JavaScript. Supports watch mode and source maps. Works with TypeScript 1.5, 1.6, and nightly builds of TypeScript 1.7 and 1.8.
* [`purs`](https://www.npmjs.com/package/purs-loader): Loads [PureScript](http://www.purescript.org/) like JavaScript.
* [`oj`](https://github.com/DragonsInn/oj-loader): Loads [OJ](https://github.com/musictheory/oj) (an Objective-C like language) files and compiles them to plain JavaScript.
* [`elm-webpack`](https://github.com/rtfeldman/elm-webpack-loader): Loads [Elm](http://elm-lang.org/) files and compiles them to plain JavaScript.
* [`miel`](https://github.com/collardeau/miel-loader): Loads [Miel](https://github.com/collardeau/miel) syntax and compiles to JavaScript.
* [`wisp`](https://github.com/girvo/wisp-loader): Loads [Wisp](https://github.com/Gozala/wisp) modules and compiles them to JavaScript.
* [`sibilant`](https://github.com/jbr/sibilant-webpack-loader): Loads [Sibilant](https://github.com/jbr/sibilant) files and compiles them to JavaScript.

#### templating

* [`html`](https://github.com/webpack/html-loader): Exports HTML as string, require references to static resources.
* [`dom`](https://github.com/Wizcorp/dom-loader): Exports HTML in a DOM element container.
* [`riot`](https://github.com/esnunes/riotjs-loader): Load RiotJS tags and convert them to javascript.
* [`pug`](https://github.com/pugjs/pug-loader): Loads Pug/Jade template and returns a function
* [`jade-html`](https://github.com/bline/jade-html-loader): Loads Jade template and returns generated HTML
* [`jade-react`](https://github.com/halhenke/jade-react-loader): Uses Jade templates for React rendering instead of JSX
* [`virtual-jade`](https://github.com/tdumitrescu/virtual-jade-loader): Use Jade templates to produce [`virtual-dom`](https://github.com/Matt-Esch/virtual-dom) hyperscript output
* [`template-html`](https://github.com/jtangelder/template-html-loader): Loads any template with consolidate.js and returns generated HTML
* [`handlebars`](https://github.com/altano/handlebars-loader): Loads handlebars template and returns a function
* [`handlebars-template-loader`](https://github.com/emaphp/handlebars-template-loader): Loads handlebars template and returns a function (alternative)
* [`dust`](https://github.com/avaly/dust-loader): Loads dust template and returns a function
* [`ractive`](https://github.com/rstacruz/ractive-loader): Pre-compiles Ractive templates for interactive DOM manipulation
* [`jsx`](https://github.com/petehunt/jsx-loader): Transform jsx code for [React](http://facebook.github.io/react/) to js code.
* [`react-templates`](https://github.com/AlexanderPavlenko/react-templates-loader): Loads react-template and returns a function
* [`em`](https://github.com/yoshdog/emblem-loader): Compiles [Emblem](http://emblemjs.com/) to Handlebars.js
* [`ejs`](https://github.com/okonet/ejs-loader): Loads EJS ([underscore](http://underscorejs.org/#template)( templating engine) template and returns a pre-compiled function
* [`ejs-html`](https://github.com/akim-mcmath/ejs-html-loader): Loads [EJS](http://ejs.co/) templates and returns generated HTML.
* [`mustache`](https://github.com/deepsweet/mustache-loader): Pre-compiles Mustache templates with [Hogan.js](https://github.com/twitter/hogan.js) and returns a function
* [`yaml`](https://github.com/okonet/yaml-loader): Converts YAML to JSON
* [`yml`](https://github.com/nkt/yml-loader): Converts YAML to JavaScript object, optionally omitting blacklisted keys
* [`react-markdown`](https://github.com/javiercf/react-markdown-loader): Compiles Markdown to a React Component using the markdown-parse parser
* [`front-matter`](https://github.com/elliottsj/front-matter-loader): Extracts YAML frontmatter
* [`markdown`](https://github.com/peerigon/markdown-loader): Compiles Markdown to HTML
* [`remarkable`](https://github.com/unindented/remarkable-loader): Compiles Markdown to HTML using the Remarkable parser
* [`markdown-it`](https://github.com/unindented/markdown-it-loader): Compiles Markdown to HTML using the markdown-it parser
* [`markdownattrs`](https://github.com/pikulev/markdownattrs-loader): Compiles Markdown to HTML using the markdown-it-attrs parser that allows you to set classes, identifiers and attributes to your markdown.
* [`ng-cache`](https://github.com/teux/ng-cache-loader): Puts HTML partials in the Angular's $templateCache
* [`ngtemplate`](https://github.com/WearyMonkey/ngtemplate-loader): Bundles your AngularJS templates and Pre-loads the template cache.
* [`hamlc`](https://github.com/ericdfields/hamlc-loader): Compiles haml-coffee templates (.hamlc) and returns a function.
* [`haml`](https://github.com/AlexanderPavlenko/haml-loader): Renders haml-coffee templates (.html.hamlc) and returns a string.
* [`jinja`](https://github.com/pierreant-p/jinja-loader): Precompiles nunjucks and jinja2 templates
* [`nunjucks`](https://github.com/at0g/nunjucks-loader): Precompiles nunjucks templates
* [`soy`](https://github.com/bendman/soy-loader): Compiles Google Closure templates and returns the namespace with render functions
* [`smarty`](https://github.com/zhiyan/smarty-loader): Pre-compiles php smarty templates and returns a function
* [`swagger`](https://github.com/mbaasy/swagger-loader): Compiles Swagger/OpenAPI JSON and YAML specifications.
* [`template-string`](https://github.com/bradbenvenuti/template-string-loader): Use ES6 template strings for html templates
* [`ect`](https://github.com/cusspvz/ect-loader): Compile [ectjs](http://ectjs.com/) templates
* [`tmodjs`](https://github.com/xosuperpig/tmodjs-loader): Load [art-template](https://github.com/aui/artTemplate) , a template-engine that is widely used in China.
* [`layout`](https://github.com/uxnow/layout-loader): You can use require directly in html now!
* [`swig`](https://github.com/coditorium/nodejs-swig-loader): Webpack Swig loader
* [`twig`](https://github.com/zimmo-be/twig-loader): Webpack Twig.js loader

#### styling

* [`bootstrap-webpack`](https://github.com/gowravshekar/bootstrap-webpack): Loads a configuration file for Twitter Bootstrap integration using Less. Allows complete customisation via Less.
* [`font-awesome-webpack`](https://github.com/gowravshekar/font-awesome-webpack): Loads a configuration file for Font Awesome integration using Less. Allows complete customisation via Less.
* [`bootstrap-sass`](https://github.com/shakacode/bootstrap-sass-loader): Deprecated. See [`bootstrap`](https://github.com/shakacode/bootstrap-loader).
* [`bootstrap`](https://github.com/shakacode/bootstrap-loader): Loads a configuration file for Twitter Bootstrap integration using Sass. Allows complete customization via Sass. Supports CSS modules and both Bootstrap 3 and 4.
* [`font-awesome`](https://github.com/shakacode/font-awesome-loader): Easy integration of font-awesome with customization via Sass.
* [`style`](https://github.com/webpack/style-loader): Add exports of a module as style to DOM
* [`isomorphic-style`](https://github.com/kriasoft/isomorphic-style-loader): Ad-hoc replacement to `style-loader` adding support of isomorphic apps and critical path CSS
* [`css`](https://github.com/webpack/css-loader): Loads css file with resolved imports and returns css code
* [`cess`](https://github.com/irom-io/cess-loader): Loads and compile cess file (css in es6 js) to css
* [`less`](https://github.com/webpack/less-loader): Loads and compiles a less file
* [`sass`](https://github.com/jtangelder/sass-loader): Loads and compiles a scss file
* [`stylus`](https://github.com/shama/stylus-loader): Loads and compiles a stylus file
* [`csso`](https://github.com/sandark7/csso-loader): Minifies input CSS with CSSO
* [`rework`](https://github.com/okonet/rework-loader): Post-process CSS with [Rework](https://github.com/reworkcss/rework) and returns CSS code
* [`postcss`](https://github.com/postcss/postcss-loader): Post-process CSS with Autoprefixer and [other PostCSS plugins](https://github.com/postcss/postcss#built-with-postcss)
* [`autoprefixer`](https://github.com/passy/autoprefixer-loader): Add vendor prefixes to CSS rules using values from Can I Use
* [`namespace-css`](https://github.com/jeffling/namespace-css-loader): Namespace your css with a given selector (for encapsulating all rules in one subset of your site)
* [`fontgen`](https://www.npmjs.com/package/fontgen-loader): Create your own webfont with proper CSS on-the-fly and include it into WebPack.
* [`classnames`](https://github.com/itsmepetrov/classnames-loader): Automatically bind [css-modules](https://github.com/css-modules/css-modules) to [classnames](https://github.com/JedWatson/classnames).
* [`theo`](https://github.com/Autodesk/theo-loader) Loads Design Tokens files transformed by [theo](https://github.com/salesforce-ux/theo)
* [`bulma`](https://github.com/stipsan/bulma-loader) Customize [Bulma](http://bulma.io/) in your [css-modules](https://github.com/css-modules/css-modules).
* [`css-to-string`](https://github.com/smithad15/css-to-string-loader) Convert the output of the [`css-loader`](https://github.com/webpack/css-loader) back to a string.

#### translation

* [`po`](https://github.com/perchlayer/po-loader): Loads a PO gettext file and returns JSON
* [`po2mo`](https://github.com/rubencosta/po2mo-loader): Compiles gettext PO files to MO files
* [`format-message`](https://github.com/thetalecrafter/format-message-loader): Compiles translations to ICU Message Format strings in [`formatMessage`](https://github.com/thetalecrafter/format-message) calls
* [`jsxlate`](https://github.com/drd/jsxlate-loader): Transform React source code for use with [`jsxlate`](https://github.com/drd/jsxlate)
* [`angular-gettext`](https://github.com/princed/angular-gettext-loader) Compiles `.po` files as `Angular.js` module or `json` to be used with `angular-gettext`.
* [`webpack-angular-translate`](https://github.com/DatenMetzgerX/webpack-angular-translate): Extracts [angular-translate](https://angular-translate.github.io) translation id's and default text's
* [`angular-gettext-extract`](https://github.com/wombleton/angular-gettext-extract-loader) Extracts strings for translation into a nominated `.pot` file.
* [`gettext`](https://github.com/mrblueblue/gettext-loader): Compiles a Gettext PO file from code source.
* [`preprocessor`](https://github.com/artificialtrends/preprocess-loader): The preprocessor-loader provides the ability to preprocess source files through user defined regular expressions, macros, and callback routines. All user defined logic can be applied to line scope or source scope.
* [`amdi18n-loader`](https://github.com/TooBug/webpack-amdi18n-loader): I18n loader similar to require.js i18n plugin. The language packs support AMD/CommonJS module and can be written in `.json` / `.js` / `.coffee` files.
* [`sprockets-preloader`](https://www.npmjs.com/package/sprockets-preloader): Translate sprockets require directives into JavaScript module dependencies. Useful for migrating a Rails project to Webpack module bundling.
* [`properties`](https://www.npmjs.com/package/properties-loader): Loader for .properties files.
* [`transifex`](https://www.npmjs.com/package/transifex-loader): Fetch imported translation files from transifex.

#### support

* [`mocha`](https://github.com/webpack/mocha-loader): do tests with mocha in browser or node.js
* [`coverjs`](https://github.com/webpack/coverjs-loader): PostLoader to code coverage with CoverJs
* [`istanbul-instrumenter`](https://github.com/deepsweet/istanbul-instrumenter-loader): [Istanbul](https://github.com/gotwarlost/istanbul) postLoader to code coverage with [karma-webpack](https://github.com/webpack/karma-webpack) and [karma-coverage](https://github.com/karma-runner/karma-coverage)
* [`isparta-instrumenter`](https://github.com/ColCh/isparta-instrumenter-loader): [Isparta](https://github.com/douglasduteil/isparta) preLoader to code coverage with [karma-webpack](https://github.com/webpack/karma-webpack) and [douglasduteil/karma-coverage#next](https://github.com/douglasduteil/karma-coverage)
* [`ibrik-instrumenter`](https://github.com/vectart/ibrik-instrumenter-loader): [Ibrik](https://github.com/Constellation/ibrik) preLoader to CoffeeScript code coverage with [karma-webpack](https://github.com/webpack/karma-webpack) and [douglasduteil/karma-coverage](https://github.com/douglasduteil/karma-coverage)
* [`eslint`](https://github.com/MoOx/eslint-loader): PreLoader for linting code using ESLint.
* [`jshint`](https://github.com/webpack/jshint-loader): PreLoader for linting code.
* [`jscs`](https://github.com/unindented/jscs-loader): PreLoader for style checking.
* [`standard`](https://github.com/timoxley/standard-loader): Conform to [standard](https://github.com/feross/standard) code style.
* [`inject`](https://github.com/plasticine/inject-loader): A Webpack loader for injecting code into modules via their dependencies
* [`injectable`](https://github.com/jauco/webpack-injectable): Allow to inject dependencies into modules
* [`transform`](https://github.com/webpack/transform-loader): Use browserify transforms as loader.
* [`falafel`](https://github.com/wombleton/falafel-loader): Use falafel AST transforms as a loader.
* [`image-size`](https://github.com/patcoll/image-size-loader): Loads an image and returns its dimensions and type
* [`csslint`](https://github.com/hyungjs/csslint-loader): PreLoader for linting code using CSSLint
* [`coffeelint`](https://github.com/bline/coffeelint-loader): PreLoader for linting [CoffeeScript](http://coffeescript.org/).
* [`tslint`](https://github.com/wbuchwalter/tslint-loader): PreLoader for linting TypeScript using [TSLint](https://github.com/palantir/tslint)
* [`parker`](https://github.com/tanem/parker-loader): Output a stylesheet analysis report using [parker](https://github.com/katiefenn/parker).
* [`sjsp`](https://github.com/3100/sjsp-loader): Inject some codes for profiling using [node-sjsp](https://github.com/45deg/node-sjsp).
* [`amdcheck`](https://github.com/mehdishojaei/amdcheck-loader): Uses AST to find and remove unused dependencies in AMD modules using [amdextract](https://github.com/mehdishojaei/amdextract).
* [`manifest`](https://github.com/RinconStrategies/manifest-loader): A loader to generate JSON asset manifests to pass to preloading systems.
* [`gulp-rev`](https://github.com/adjavaherian/gulp-rev-loader): Use in tandem with gulp-rev to replace assets from rev-manifest.
* [`html-test`](https://github.com/wombleton/html-test-loader) Test your html templates (for example) for analytics.
* [`stylelint`](https://github.com/adrianhall/stylelint-loader) Preloader for linting SASS and SCSS with style lint
* [`stylefmt`](https://github.com/tomasAlabes/stylefmt-loader) Preloader for fixing SASS/SCSS/PostCSS errors with style lint
* [`scsslint`](https://github.com/domjtalbot/scsslint-loader): PreLoader for linting Scss using [scss-lint](https://github.com/brigade/scss-lint).
* [`htmlhint`](https://github.com/mattlewis92/htmlhint-loader): PreLoader for linting HTML using [htmlhint-loader](https://github.com/mattlewis92/htmlhint-loader).
* [`documentation`](https://github.com/domjtalbot/documentation-loader): Javascript documentation with [DocumentationJS](https://github.com/documentationjs/documentation)
* [`sassdoc`](https://github.com/domjtalbot/sassdoc-loader): Scss documentation with [SassDoc](https://github.com/SassDoc/sassdoc)
* [`performance-loader`](https://github.com/maxkostow/performance-loader): profile module performance
