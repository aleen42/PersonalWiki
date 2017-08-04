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

Then you can init the module with:

```bash
npm init
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
describe('tests', function () {
	it('test case 1', function () {
		autoContent.printText(3).should.equal(4);
	});
});
```

After that, a `Makefile` file can be created like the following:

```makefile
test:
	./node_modules/.bin/mocha --reporter nyan

.PHONY: test
```

Finally, the test scrit of `package.json` can be:

```json
{
  // ...
  "scripts": {
    "test": "make test"
  },
  // ...
  "devDependencies": {
    "mocha": "~2.4.5",
    "chai": "~3.5.0"
  }
}
```

Here is the final files architecture:

> lib

>> index.js

> test

>> index.js

> package.json

> Makefile

> node_modules

#### Write the Readme with convention

```md
## auto-content

a node.js module for generating justified contents

## Installation

	npm install auto-content

## Usage

	const should = require('chai').should();
	const autoContent = require('../lib/index');

	console.log(autoContent.printText(1));

## Tests

	npm test

## Release History

* 0.1.0 Initial release

## :yum: How to contribute

Have an idea? Found a bug? See [how to contribute](https://aleen42.github.io/PersonalWiki/contribution.html).

## :scroll: License

[MIT](https://aleen42.github.io/PersonalWiki/MIT.html) © aleen42
```

#### Publish the module

Note that for whatever reason if you decide not to publish your module on npm, the npm package format provides value in itself in both portability and ease of installation. For example, you can install packages directly from Github, and even specify a tag, sha, or branch if you want.

```bash
npm install git://github.com/aleen42/auto-content.git
npm install git://github.com/aleen42/auto-content.git#0.1.0
```

Before publishing, be sure to test that your package installs and works correctly.

- Verify that the package installs properly

After that, you can register this module with your npm account by using the following command:

```bash
npm adduser
```

Finally, just publish your module:

```bash
npm publish
```

With that, other developers can install your module by typing:

```
npm install auto-content
```
