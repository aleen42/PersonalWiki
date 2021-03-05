## Namespaces and Modules [Back](../TypeScript.md)

> *Note: since `TypeScript@1.5`, "**internal modules**" have been called "**namespaces**", while "**external modules**" have been called "**modules**".*

Sometimes it is hard to distinguish namespaces from modules, and this note mainly aims to help us to organize them, and think about when to use them respectively.

### 1. Using Namespaces

The main case of using namespaces is to define properties through multiple files, and concatenate them using `--outFile`. Actually, with a project becoming larger and larger, it is not a good way to structure codes in a Web application by using namespaces. In most modern case, we may prefer to Webpack for a bundling tool.

### 2. Using Modules

The main difference between modules and namespaces is that modules **declare** their dependencies. Modules provide for better code reuse, strong isolation and better tooling support for bundling tools like Webpack. Therefore, modules are the default and the recommended approach to structure code in most common cases.

### 3. Pitfalls (陷阱)

How to avoid pitfalls in using namespaces and modules?

#### 3.1 Reference Statement

Do not try to use the `/// <reference ... />` syntax to refer to a module file, rather than using `import` (ES Module) or `require` (CommonJS) statement.

Such a reference statement is mainly used for specifying where the compiler will look for an ambient module declaration.

```typescript
// module.d.ts
declare module 'Module' {
    export function fn(): string;
}
```

```typescript
/// <reference path="module.d.ts" />
import * as m from 'Module';
```

#### 3.2 Needless Namespaces

Sometimes, it is needless to wrap modules with namespaces.

The following snippet is so confusing:

```typescript
export namespace Shapes {
    export class Triangle { /** ... */ }
    export class Square { /** ... */ }
}
```

When using:

```typescript
import * as shapes from './shapes';
const triangle = new shapes.Shapes.Triangle(); /** shapes.Shapes? */
```
