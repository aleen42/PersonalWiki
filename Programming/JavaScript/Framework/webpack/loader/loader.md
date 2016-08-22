## Loader [Back](./../webpack.md)

### Description

Loaders are transformations that are applied on a resource file of your app. For example, you can use loaders to tell webpack to load CoffeeScript or JSX

### Lists of Loaders

#### basic

- `json`: Loads file as JSON
hson: Loads HanSON file (JSON for Humans) as JSON object
raw: Loads raw content of a file (as utf-8)
val: Executes code as module and consider exports as JavaScript code
to-string: Executes code as a module, casts output to a string and exports it
imports: Imports stuff to the module
exports: Exports stuff from the module
expose: Expose exports from a module to the global context
script: Executes a JavaScript file once in global context (like in script tag), requires are not parsed.
apply: Executes a exported JavaScript function, optionally with arguments, and exports its return value.
callback: Parses your JS, calls specified functions (which you implement in webpack context) and replaces them with the results
if-loader: This is a preprocesser for the webpack module bundler. It support the if directive,similar to C #ifdef .
ifdef-loader: Preprocessor for .js/.ts files that allows conditional compilation via // #if and // #endif, while preserving sourcemaps.
source-map: Extract sourceMappingURL comments from modules and offer it to webpack
checksum: Computes the checksum of a file
null: Emits an empty module.
cowsay: Emits a module with a cowsay header.
dsv: Loads csv/tsv files.
glsl: Loads glsl files and support glsl-chunks.
render-placement: Adds React.render to your component for you (not very practical in most cases)
xml: Loads XML as JSON.
svg-react: Load SVG files as JSX-ified React.createClass declarations.
svg-url: Loads SVG file as utf-8 encoded data:URI string.
svg-as-symbol: Wraps content of root element of source SVG file inside symbol element and returns resulting markup.
base64: Loads file content as base64 string
ng-annotate: A loader to annotate dependency injections in Angular.js applications.
node: Loads .node files that are produced using node-gyp.
required: Require a whole directory of trees in bulk. Require JS, Import CSS and imports stuff in it.
icons Generates iconfont from .svg files (uses gulp-iconfont)
markup-inline Inline SVGs to HTML. It’s very useful when applying icon font or applying CSS animation to SVG.
block-loader Generic loader for rewriting only parts of files, based on content start/end delimiters.
bundler-configuration Bundler configuration loader, a tool to include bundler configuration in the resulting build.
console: Prints the resolved require of webpack to the console.
solc: Compiles Solidity code (.sol) and returns JavaScript objects with Application Binary Interface (ABI) and bytecode ready for deployment to Ethereum.
web3: Deploys Ethereum VM bytecode and returns ready-to-use JS instances of deployed smart contracts. Also returns initialized Web3 object.
includes: Load any text file and support nested includes
combine: Combine results from multiple loaders into one object
regexp-replace: Replace RegExp matches with a string

