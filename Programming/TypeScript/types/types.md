## Basic Types [Back](../TypeScript.md)

TypeScript has supported much the same types of the simplest units of data as we expect in JavaScript, like **Number**, **String**, **Structure**, **Boolean**, etc. This chapter mainly aims to make note around basic types of TypeScript.

### 1. Boolean

The most basic data type is the simple `true` / `false` value, which both JavaScript and TypeScript call a `boolean` value:

```typescript
let isDone: boolean = false;
```

### 2. Number

In TypeScript, all numbers are floating point values as same as JavaScript, which get the type, named `number`. Certainly, decimal, hexadecimal, binary or even octal literals are also supported in TypeScript:

```typescript
let decimal: number = 6;
let hex: number = 0xff;
let binary: number = 0b1001;
let octal: number = 0o777;
```

### 3. String

All textual data are both used the type `string` to refer to by JavaScript and TypeScript. As in JavaScript, we can also use double quotes or single quotes to surround textual data in TypeScript:

```typescript
let color: string = '#a10000';
```

**Template Literals** has been widely used since ECMAScript 2016, and in TypeScript, we can also use it with embedded expressions:

```typescript
let str: string = 'Aleen';
console.log(`Hello, ${str}`);
```

### 4. Array

Array types is a basic data type for storing data, and in TypeScript, we can declare this type in two ways. One is to use `[]` literal:

```typescript
let list: number[] = [1, 2, 3];
```

And the other is to code like generic programming:

```typescript
let list: Array<number> = [1, 2, 3];
```

**Tuple** is a new feature for TypeScript to declare an array where the type of a fixed number of elements is known. For instance, we can declare an array type with tuple as a pair of a `string` and a `number`:

```typescript
let list: [string, number];
list = ['hello', 10]; /** OK */
list = [10, 'hello']; /** Error */
```

With tuple specification, accessing operations are also limited as TypeScript has known all types of elements inside this array:

```typescript
console.log(list[1].substr(1)); /** Error */
```

What about elements outside the set of known indices? TypeScript will treat them as a union type of `string` and `number`:

```typescript
list[2] = 'world'; /** OK */
console.log(list[3].toString()) /** OK, as both `number` and `string` has the method `toString()` */
list[4] = true; /** Error */
```

_Note: more details of union types can be checked later._

### 5. Enum

`enum` is one of the helpful addition to the standard set of data types from JavaScript, which is mainly used to specify a type of set contains numeric values in TypeScript:

```typescript
enum Color { Red, Green, Blue }
let color: Color = Color.Blue;
```

Or, we can also specify a specific number for each value:

```typescript
enum Color { Red = 1, Green = 2, Blue = 4 }
```

_Note: If you don't specify the number, the first item is mapped to zero by default._

TypeScript has also supported a handy feature for us to extract names of an enumerable type with a specific indices:

```typescript
enum Color { Red = 1, Green, Blue }
let color: string = Color[2]; /** "Green" */
```

### 6. Any

Any unknown type can be described as `any`, like declaring a dynamic variable for accepting different basic types. In such a case, TypeScript won't throw any type error during compiling time:

```typescript
let notSure: any = 4;
notSure = 'string?'; /** OK */
notSure = true; /** also OK */
```

Remember that do not expect `Object` to play a similar role as `any`, because we can only assign members for it, but not able to access methods.

```typescript
let notSure: any = 4;
notSure.toFixed(); /** as TypeScript not check */

let notSure: Object = 4;
notSure.toFixed(); /** Error: no such a method, named 'toFixed', in the type `object` */ 
```

`any` type can also used to specify an array, composed with different types:

```typescript
let list: any[] = [1, true, 'string'];
```

### 7. Void, Null and Undefined

As the official document said that, `void` type was a little like the opposite of `any`, which we can only assign `undefined` or `null` to it:

```typescript
let unusable: void = void 0;
```

In most cases, `void` type is mainly used for specifying result returned from a function:

```typescript
function warn(): void {
    console.log('only warn');
}
```

In TypeScript, `null` and `undefined` are both a kind of types as same as JavaScript, which are much like `void`. They are subtypes of any other type by default, which means we can assign `null` or `undefined` to any other type like `number`, except enabling `strictNullChecks` options for avoiding a lot of common errors, documented in [this note](../integrations/integrations.md). If we don't ensure whether a specified variable will be assigned with `null` or `undefined`, we can use union types to workaround this situation.

### 8. Never

When there are types of values that never occur, the `never` type is what we need to specify, which is mainly used as the return type for a function expression:

- an arrow function expression that always throws an exception
- a function never returns

```typescript
function error(message: string): never {
    throw new Error(message); /** returning never has an unreachable end point */
}

function infiniteLoop() {
    while(true) {}
}
```

### 9. Object

`object` is a type that represents any non-primitive type, such as `number`, `string`, `boolean`, `symbol`, `null`, or `undefined`.

```typescript
declare function create(o: object | null): void;

create({ prop: 0 }); /** OK */
create(null); /** OK */

create(1); /** Error */
create('string'); /** Error */
create(false); /** Error */
create(undefined); /** Error */
```

### 10. Type Assertions

Type assertions are a way to tell the compiler to trust what developers specify, which is like a type cast in other languages. It has no runtime impact, ans is used purely by the compiler.

There are two types of type assertions, and one is the "angle-bracket" syntax:

```typescript
let someValue: any = 'string';
let strLength: number = (<string>someValue).length;
```

The other is the `as` -syntax:

```typescript
let someValue: any = 'string';
let strLength: number = (someValue as string).length;
```

_Note: when using TypeScript with JSX, only `as` -style assertions are allowed as `<xxx>` will be treated as elements._
