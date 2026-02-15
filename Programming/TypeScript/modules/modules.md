## Modules [Back](../TypeScript.md)

> *Note: since `TypeScript@1.5`, "**internal modules**" have been called "**namespaces**", while "**external modules**" have been called "**modules**".*

As introduced within ECMAScript 2015, JavaScript has a concept named "modules", which has been shared within TypeScript. Modules has its own scope, rather than the global one, which means that variables, functions, classes, etc. declared in a module are not visible outside the module. To create or use a module, we may need to use `export` and `import` statements.

In more detailed, it is the same with JavaScript that a file without any top-level `import` or `export` declarations is treated as a file within a global scope. What the difference is that we can also import or export interfaces, types or any other new kinds of declarations in TypeScript.

```typescript
/** validator.ts */
export interface validator {
    isAcceptable(s: string): boolean;
}
```

```typescript
import {validator} from './validator.ts';
const stringValidator: validator = {
    isAcceptable(s: string): boolean {
        return !!s.length;
    },
}
```

As for detailed syntax around modules, it is not going to discuss in this chapter, except some special points in TypeScript.

To compile a TypeScript file within CommonJS style, we need to use `--module commonjs`, while `--module amd` for AMD style:

```bash
tsc --module commonjs test.ts
```

When it comes to dynamic module loading, `typeof` keywords help us to keep type safety when loading modules within conditions:

1. CommonJS Style:

    ```typescript
    declare function require(module: string): any;
    
    import { Zip } from './zipModule';
    
    if (need) {
        const Zip: typeof Zip = require('./zipModule');
        /** ... */
    }
    ```

2. AMD Style:

    ```typescript
    declare function defined(module: string[], callback: (...args: any[]) => void): void;

    import { Zip } from './zipModule';
    
    if (need) {
        defined(['./zipModule'], (Zip: typeof Zip) => {
            /** ... */
        });
    }
    ```

### 1. Ambient Modules

In computer science, it is common to say that declarations that do not define an implementation "ambient", and typically such modules are defined in `*.d.ts` files, which you can think of as head files within C/C++.

It is more convenient to write declarations into one large head file, rather than define each one in each module. Take the following snippet as an example. Assume that we have a head file, named as `node.d.ts`, in compose of two declarations:

```typescript
/** node.d.ts */
declare module 'url' {
    export interface Url {
        protocol?: string;
        host?: string;
        path?: string;
        hash?: string;
    }
    
    export function parse(url: string): Url;
}

declare module 'path' {
    export function normalize(path: string): string;
    export function join(...paths: any[]): string;
}
```

And then we can reference it and load modules using `import` statements:

```typescript
/// <reference path="node.d.ts">
import * as URL from 'url';
const url: URL.Url = URL.parse('http://aleen42.github.io/PersonalWiki');
```

#### 1.1 Shorthand ambient modules

If we do not want to take the time to write out declarations before using a new module, we can use s shorthand declaration instead:

```typescript
declare module 'url';
```

#### 1.2 Wildcard module declarations

When familiar with Webpack, we usually use different loaders to help us load modules from different types of files like `*.css` , raw text, etc. For such declarations, we can use a prefix to indicate the special loading statements:

```typescript
/** modules.d.ts */
declare module 'text!*' {
    const content: string;
    export default content;
}
```

And then reference it:

```typescript
/// <reference path="modules.d.ts"
import log from 'text!./log.txt';
```

### 2. Guidance around structuring modules

#### 2.1 Export as close to top-level as possible

Export things in a nested structure has reduced its code readability, especially when exporting static methods, it is advised exporting directly in the top level rather than inside the class.

```typescript
export default class Util {
    /** bad */
    static test() { console.log('test'); }
}
```

Why not exporting directly?

```typescript
export class Util {}
export function test() { console.log('test'); }
```

#### 2.2 Use `export default` statements when exporting single class or function

Simply, when exporting single class or function inside a module, use `export default` statements help us to reduce bytes during importing:

```typescript
/** help.ts */
export default function help() { /** ... */ }
```

```typescript
/** rather than import {help} from './help' */
import help from './help';
```

In addition, it is more convenient to name whatever we want during importing:

```typescript
import h from './help';
```

#### 2.3 Exporting and Importing skills

When exporting multiple objects, put them all at top-level like the following snippet:

```typescript
/** help.ts */
export class Type { /** ... */ }
export function help() { /** ... */ }
```

And then explicitly import them, except importing a large number of things:

```typescript
import {Type, help} from './help';
```

Use the namespace import pattern while importing a large number of things:

```typescript
/** modules.ts */
export class Dog { /** ... */ }
export class Cat { /** ... */ }
export class Tree { /** ... */ }
export class Flower { /** ... */ }
```

```typescript
import * as Modules from './modules';
```

#### 2.4 Re-export to extend

modules do not **merge** like global namespace objects would, and if we need to modify some modules, it is recommended to not mutate them, but rather export a new module with mutations. It is quite similar to object-oriented programming (OOP).

```typescript
import Base from './base';
export default class Mutate extends Base {
    /** ... */
}
```
