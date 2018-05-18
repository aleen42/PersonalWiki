## Integrations [Back](./../TypeScript.md)

TypeScript should always be treated as an extension of JavaScript, and try to migrate from JavaScript gradually. The first session we will talk about is the configuration of TypeScript as same as other common tools.

### 1. Configurations

TypeScript uses a file called `tsconfig.json` for managing projects' options, like `package.json` to npm modules, where you can specify how to compile Typescript into JavaScript, like which files you want to include or exclude, or whether target files belongs to ES6 syntax, etc. For example, the following configuration file has specified a few things:

```json
{
    "compilerOptions": {
        "outDir": "./build",
        "allowJs": true,
        "target": "es5"
    },
    "include": [
        "./src/**/*"
    ]
}
```

- using `include` to specify reading in any "understandable" files in the `src` folder.
- using `allowJs` option to mark JavaScript files as "understandable".
- using `outDir` to specify where to output files.
- using `target` to specify compiler to translate files down to an older version like ECMAScript 5.

Actually, with setting configurations for compilers to know about your project, you can also earn more early benefits like catching certain bugs with some options, like linting.

- `noImplicitReturns`: which prevents you from forgetting to return at the end of a function.
- `noFallthroughCasesInSwitch`: which is helpful if you never want to forget a break statement between `cases` in a `switch` block.

For more options to check wha we can do, please visit official documents [**here**](https://www.typescriptlang.org/docs/handbook/compiler-options.html).

### 2. Work Flow

As a front-end project, the flow of work has always attracted our concern, where developers usually use some building tools like **Gulp**, or **Grunt** to manage tasks, and some bundling tools like **Webpack** to build bundles with JavaScript modules. That's why it is so significant to know how to integrating such a building tool with TypeScript.

#### 2.1 Gulp

As described in the last session "configurations", we know that TypeScript has used a file named `tsconfig.json` to manage projects' options, and if we want to register a task to convert TypeScript into JavaScript, we can refer to the following snippet, where we use `gulp-typescript`:

```js
/** Gulpfile.js */
const gulp = require('gulp');
const ts = require('gulp-typescript');
const tsProject = ts.createProject('./tsconfig.json');

gulp.task('convert', () => tsProject.src()
    .pipe(tsProject())
    .js.pipe(gulp.dest('dist'))
);
```

#### 2.2 Webpack

When it comes to integrating with Webpack, it is quite simple like using Gulp. As the official document said, we can use [`awesome-typescript-loader`](https://github.com/s-panferov/awesome-typescript-loader), a TypeScript loader to load TypeScript files, combined with `source-map-loader` for easier debugging.

The following has shown how we configure Webpack 2.x+:

```js
/** webpack.config.js */
module.exports = {
    /** ... */
    module: {
        rules: [
            { test: /\.tsx?$/, loader: 'awesome-typescript-loader' }
        ]
    }
};
```

Certainly, we should remember that this TypeScript loader should be run before any other loader, so that others can deal with JavaScript files. The same goes for [`ts-loader`](https://github.com/TypeStrong/ts-loader), another TypeScript loader, and what are differences between them? We can check what [`awesome-typescript-loader`](https://github.com/s-panferov/awesome-typescript-loader) announce:

> 1. atl has first-class integration with Babel and enables caching possibilities. This can be useful for those who use Typescript with Babel. When `useBabel` and `useCache` flags are enabled, typescript's emit will be transpiled with Babel and cached. So next time if source file (+environment) has the same checksum we can totally skip typescript's and babel's transpiling. This significantly reduces build time in this scenario.
> 2. atl is able to fork type-checker and emitter to a separate process, which also speeds-up some development scenarios (e.g. react with react-hot-loader) So your webpack compilation will end earlier and you can explore compiled version in your browser while your files are type checked.

The configuration for using [`ts-loader`](https://github.com/TypeStrong/ts-loader) is really familiar:

```js
/** webpack.config.js */
module.exports = {
    /** ... */
    module: {
        rules: [
            { test: /\.tsx?$/, loader: 'ts-loader' }
        ]
    }
};
```

### 3. Modules

After setup some bundling tools like **Webpack**, we can just use files with `.ts` or `.tsx` extension to code with TypeScript. However, the most bunches of errors we will meet always arise when trying to import modules. In JavaScript, we can use some modules style like CommonJS, AMD, or even ES modules to import modules, while in TypeScript, the only available syntax is `import/require`. But what if we don't want to change such a kind of style? What you can do is to convince TypeScript:

```ts
/** For Node/CommonJS */
declare function require(path: string): any;
/** For RequireJS/AMD */
declare function define(...args: any[]): any;
```

In official opinions, it is better to use TypeScript syntax for importing modules:

```ts
import foo = require('./foo');
```

By default, JavaScript modules' exporting seems not useful for TypeScript importing, where you may ge an error like "Cannot find module 'foo'". That's because we should declare such a module files to describe it as a library. Fortunately, the community has provided us a project named [`DefinitelyTyped`](https://github.com/DefinitelyTyped/DefinitelyTyped) , where contributors has already declared some frequently used JavaScript libraries for us to use directly. For instance, we can directly require [`@types/lodash`](https://www.npmjs.com/package/@types/lodash) so that we can import it in TypeScript:

```ts
import _ = require('@types/lodash');
```

When it comes to declaring custom libraries created by us, we can typically use `exports` or `module.exports` like CommonJS to declare, which is available in TypeScript. Besides, we can also declare by assigning to `export` like the following snippet:

```ts
export = function () { /** ... */ };
```
