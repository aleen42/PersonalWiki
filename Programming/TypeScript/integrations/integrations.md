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

```typescript
/** For Node/CommonJS */
declare function require(path: string): any;
/** For RequireJS/AMD */
declare function define(...args: any[]): any;
```

In official opinions, it is better to use TypeScript syntax for importing modules:

```typescript
import foo = require('./foo');
```

By default, JavaScript modules' exporting seems not useful for TypeScript importing, where you may ge an error like "Cannot find module 'foo'". That's because we should declare such a module files to describe it as a library. Fortunately, the community has provided us a project named [`DefinitelyTyped`](https://github.com/DefinitelyTyped/DefinitelyTyped) , where contributors has already declared some frequently used JavaScript libraries for us to use directly. For instance, we can directly require [`@types/lodash`](https://www.npmjs.com/package/@types/lodash) so that we can import it in TypeScript:

```typescript
import _ = require('@types/lodash');
```

When it comes to declaring custom libraries created by us, we can typically use `exports` or `module.exports` like CommonJS to declare, which is available in TypeScript. Besides, we can also declare by assigning to `export` like the following snippet:

```typescript
export = function () { /** ... */ };
```

### 4. Loose Scenarios in JavaScript

In JavaScript, we can do a lot of loose things as the language itself does not support type checked, like initiating a method to accept any kinds of arguments without throwing errors. When meeting with following situations, we should take more care about them when migrating from JavaScript.

#### 4.1 Arguments

When checking arguments of a declared methods to work around situations where methods accept too many arguments, TypeScript needs us to explicitly declare how those kind of methods handle argument:

Like following function in JavaScript:

```js
function func() {
    if (arguments.length === 2 && !Array.isArray(arguments[1])) {
        var f = arguments[0];
        var arr = arguments[1];
    }
}

func(function (x) { console.log(x); }, [1, 2, 3]);
func(function (x) { console.log(x); }, 1, 2, 3);
```

When migrating to TypeScript, we need to explicitly declare this two situations by using function overloads:

```typescript
function func(f: (x: number) => void, arr: number[]): void;
function func(f: (x: number) => void, ...arr: number[]): void;
function func() {
    if (arguments.length === 2 && !Array.isArray(arguments[1])) {
        var f = arguments[0];
        var arr = arguments[1];
    }
}

func(console.log, [1, 2, 3]);
func(console.log, 1, 2, 3);
```

The above situation has added two overloads for declaring. Both of them check whether the function `func` takes a function as its first parameter (which should take a `number`), and the then the first overload means `func` should take an array of `number` as its second parameter, while the second overload means it can take any number of arguments (reset parameter).

#### 4.2 Objects' Properties

In JavaScript, we can create an object and add properties to it immediately like so:

```js
var obj = {};
obj.color = 'red';
obj.volume = 11;
```

In TypeScript, it is not allowed as it treats `obj` as an only empty object, which have no properties. So we need to declare what this object should look like before:

```typescript
interface Options { color: string; volume: number }

let obj = {} as Options;
obj.color = 'red';
obj.volume = 11;
```

As alternatives, TypeScript has also allowed us to declare the object as `any`, a _flexible_ type, to handle the situation when we don't exactly know what the object will look like during initialization stage:

```typescript
let obj = {} as any;
```

It is suggested that considering whether we really need to use this `any` to declare objects, before making a decision, because it also means that we lose most of the error checking, which is exactly the feature of TypeScript.

When comparing `{}` with `Object`, it is better to use `{}`, because object literal is technically a more general type than `Object` in certain esoteric cases.

#### 4.3 Strict Types

As TypeScript gives us more safety and analysis feature, we can start enabling these checks for greater safety.

##### 4.3.1 No Implicit `any`

When TypeScript don't exactly figure out what certain types should be, it will decide to use the type `any` in such a case. Though it is great for migration from JavaScript, it also means that we have lost this support at the same time. What if we want to dig out such pain spots, we can enable the option `noImplicitAny` for helping analysis.

##### 4.3.2 Strict `null` and `undefined` Checks

By default, TypeScrit assumes that `null` and `undefined` are in the domain of every type, which means that any declared type can also be `null` or `undefined`. Same as the `any` mentioned above, it is great for migration, but we must lose something for this. If we want to handle ourselves, just enable the option `strictNullChecks`.

After enabling it, we can experience what TypeScript will check:

```typescript
declare let foo: string[] | null;
foo.length; /** error - 'foo' is possibly 'null' */
```

If disabling:

```typescript
declare let foo: string[];
foo.length; /** no error */
```

Sometimes, we may have some variables we know better in some logic, which can possibly be a `null` somewhere else. If meeting such a situation, we can probably use the postfix `!` to tell TypeScript that the variable during current logic should be an array of string like the following example:

```typescript
foo!.length; /** no error */
```

##### 4.3.3 Outside Context

The context described by the variable `this`, will be treated as `any` in TypeScript by default, when you using it outside a `class`.

```typescript
class Point {
    constructor(public x, public y) {}
    getDistance(p: Point) {
        let dx = p.x - this.x;
        let dy = p.y - this.y;
        return Math.sqrt(dx ** 2 + dy ** 2);
    }
}

// Reopen the interface
interface Point {
    distanceFromOrigin(): number;
}

Point.prototype.distanceFromOrigin = function () {
    return this.getDistance({ x: 0, y: 0 });
}
```

Same problems as we mentioned above, we won't get any error, like `getDistance` has been misspelled by us. With setting `noImplicitThis`, TypeScript will issue an error when `this` has not been specified as an explicit type. The fix is to use a `this` parameter to give an explicit type in the interface:

```typescript
// in the interface
interface Point {
    distanceFromOrigin(this: Point): number;
}
```

Or in the function itself:

```typescript
Point.prototype.distanceFromOrigin = function (this: Point) {
    return this.getDistance({ x: 0, y: 0 });
};
```

### 5. React

React has been known as a framework, which helps developers manage components in a large project. It similar with AngularJS or Vue, and this section only talks about how we integrate with TypeScript when we used React before. JSX is a well-known template language if you have already developed React before. If not, you can visit [my note](../../JavaScript/Framework/react/jsx_syntax/jsx_syntax.md) before. Corresponding with JSX, TypeScript has also extended itself with TSX for supporting JSX. For example, the following snippet has shown us how to define a hello component in TypeScript:

```typescriptx
/** hello.tsx */
import * as React from 'react';
export interface HelloProps { compiler: string; framework: string; }

export const Hello = (props: HelloProps) => <h1>Hello from {props.compiler} and {props.framework}!</h1>;
```

With classes declaration, we can also define like this:

```typescriptx
/** hello.tsx */
export class Hello extends React.Component<HelloProps /** props */, {} /** state */> {
    render(this: Hello) {
        return <h1>Hello from {this.props.compiler} and {this.props.framework}!</h1>;
    }
}
```

Then, render it inside the main entry `index.tsx`:

```typescriptx
/** index.tsx */
import * as React from 'react';
import * as ReactDOM from 'react-dom';

import { Hello } from './hello';

ReactDOM.render(
    <Hello compiler="TypeScript" framework="React"></Hello>,
    document.getElementById('content')
);
```

_Note: if we import an component defined outside our project like node modules inside the folder `node_modules`, we should use a **relative path** to import rather than only an alias name, as TypeScript won't try looking in that folder._
