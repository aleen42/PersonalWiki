## Create and publish a node.js module [Back](./../node.md)

#### What is npm?

**npm** is an online registry for open-source node.js projects, modules, resources, etc. Here is the [official website](http://npmjs.org.).

**npm** is also the official package manager for node.js, and provides a command line interface (CLI) for interacting with the registry.

For you ruby devs, npm is akin to [rubygems](http://rubygems.org/).

#### Configure npm

To set some information for our own:

```bash
npm set init.author.name "aleen42"
npm set init.author.email "aleen42@vip.qq.com"
npm set init.author.url "http://aleen42.github.io/pc.html"
```

#### Create a module

The primary 2 items that we are concerned with here are `require` and `exports`. You `require` other modules that you wish to use in your code and your module `exports` anything that should be exposed publicly.

```js
module.exports = {
	_hello: 1,

	printText: function(i) {
		this._hello += i;
		return this._hello;
	}
};
```

#### Create some tests

Here is to create tests with [Mocha](http://visionmedia.github.io/mocha/) and [Chai](http://chaijs.com/) frameworks with the following commands.

*Note that they are added to the 'devDependencies' section, as they are **only required during development** and not at runtime.*

```bash
npm install mocha --save-dev
npm install chai --save-dev
```

The above commands will also create a `node_modules` folder in your project directory containing those dependencies. Following best practices, we'll want to keep the `node_modules` folder out of the git repository. We can do that by adding a `.gitignore` file to our project root, with the following contents:

```
node_modules
```

Then, create a `test` directory to hold tests by creating a file with the same name `index.js`

```js
const should = require('chai').should();
const autoContent = require('../lib/index');

/** test case with should syntax provided by the Chai framework */
autoContent.printText(3).should.equal(4);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a