## Type Compatibility [Back](../TypeScript.md)

Type Compatibility in TypeScript is based on structural subtyping, which is a way of relating types based on their members. In contrast with [nominal-typed](https://en.wikipedia.org/wiki/Nominal_type_system) languages like C# or Java, the following snippet should be an error as the `Person` class does not explicitly declared itself as being an implement of the interface `Named`:

```typescript
interface Named {
    name: string;
}

class Person {
    name: string;
}

let p: Named;
p = new Person(); /** OK in TypeScript */
```

TypeScript's structural type system was designed based on how JavaScript code was typically written. It is anonymous objects like function expressions and object literals that make it more natural to act like a structural type system instead of a nominal one.

*Note: when a type system has a kind of properties which can not be known at compile-time to be safe, it is said to not be "sound (稳固)". The places where TypeScript allows such cases should be carefully considered.*

To know more clearly about type compatibility, we can take another example, where `x` is compatible with `y`, if `y` has at least the same members as `x`:

```typescript
interface Named {
    name: string;
}

let x: Named;
let y = { name: 'aleen42', location: 'China' };

x = y; /** It is OK, as its compatibility */
```

The same rule for assignment is used when checking function call arguments:

```typescript
interface Named {
    name: string;
}

function greet(person: Named) {
    console.log(`Hello, ${person.name}`);
}

let y = { name: 'aleen42', location: 'China' };
greet(y);
```

However, it can not be used when there is direct assignment:

```typescript
interface Named {
    name: string;
}

/**
 * TS2322: Type '{ name: string; location: string; }' is not assignable to type 'Named'.
 *   Object literal may only specify known properties, and 'location' does not exist in type 'Named'.
 */
let x: Named = { name: 'aleen42', location: 'China' };

function greet(person: Named) {
    console.log(`Hello, ${person.name}`);
}

/**
 * TS2345: Argument of type '{ name: string; location: string; }' is not assignable to parameter of type 'Named'.
 *   Object literal may only specify known properties, and 'location' does not exist in type 'Named'.
 */
greet({ name: 'aleen42', location: 'China' });
```

### 1. Functions

Should what kinds of functions be considered compatible? As long as the assignment has front parts arguments of the assigned function, because ignoring extract function parameters is quite common in JavaScript:

```typescript
let x = (): number => 0;
let alien = (a: string): number => 0;
let y = (a: number): number => 0;
let z = (a: number, b: string): number => 0;

z = y;
z = x;

/** TS2322: Type '(a: number) => number' is not assignable to type '() => number' */
x = y;
/**
 * TS2322: Type '(a: string) => number' is not assignable to type '(a: number, b: string) => number'.
 *   Types of parameters 'a' and 'a' are incompatible.
 *     Type 'number' is not assignable to type 'string'.
 */
z = alien;
```

How are return types treated? The type system in TypeScript enforces that the source function's return type be a subtype of the target type's return type.

```typescript
let x = () => ({ name: 'aleen42' });
let y = () => ({ name: 'aleen42', location: 'China' });

x = y;
/**
 * TS2322: Type '() => { name: string; }' is not assignable to type '() => { name: string; location: string; }'.
 *   Type '{ name: string; }' is not assignable to type '{ name: string; location: string; }'.
 *     Property 'location' is missing in type '{ name: string; }'.
 */
y = x;
```

#### 1.1 Function Parameter Bivariance (协变)

As for polymorphism, function parameters' type can also be compatible for a more specialized type:

```typescript
enum EventType { Mouse, Keyboard }

interface Event { timestamp: number; }
interface EventMouse extends Event { x: number; y: number }
interface EventKey extends Event { keyCode: number }

function listenEvent(eventType: EventType, handler: (n: Event) => void) {
    /* ... */
}

// Unsound, but useful and common
listenEvent(EventType.Mouse, (e: EventMouse) => console.log(e.x, e.y));

// Undesirable alternatives in presence of soundness
listenEvent(EventType.Mouse, (e: Event) => console.log((<EventMouse>e).x, (<EventMouse>e).y));
listenEvent(EventType.Mouse, <(e: Event) => void>((e: EventMouse) => console.log(e.x, e.y)));
```

As mentioned above, this kind of parameters is unsound but commonly useful in many JavaScript patterns.

#### 1.2 Optional Parameters and Reset Parameters

When it comes to optional and reset parameters, they are interchangeable when comparing functions for compatibility.

When a function has a reset parameter, it is treated as if it were an infinite series of optional parameters.

```typescript
function invoke(args: any[], callback: (...args: any[]) => void) {
    /** ... */
}

/** unsound, as callback will provide any number of arguments, beside x and y. */
invoke([1, 2], (x, y) => console.log(x, y));
invoke([1, 2], (x?, y?) => console.log(x, y));
```

#### 1.3 Overloads

When a function has overloads, they must be compatible for the source function, so that the overloads function can be called in all the same situations as the source function.

```typescript
/** TS2394: Overload signature is not compatible with function implementation. */
function invoke(x: number): void;
function invoke(x: string, y: number): void;

function invoke(x: string, y: number): void { console.log(x, y); }
```

### 2. Enums

Both enums and numbers are compatible with each other, but enum values from different enum types are considered incompatible:

```typescript
enum Status { READY, PENDING }
enum Color { RED, BLUE, YELLOW }

let s: Status = Status.READY;
s = 1;
/* TS2322: Type 'Color.RED' is not assignable to type 'Status'. */
s = Color.RED;
```

### 3. Classes

Classes work similar to object literal types with one exceptions: *classes will have both static and instance types*. When comparing two objects with a class type, only members of the instance are compared, while static members and constructors have no any effect.

```typescript
class Animal {
    name: string;
    constructor(name: string, sound: string) {}
}

class Size {
    name: string;
    constructor(name: string) {}
}

let a: Animal;
let s: Size;

/** both OK */
a = s;
s = a;
```

When it comes to private and protected members in a class, if the target type contains a private member, then the source type must also contain a private member that originated from the same class.

```typescript
class Animal {
    private name: string;
    constructor(name: string, sound: string) {}
}

class Size {
    private name: string;
    constructor(name: string) {}
}

let a: Animal;
let s: Size;

/**
 * TS2322: Type 'Animal' is not assignable to type 'Size'.
 *   Types have separate declarations of a private property 'name'.
 */
a = s;
s = a;
```

Likewise, the same applies for an instance with protected members.

```typescript
class Animal {
    protected name: string;
    constructor(name: string, sound: string) {}
}

class Horse extends Animal {
    protected name: string;
    constructor(name: string, sound: string) { super(name, sound); }
}

class Size {
    private name: string;
    constructor(name: string) {}
}

let a: Animal;
let h: Horse;
let s: Size;

a = h; /** OK */
/**
 * TS2322: Type 'Animal' is not assignable to type 'Size'.
 *   Types have separate declarations of a private property 'name'.
 */
a = s;
```

### 4. Generics

When comparing with two objects with generics specification, type parameters only affect the compatible result when they are used to specify parts of the generics. For example,

```typescript
interface Empty<T> {}
let x: Empty<number>
let y: Empty<string>

x = y; /** OK, as T is not used for specify a part of Empty */
```

When used? Error of course.

```typescript
interface NotEmpty<T> {
    data: T;
}
let x: NotEmpty<number>
let y: NotEmpty<string>

/**
 * TS2322: Type 'NotEmpty<string>' is not assignable to type 'NotEmpty<number>'.
 *   Type 'string' is not assignable to type 'number'.
 */
x = y;
```

For generic types that do not have their type arguments specified, compatibility is checked by specifying `any` in place of all unspecified type arguments.

```typescript
let identity = function<T>(x: T): T { /** ... */return x; }
let reverse = function<U>(y: U): U { /** ... */return y; }
identity = reverse; /** OK, because (x: any) => any matches (y: any) => any */
```
