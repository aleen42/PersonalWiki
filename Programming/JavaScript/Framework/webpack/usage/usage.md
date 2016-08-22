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
