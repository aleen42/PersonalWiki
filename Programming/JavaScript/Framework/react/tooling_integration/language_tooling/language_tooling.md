## Language Tooling [Back](./../tooling_integration.md)

### ES2015 with JSX

#### In-browser JSX Transform

If you like using JSX, Babel 5 provided an in-browser ES2015 and JSX transformer for development called browser.js that can be included from [CDNJS](https://cdnjs.com/libraries/babel-core/5.8.34).

With that JavaScript file, we can just include a `<script type="text/babel">` tag to engage the JSX transformer.

> Note:

> The in-browser JSX transformer is fairly large and results in extraneous computation client-side that can be avoided. Do not use it in production

#### Productionizing: Precompiled JSX

If you have npm, you can run: 

```bash
$ npm install -g babel-cli
```

This tool will translate files that use JSX syntax to plain JavaScript files that can run directly in the browser. It will also watch directories for you and automatically transform files when they are changed; for example:

```bash
$ babel --watch src/ --out-dir lib/.
```

Beginning with Babel 6, there are no transforms included by default. This means that options must be specified when running the `babel` command, or a `.babelrc` must specify options.

Additional packages must also be installed which bundle together a number of transforms, called presets. The most common use when working with React will be to include the `es2015` and `react` presets. More information about the changes to Babel can be found in [their blog post announcing Babel 6](http://babeljs.io/blog/2015/10/29/6.0.0).

Here is an example of what you will do if using ES2015 syntax and React:

```bash
$ npm install babel-preset-es2015 babel-preset-react
$ babel --presets es2015,react --watch src/ --out-dir lib/
```

#### Helpful Open-Source Projects

The open-source community has built tools that integrate JSX with several editors and build systems. See [JSX integrations](https://github.com/facebook/react/wiki/Complementary-Tools#jsx-integrations) for the full list.

### Flow

Flow is a JavaScript type checker released by Facebook, and it supports JSX. For more info, checkout the [Flow homepage](http://flowtype.org/).

### TypeScript

TypeScript is a type-checker and transpiler that supports type-checking React and JSX. For more info, check out their guide on [getting started with React and Webpack](https://www.typescriptlang.org/docs/handbook/react-&-webpack.html), or learn more about [TypeScript's JSX support](https://www.typescriptlang.org/docs/handbook/jsx.html).

To learn more about TypeScript in general, visit the [TypeScript homepage](https://www.typescriptlang.org/).
