## Webpack + React [Back](./../webpack.md)

For my familiarity, I'll build up with react projects with the following file structure:

> project

>> src

>>> components

>>> *_entry.js

>> build

> webpack.config.js

> *.html

Files of sites like (`*.html`) will be placed in the root of this project or if using Laravel, the place will be other one outside this project. Files emitted by webpack will be in `/build`, and imported by sites. Then, here I would like to use a case for teaching how to use webpack to bundle  files with different dependencies in a React project.

#### 1. Initialize a npm project

```bash
npm init # (answer the questions)
```

#### 2. Install webpack as a development dependency, and global as well

```bash
npm install webpack --save-dev
```

```bash
sudo npm install webpack -g
```

#### 3. Install loaders for transpiling es2015 and JSX

```bash
npm install babel-core --save-dev
npm install babel-preset-es2015 --save-dev
npm install babel-preset-react --save-dev
npm install babel-loader
```

#### 4. Set up a configuration file for webpack `webpack.config.js`

```js
module.exports = {
	entry: './src/entry.js',
	output: {
		path: __dirname + '/build',
		filename: 'bundle.js'
	},
	resolve: {
		extensions: ['', '.js', '.jsx']
	},
	module: {
		loaders: [
			{
				test: /\.jsx?$/,
				loader: 'babel-loader',
				exclude: /node_modules/,
				query: {
					presets: ['es2015', 'react']
				}
			}
		]
	}
};

```

#### 5. Write certain JavaScript files

**entry.js**

