## Namespaces [Back](../TypeScript.md)

> *Note: since `TypeScript@1.5`, "**internal modules**" have been called "**namespaces**", while "**external modules**" have been called "**modules**".*

In order to keep track of types and not worry about name collisions with other objects, NameSpacing statements help us to wrap out, instead of putting all of them into the global namespace. For instance, assume that we have two same testing methods defined in one single file, and hope to declare them with different meanings, and then here we can use namespace to work around collisions with same defined methods:

```typescript
namespace Email {
    export function test(email: string): boolean { /** ... */return true; }
}

namespace Phone {
    export function test(phone: string): boolean { /** ... */return true; }
}

Email.test('aleen42@vip.qq.com');
```

The usage is quite similar to an defined object, but namespace can be split into separated files. For example, if we want to define different methods of the same namespace `Email` in different files like this:

> email
>> email.ts

>> test.ts

>> parse.ts

```typescript
/** email.ts */
namespace Email {
    export interface email {
        prefix: string;
        domain: string;
    }
}
```

```typescript
/** test.ts */
/// <reference path="email.ts" />
namespace Email {
    export function test(email: string): boolean { /** ... */return true; }
}
```

```typescript
/** email/parse.ts */
/// <reference path="email.ts" />
namespace Email {
    export function parse(email: string): email {
        /** ... */
        return {
            prefix: 'aleen',
            domain: 'vip.qq.com',
        };
    }
}
```

Once splitting namespaces into different files, we need to guarantee that all files should be loaded during compiling, and with `--outFile` flag, we can compile all input files into one single JavaScript file:

```bash
tsc --outFile email.js email.ts
```

The compiler will automatically concat files based on the reference tags present in such files.

As for namespaces, we can also export them which means we can create nested namespaces like this:

```typescript
namespace Shapes {
    export namespace Polygons {
        export class Triangle {}
        export class Square {}
    }
}

const square = new Shapes.Polygons.Square();
```

If we see that there are a few files exporting a same namespace, and do not think that they will be combined into one. They won't! While a file only declare one namespace to export like `export namespace Foo {`, it is suggested that removing `Foo` and move anything upward a level.

Same as [ambient modules](../modules/modules.md#1-ambient-modules), we can also declare ambient namespace in head files. However, it is not advised using namespaces in modules. Modules have their own scopes, where only exported declarations are visible outside the module. With this in mind, namespaces provide little value when working with modules.

In most cases, namespaces are commonly used for grouping logically-related objects together including types.
