## Usage [Back](./../webpack.md)

### Getting Started

There're 3 kinds of usages of webpack: **CLI**, **node.js API**, and **Configuration**.

First, we'll learn the basics of webpack by using just webpack's command-line interface.

#### Create a modular JavaScrip project

**cat.js**

```js
var cats = ['dave', 'henry', 'martha'];
module.exports = cats;
```

**app.js (Entry Point)**

```js
var cats = require('./cat.js');
console.log(cats);
```

The "entry point" is where your application will start, and where webpack will start tracking dependencies between modules.

Give webpack the entry point (app.js) and specify an output file (app.bundle.js) of a command-line interface:

```js
webpack ./app.js app.bundle.js
```

webpack will read and analyze the entry point and its dependencies (including transitive(傳遞性) dependencies). Then it will bundle them all into `app.bundle.js`.

![](./how-it-works.png)

### Getting Serious

To gain full access to webpack's flexibility, we need to create a "configuration file".

#### Project Structure

In real-world webpack projects, we'll separate the source files from the bundled files by organizing them in folders. For example, we'll put the source files in src, and bundled files in bin.

Our final project structure will look like this:

![](./project-structure.png)

> In the wild, there are many project structures. Some projects use `app` instead of `src`. Some projects use `dist` or `build` instead of `bin`. Projects with tests usually use `test`, `tests`, `spec`, `specs` or colocate the test files in the source folder.

1. Create the `bin` and `src` directory.
    ```bash
    mkdir bin
    mkdir src
    ```
2. Move the original source file to `src` folder:
    ```bash
    mv app.js cat.js src
    ```
3. Initialize an npm project
    ```bash
    npm init # (answer the questions)
    ```
4. Install webpack as a development dependency.
    ```bash
    npm install webpack --save-dev
    ```

#### A Configuration File

As your project grows and your configuration becomes more complex, it becomes unwieldy to configure webpack from the command line. Let's create a configuration file instead.

1. Create `webpack.config.js`:
    ```js
    module.exports = {
        entry: './src.app.js',
        output: {
            path: './bin',
            filename: 'app.bundle.js'
        }
    };
    ```

    > A webpack configuration file is a CommonJS-style module.
2. With a configuration file in place, you can now simply run webpack like this:
    ```bash
    webpack
    ```

#### Using Loaders

webpack only supports JavaScript modules natively, but most people will be using a transpiler for ES2015, CoffeeScript, TypeScript, etc. They can be used in webpack by using loaders.

Loaders are special modules webpack uses to 'load' other modules (written in another language) into JavaScript (that webpack understands). For example, babel-loader uses Babel to load ES2015 files.
    