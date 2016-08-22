## Usage [Back](./../webpack.md)

### Getting Started

There're 3 kinds of usages of webpack: **CLI**, **node.js API**, and **Configuration**.

First, we’ll learn the basics of webpack by using just webpack’s command-line interface.

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