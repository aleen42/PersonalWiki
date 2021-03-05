## Generics [Back](../TypeScript.md)

Reusable is a really major part of software engineering while building components. Well-defined components are not always mostly based on its consistent APIs, but its capability of handling flexible data.

That's why **generics** works so widely in languages like C#, Java, or C++. It helps components to work over a variety of types rather than a single one.

Take the following case as a simple example in TypeScript. When there is a function, named `identify`, which should return what it receives, which should be number or string. Then without generics, we will defined like this:

```typescript
function identify(arg: number | string): number | string {
    return arg;
}
```

When you need to change the limitation of received arguments one day, but you do not want to change the defined function itself? **Generics** may be your choice at first.

```typescript
function identify<T>(arg: T): T {
    return arg;
}
```

After that, any data with variety types can be handled easily:

```typescript
identify<string>('hello');
identify<number>(42);

// one day you may need to handle an array of number type
identify<number[]>([1, 2, 3]);
```

Besides, we can also only pass arguments, a.k.a **type argument inference** , where the type will be automatically grasped by the TypeScript compiler to construct `T`:

```typescript
identify('hello');
identify(42);

// one day you may need to handle an array of number type
identify([1, 2, 3]);
```

So when should we use the second way? In most common case, except the compiler fails to infer the type in a much more complex example. Type argument inference helps keeping code shorter and more readable.

Probably you may ask is it different from using `any` type specification? The following two snippets can show how strict generics are:

```typescript
function identify<T>(arg: T): T {
    console.log(arg.length); /** TS2339: Property 'length' does not exist on type 'T'. */
    return arg;
}
```

But what if specify arguments with `any` type:

```typescript
function identify(arg: any): any {
    console.log(arg.length); /** OK? it is OK */
    return arg;
}
```

Apparently, specify with `any` type can not help us catch some typed errors during the layer of language. However, it is reversely what we need TypeScript to do for us.

### 1. Generic Types

Since we talk about functions in the last chapter, we can also use a different name for the generic type parameter:

```typescript
const identify: <U>(arg: U) => U = function <T>(arg: T): T { return arg; };
```

Generic types can be also defined as a call signature of an object literal type:

```typescript
const identify: {<T>(arg: T): T} = function <T>(arg: T): T { return arg; };
```

This leads us to know how about defining a generic interface in TypeScript:

```typescript
interface Identify {
    <T>(arg: T): T;
}

const identify: Identify = function <T>(arg: T): T { return arg; };

/**
 * TS2322: Type '<T>(arg: number) 
 * => number' is not assignable to type 'Identify'.  
 *  Types of parameters 'arg' and 'arg' are incompatible.  
 *    Type 'T' is not assignable to type 'number'.
 */
const otherIdentify: Identify = function (arg: number): number { return arg; };
```

Certainly, we can also move the generic parameter to be a parameter of the whole interface like this, :

```typescript
interface Identify<T> {
    (arg: T): T;
}

const identify: Identify<number> = function <number>(arg: number): number { return arg; };
```

### 2. Generic Classes

In addition to generic interfaces, or generic functions, we can also create generic classes.

*Note: but **NOT** generic enums and namespaces.*

```typescript
class GenericNumber<T> {
    value: T;
    add: (x: T) => T;
}
```

Assume that I need to create two number classes with `number` and `string` types, and we can use such a `GenericNumber` class like this:

```typescript
const floatNumber = new GenericNumber<number>();
floatNumber.value = 0;
floatNumber.add = function (x: number) { return (this.value += x); };

const stringNumber = new GenericNumber<string>();
stringNumber.value = '0';
stringNumber.add = function (x: string) { return `${parseFloat(this.value) + parseFloat(x)}`; };
```

As we covered in [the section of classes](../classes/classes.md#5-static-properties), a class may have static properties, which can not be generic.

### 3. Generic Constraints

As we know that if we want to access some unknown properties of generic types, TypeScript should warn us to do so:

```typescript
function identify<T>(arg: T): T {
    console.log(arg.length); /** TS2339: Property 'length' does not exist on type 'T'. */
    return arg;
}
```

What if we guarantee that the argument `arg` should have the `length` property, and we can constrain the function to work with all arguments with the `length` property:

```typescript
function identify<T extends { length: number; }>(arg: T): T {
    console.log(arg.length);
    return arg;
}
```

How about use `number` as types?

```typescript
identify<number>(3); /** TS2344: Type 'number' does not satisfy the constraint '{ length: number; }'. */
```

In advanced, we can also declare a type parameter that is constrained by another type parameter. Take the following example, `keyof` keywords has specified that the second parameter should be a key of `T`:

```typescript
function identify<T>(obj: T, key: keyof T): T {
    console.log(obj[key]);
    return obj;
}

identify({a : 1}, 'a');
identify({a : 1}, 'b'); /** TS2345: Argument of type '"b"' is not assignable to parameter of type '"a"'. */
```
