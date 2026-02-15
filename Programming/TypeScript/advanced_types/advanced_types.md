## Advanced Types [Back](../TypeScript.md)

### 1. Intersection Types (类型交集)

We can combine multiple types into one together, which allows us to specify a type with all features of those types. It is called **intersection types**, specified with `&` notation (`|` notation should be what we clearly know before for specifying [union types](#2-union-types)). For instance, `Person & Serializable & Loggable` means that an object of such a type will have all members of all three types.

Certainly, it does not fit in the classic object-oriented mold. Intersection types are most commonly used for mixins and other concepts:

```typescript
function extend<T, U>(first: T, second: U): T & U {
    const result = <T & U>{};
    for (let id in first) {
        (<any>result)[id] = (<any>first)[id];
    }
    
    for (let id in second) {
        if (!result.hasOwnProperty(id)) {
            (<any>result)[id] = (<any>second)[id];            
        }
    }
    return result;
}

class Person {
    name: string;
    constructor(name: string) { this.name = name; }
}

class Logger {
    log(str: string) { console.log(str); }
}

const PersonLogger: Person & Logger  = extend<Person, Logger>(new Person('aleen42'), new Logger());
console.log(PersonLogger.name); /** => aleen42 */
PersonLogger.log('Hello'); /** => Hello */
```

### 2. Union Types

Union types are more widely used especially when we need to create an array of different types.

```typescript
const arr: (number | string)[] = [0, 1, 'str'];
```

A union type describes a value that can be one of several types, where we use `|` notation to separate each type. Familiar with [the case](../enums/enums.md#5-enum-member-types) mentioned above, TypeScript will catch some error when it is not sure for something with given union types:

```typescript
interface Bird {
    fly();
    layEggs();
}

interface Fish {
    swim();
    layEggs();
}

function getSmallPet(): Fish | Bird {
    return {
        swim() {
            console.log('swim');
        },
        layEggs() {}
    };
}

let pet = getSmallPet();
pet.layEggs(); /** OK */
/**
 * TS2339: Property 'swim' does not exist on type 'Bird | Fish'.
 *   Property 'swim' does not exist on type 'Bird'
 */
pet.swim();
```

### 3. Differentiating Types and Type Guards

#### 3.1 Differentiating Types

Some times we may need to know whether a member of objects can be accessed before calling them, which means for differentiating types in short. Take the example above around [union types](#2-union-types), we may want to call the `swim` method if the `pet` is a kind of `Fish`. However, the following snippet still get errors:

```typescript
pet.swim && pet.swim();
```

To work around this, we may need to use type assertion:

```typescript
(<Fish>pet).swim && (<Fish>pet).swim();
```

#### 3.2 User-Defined Type Guards

In a more elegant way, we can simplify without using type assertions several times by using so-called **type guards** in TypeScript. To define such a type guard, we simply need to define a function whose return type is a **type predicate**.

```typescript
function isFish(pet: Fish | Bird): pet is Fish {
    return !!(<Fish>pet).swim;
}
```

In the above example, `pet is Fish` is the so-called type predicate, where `pet` is the parameter, which should be the name of a parameter from the current function, while `Fish` is the type. Between them is a keyword, named with `is`. Whenever the method with type predicate is called with some variable, TypeScript will **narrow** it to the specific type.

```typescript
isFish(pet) ? pet.swim() : pet.fly(); /** OK, as TypeScript know it should be either one */
```

#### 3.3 `typeof` Type Guards

Sometimes we may not wish to define a method to figure out whether a type is a primitive, such as `number`, `string`, `boolean`, or `symbol`. In such a case, we can just we `typeof` type guards to do that for us.

```typescript
let object: number | string;
console.log(typeof object === 'number' ? object.valueOf() : object.length);
```

#### 3.4 `instanceof` Type Guards

In comparison with `typeof` type guards, `instanceof` type guards are mainly useful for objects created with constructor functions.

```typescript
class Bird {
    fly() {};
    layEggs() {};
}

class Fish {
    swim() {};
    layEggs() {};
}

function getSmallPet(): Fish | Bird {
    return new Fish();
}

let pet = getSmallPet();
pet instanceof Fish ? pet.swim() : pet.fly();
```

### 4. Nullable Types

There are two special types in TypeScript: `null` and `undefined`, which has two different value respectively. As mentioned in [this section](../types/types.md#7-void-null-and-undefined), they can be assignable to anything without enable `strictNullChecks` option. To avoid such a so-called ["billion dollar mistake"](https://en.wikipedia.org/wiki/Null_pointer#History) said by Tony Hoare, it is suggested that enable the check option. Besides, remember that TypeScript treats `null` and `undefined` differently, and it means that `string | null` is quite different from `string | undefined`.

#### 4.1 Optional Parameters and Optional Properties

With enabling `strictNullChecks` option, optional parameters are automatically added with `| undefined`.

```typescript
function f(x: number, y?: number): number {
    return x + y || 0;
}

f(1, undefined); /** OK */
/** TS2345: Argument of type 'null' is not assignable to parameter of type 'number | undefined'. */
f(1, null);
```

The same rule also applies for optional properties:

```typescript
class C {
    a: number;
    b?: number;
}

const c = new C();
/** TS2322: Type 'null' is not assignable to type 'number | undefined'. */
c.b = null;
```

#### 4.2 Type Guards and Type Assertions

Since nullable types are implemented with a union, we may need to use a type guard to avoid the `null` like the following snippet:

```typescript
function f(str: string | null): string {
    return str || 'default';
}
```

In cases where the compiler cannot detect whether a parameter should not be either `null` or `undefined`, we can use the type assertion operator to manually do it for the compiler with using `!` notation.

For example, the method `f` has wrapped a function named with `wrap`, where the compiler cannot know whether a outside scoped variable (`str`) should not be either `null` or `undefined`, and it should throw an error:

```typescript
(function f(str: string | null) {
    function wrap(): void {
        /** error TS2531: Object is possibly 'null'. */
        console.log(str.length);
    }

    str = str || 'default';
    wrap();
})(null);
```

Therefore, to work around this for the compiler, we can use such a type assertions to tell the compiler that `str` should not be either `null` or `undefined`:

```typescript
(function f(str: string | null) {
    function wrap(): void {
        console.log(str!.length); /** OK */
    }

    str = str || 'default';
    wrap();
})(null);
```

### 5. Type Aliases

Type aliases help us to create a new name of a specific type, which are sometimes similar to interfaces, but can name primitives, unions, tuples, and any other types.

```typescript
type Name = string;
type NameResolve = () => string;
type NameOrResolver = Name | NameResolve;

function f(name: NameOrResolver): Name {
    if (typeof name === 'string') {
        return name;
    } else {
        return name();
    }
}
```

Like interfaces, type aliases can also be generic:

```typescript
type Container<T> = { value: T; };
```

Or even refer to itself:

```typescript
type Tree<T> = {
    value: T;
    left: Tree<T>;
    right: Tree<T>;
};
```

How about combine with interfaces?

```typescript
type LinkedList<T> = T & { next: LinkedList<T>; };
interface Person {
    name: string;
}

let people: LinkedList<Person>;
console.log(people.name);
console.log(people.next.name);
```

But remember that type aliases are not allowed as right value directly:

```typescript
/** TS2456: Type alias 'Person' circularly references itself. */
type Person = Array<Person>; 
```

When it comes to differences between **type aliases** and **interfaces**, one is incorrect according to the official document, where it declared that:

> interfaces create a new name that is used everywhere. Type aliases don't create a new name --- for instance, error messages won't use the alias name.

Actually since `TypeScript@2.1`, the error message should be same:

```typescript
type PointAlias = { x: number; y: number; };
interface PointInterface { x: number; y: number; }

/** TS2322: Type '{ x: number; }' is not assignable to type 'PointAlias'. */
const pointAlias: PointAlias = { x: 1 };
/** TS2322: Type '{ x: number; }' is not assignable to type 'PointInterface'. */
const pointInterface: PointInterface = { x: 1 }; 
```

Clearly, we can apparently know the error message from a specific type.

As for the declaration that type aliases cannot be implemented or extended? **Incorrect either**. We can actually do so:

```typescript
type Point = { x: number; y: number; };
interface ThreeDimensions extends Point {
    z: number;
}
```

Or even implement them:

```typescript
type Point = { x: number; y: number; };
class X implements Point {
    x: 2;
    y: 3;
}
```

Combining both type aliases and interfaces is also allowed for us:

```typescript
type Point = { x: number; y: number; };
interface Shape {
    area(): number;
}

class Rectangle implements Point, Shape {
    x: 2;
    y: 3;
    area(): number { return this.x * this.y; }
}
```

However, the problem should be due to TypeScript itself, as in a common case, we should obey two principles between using interfaces and type aliases:

1. Use **interfaces** when it is used to implemented or extended.
2. Use **type aliases** when an interface is too complicated to describe by a direct type.

### 6. Literal Types

When needing to specify that a string must have some certain values, **string literal types** are usually the way to go:

```typescript
type Easing = 'ease-in' | 'ease-out' | 'ease-in-out';
function animate(dx: number, dy: number, easing: Easing): void { /** ... */ }
/** TS2345: Argument of type '"uneasy"' is not assignable to parameter of type 'Easing'. */
animate(0, 0, 'uneasy');
```

The following snippet is same with above one:

```typescript
function animate(dx: number, dy: number, easing: 'ease-in'): void;
function animate(dx: number, dy: number, easing: 'ease-out'): void;
function animate(dx: number, dy: number, easing: 'ease-in-out'): void;
function animate(dx: number, dy: number, easing: string): void { /** ... */ }
```

*Note: Similar to string literal types, TypeScript also has numeric literal types.*

Both string and numeric literal types act like enum member types as mentioned [here](../enums/enums.md#5-enum-member-types) above.

```typescript
enum Easing {
    EASE_IN = 'ease-in',
    EASE_OUT = 'ease-out',
    EASE_IN_OUT = 'ease-in-out',
}

function animate(dx: number, dy: number, easing: Easing): void { /** ... */ }
```

### 7. Discriminated Unions (可辨识联合)

**Discriminated Unions**, a.k.a **Tagged Unions** or **Algebraic Data Types**, are a type of data structures in compose of a set of data tagged with a specific type. Take the following snippet in TypeScript as an example:

```typescript
interface Square {
    kind: 'square';
    size: number;
}

interface Rectangle {
    kind: 'rectangle';
    width: number;
    height: number;
}

interface Circle {
    kind: 'circle';
    radius: number;
}
```

There are three kinds of interfaces, among them there is a common `kind` property. It is so-called the **discriminant** or **tag**. If we put them into a union, it is actual discriminated union:

```typescript
type Shape = Square | Rectangle | Circle;
function area(s: Shape) {
    switch (s.kind) {
    case 'square':
        return s.size ** 2;
    case 'rectangle':
        return s.width * s.height;
    case 'circle':
        return Math.PI * s.radius ** 2;
    }
}
```

What if we do not handle the case of `Triangle` if we declare our unions with `Square | Rectangle | Circle | Triangle`, TypeScript compiler won't tell us to cover all cases by default:

```typescript
type Shape = Square | Rectangle | Circle | Triangle;
function area(s: Shape) {
    switch (s.kind) {
    case 'square':
        return s.size ** 2;
    case 'rectangle':
        return s.width * s.height;
    case 'circle':
        return Math.PI * s.radius ** 2;
    }
    /** OK, by default */
}
```

If we do need the compiler to notify us, there are two ways to work around.

One is to turn on `--strictNullChecks` and specify a return type:

```typescript
type Shape = Square | Rectangle | Circle | Triangle;
function area(s: Shape): number {
    switch (s.kind) {
    case 'square':
        return s.size ** 2;
    case 'rectangle':
        return s.width * s.height;
    case 'circle':
        return Math.PI * s.radius ** 2;
    }
    /** OK, by default */
}
```

Then, the compiler should throw an error to tell us that the returned value can be `undefined` when `s` is a kind of `Triangle`.

And the other way is to use the `never` type that the compiler uses to check for exhaustiveness:

```typescript
function assertNever(x: never): never {
    throw new Error("Unexpected object: " + x);
}

type Shape = Square | Rectangle | Circle | Triangle;
function area(s: Shape) {
    switch (s.kind) {
    case 'square':
        return s.size ** 2;
    case 'rectangle':
        return s.width * s.height;
    case 'circle':
        return Math.PI * s.radius ** 2;
    default:
        /** TS2345: Argument of type 'Triangle' is not assignable to parameter of type 'never'. */
        return assertNever(s);
    }
}
```

That's because the method `assertNever` should check that `s` is of type `never` after all other cases have been removed. If we forget a case, then `s` has a real type which is not assignable to the type `never`.

### 8. Polymorphic `this` Types

Sometimes we need to return `this` for supporting chaining calling methods. For such kinds of methods, we can declare the return value as a `this` type:

```typescript
class Calculator {
    public constructor(protected value: number = 0) {}

    public add(val: number): this {
        this.value += val;
        return this;
    }
    
    public mul(val: number): this {
        this.value *= val;
        return this;
    }
}

new Calculator().add(1).mul(3);
```

With specifying as a polymorphic `this` types, we can also extend such a class without implement such kinds of methods again, as the compiler can know what instance `this` really points to:

```typescript
class ScientificCalculator extends Calculator {
    public constructor(value: number = 0) {
        super(value);
    }

    public sin(): this {
        this.value = Math.sin(this.value);
        return this;
    }
}

new ScientificCalculator().add(1).mul(3).sin()
```

### 9. Index Types

In JavaScript, it is common to pick a subset of properties from an object:

```js
const pluck = (obj, names) => names.map(name => obj[name]);
```

In TypeScript, if we want to declare types for such a method, we can use **index type query** and **indexed access** operators:

```typescript
function pluck<T, K extends keyof T> (obj: T, names: K[]): T[K][] {
    return names.map(name => obj[name]);
}
```

In the snippet above, `keyof T` is so-called **index type query** operator, and the compiler will declared it as a union of known, public property names of T:

```typescript
type Person = {
    name: string;
    age: number;
};

const props: keyof Person = 'name'; /** same as 'name' | 'age' */
```

*Note: use it rather than hard coding with specific unions, as it is dynamically generated*

`T[K]` is another operator we would like to talk about, which is so-called **indexed access** operator. If we will call `pluck` like this:

```typescript
const person: Person = {
    name: 'aleen42',
    age: '25',
};

pluck(person, ['name']);
```

The compiler will dynamically treat `T[K]` as the type `Person[('name' | 'age')]`.

What if we declare a type with only string index signatures?

```typescript
type Person<T> = {
    [key: string]: T;
};
```

`keyof Person<number>` will just be `string`, while `Person<number>['name']` will just be `number`.

### 10. Mapped Types

Mapped types allow us to create new types based on old types, like declaring all properties in the old type as `readonly`, or optional.

```typescript
type Readonly<T> = {
    readonly [P in keyof T]: T[P];
};

type Optional<T> = {
    [P in keyof T]?: T[P];
};
```

And then, we can use them like the following snippet:

```typescript
type ReadonlyPerson = Readonly<Person>;
type OptionalPerson = Optional<Person>;
```

With mapped types, we can also declare properties in a convenient way:

```typescript
type Config = {
    [C in ('option1' | 'option2' | 'option3')]: boolean;
};
```

It is the same with a hard-coded list of properties:

```typescript
type Config = {
    option1: boolean;
    option2: boolean;
    option3: boolean;
};
```

In addition, `Nullable` is also a general mapped types commonly used in TypeScript:

```typescript
type Nullable<T> = {
    [P in keyof T]: T[P] | null;
};
```

As we can see, the result type of all properties is some variant of `T[P]`, making the transformation [**homomorphic**](https://en.wikipedia.org/wiki/Homomorphism)(同态). It means that the mapping applies only to properties of `T` rather than others. It is helpful as the compiler knows that it can copy all the existing property modifiers before adding any new ones.

Take an example to show how to wrap the properties of a type:

```typescript
type Proxy<T> = {
    get(): T;
    set(value: T): void;
};

type Proxify<T> = {
    [P in keyof T]: Proxy<T[P]>;
};

function proxify<T>(obj: T): Proxify<T> {
    /** wrap proxies */
    const result = {} as Proxify<T>;
    for (const prop in obj) {
        if (obj.hasOwnProperty(prop)) {
            result[prop] = {
                value: obj[prop],
                get() {
                    return result[prop].value;
                },
                set(value) {
                    result[prop].value = value;
                },
            };
        }
    }
    return result;
}
```

What if unwrapping the proxies? That's pretty easy:

```typescript
function unproxify<T>(proxies: Proxify<T>): T {
    const result = {} as T;
    for (const prop in proxies) {
        if (proxies.hasOwnProperty(prop)) {
            result[prop] = proxies[prop].get();
        }
    }
    return result;
}
```

### 11. Conditional Types

Since `TypeScript@2.8`, there has been **conditional types**, which allow us to express non-uniform type mappings.

```typescript
T extends U ? X : Y
```

The type above means when the type system has enough information to conclude that `T` is assignable to `U`, then the type is `X`, otherwise the type is `Y`.

For instance, the following example has shown that returned type will be `string` or `number`:

```typescript
declare function func<T extends boolean>(x: T): T extends true ? string : number;

func(Math.random() < 0.5);
```

Nested conditional types are also supported:

```typescript
type TypeName<T> =
    T extends string ? 'string' :
    T extends number ? 'number' :
    T extends boolean ? 'boolean' :
    T extends undefined ? 'undefined' :
    T extends Function ? 'undefined' :
    'object';

type T0 = TypeName<string>;  /** 'string' */
type T1 = TypeName<'a'>;  /** 'string' */
type T2 = TypeName<true>;  /** 'boolean' */
type T3 = TypeName<() => void>;  /** 'function' */
type T4 = TypeName<string[]>;  /** 'object' */
```

However, there is sometimes no sufficient information for picking a branch directly to evaluate like the following case:

```typescript
type Foo = {
    name: string;
};

declare function f<T>(x: T): T extends Foo ? string: number;

function foo<U>(x: U) {
    /** Cannot decide until foo is called */
    const a: string | number = f(x);
}
```

#### 11.1 Distributive Conditional Types

When conditional types are passed with distributive types like a union of types, they will be automatically distributed over union types:

```typescript
/** 'string' | 'function' */
type T10 = TypeName<string | (() => void)>;
/** 'string' | 'object' | 'undefined' */
type T12 = TypeName<string | string[] | undefined>;
/** 'object' */
type T11 = TypeName<string[] | number[]>;

type BoxedValue<T> = { value: T };
type BoxedArray<T> = { array: T[] };
type Boxed<T> = T extends any[]
    ? BoxedArray<T[number]>
    : BoxedValue<T>;

type T20 = Boxed<string>; /** BoxedValue<string> */
type T21 = Boxed<number[]>; /** BoxedArray<number> */
/** BoxedValue<string> | BoxedArray<number> */
type T22 = Boxed<string | number[]>;
```

Notice that `T` has the additional constraint `any[]` in the type `Boxed<T>`, making it possible to refer to the element type of the array as `T[number]`.

In advanced, the distributive property of conditional types can also conveniently be be sued to **filter** or **differ** union types:

```typescript
type Diff<T, U> = T extends U ? never : T;
type Filter<T, U> = T extends U ? T : never;

type T30 = Diff<'a' | 'b' | 'c' | 'd', 'a' | 'c'>; /** 'b' | 'c' */
type T31 = Filter<'a' | 'b' | 'c', 'a' | 'c' | 'f'>; /** 'a' | 'c' */
type T32 = Diff<string | number | (() => void), Function>; /** string | number */
type T33 = Filter<string | number | (() => void), Function>; /** () => void */
```

Based on filtering union types, we can easily filter out non-nullable types:

```tyepscript
type NonNullable<T> = Diff<T, null | undefined>;

type T34 = NonNullable<string | number | undefined>; /** string | number */
type T35 = NonNullable<string | string [] | null | undefined>; /** string | string[] */
```

How about combining with [mapped types](#10-mapped-types)?

```typescript
type FunctionalProperty<T> = {
    [K in keyof T]: T[K] extends Function ? T[K] : never;
};

interface Part {
    id: number;
    name: string;
    update(name: string): void;
}

type T40 = FunctionalProperty<Part>; /** update(name: string): void */
```

*Note: conditional types cannot refer to themselves recursively similar to [union](#2-union-types) and [intersection](#1-intersection-types-类型交集) types.*

#### 11.2 [Type Inference](../type_inferences/type_inferences.md) in Conditional Types

Within the `extends` clause of a conditional type, it is allowed to use `infer` declarations to infer a type variable. For instance, the following snippet has extracted the return type of a function type if it has:

```typescript
type ReturnType<T> = T extends (...args: any[]) => infer R ? R : any;
```

Take a more complicated case as an example to show how to use `infer` keyword:

```typescript
type Unpacked<T> = 
    T extends (infer U)[] ? U :
    T extends (...args: any[]) => infer U ? U :
    T extends Promise<infer U> ? U :
    T;

type T0 = Unpacked<string>; /** string */
type T1 = Unpacked<string[]>; /** string */
type T2 = Unpacked<() => string>; /** string */
type T3 = Unpacked<Promise<string>>; /** string */
type T4 = Unpacked<Promise<string>[]>; /** Promise<string> */
type T5 = Unpacked<Unpacked<Promise<string>[]>>; /** string */
```

If there is multiple options for the same type variable in co-variant positions, TypeScript compiler will take a union of them:

```typescript
type Foo<T> = T extends { a: infer U, b: infer U} ? U : never;
type T10 = Foo<{ a: string, b: string }>; /** string */
type T11 = Foo<{ a: string, b: number }>; /** string | number */
```

Likewise, TypeScript compiler will take an intersection of them when in contra-variant positions:

```typescript
type Bar<T> = T extends { a: (x: infer U) => void, b: (x: infer U) => void } ? U : never;
type T10 = Bar<{ a: (x: string) => void, b: (x: string) => void }>; /** string */
type T11 = Bar<{ a: (x: string) => void, b: (x: number) => void }>; /** string & number */
```

When there is a list of overloads, inferences will take the last one:

```typescript
declare function foo(x: string): number;
declare function foo(x: number): string;
declare function foo(x: string | number): string | number;
type T30 = ReturnType<typeof foo>; /** string | number */
```

#### 11.3 Predefined Conditional Types

Some commonly used conditional types have been predefined in `lib.d.ts`:

* `Exclude<T, U>`: Exclude from `T` those types that are assignable to `U`.
* `Extract<T, U>`: Extract from `T` those types that are assignable to `U`.
* `NonNullable<T>`: Exclude `null` and `undefined` from `T`.
* `ReturnType<T>`: Obtain the return type of a function type.
* `InstanceType<T>`: Obtain the instance type of a constructor function type.

More example can be checked [here](https://www.typescriptlang.org/docs/handbook/advanced-types.html#example-3).
