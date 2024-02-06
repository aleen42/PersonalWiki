## Interfaces [Back](../TypeScript.md)

In TypeScript, interfaces will play the role of naming types, which is a powerful way to define the structure of types. For example, assume that there is a function, named `output`, which only wants to accept an object, which has at least a member property, named `label`. In TypeScript, with setting up the process of checking, we can code like the following snippet with interfaces:

```typescript
interface OutputObject {
    label: string;
}

function output(object: OutputObject) {
    console.log(object);
}
```

In such a simple example, we can clearly know how to use interface to describe type in TypeScript. Not like interfaces in other languages, we do not have to say that the object we pass through the function implements the interface, it is just a name that we can use to describe types of an object.

### 1. Optional Properties

Certainly, if we need to declare that some optional properties in interfaces, we can use notation `?:` to define like this:

```typescript
interface OutputObject {
    fontSize?: number;
    label: string;
}
```

Take advantage of optional properties, we can still also prevent use of properties that are not part of the interface:

```typescript
function output(object: OutputObject) {
    /** Error: Property 'color' does not exist on type 'OutputObject */ 
    console.log(object.color);
}
```

### 2. Readonly Properties

Some properties should only be initialized when the object is created, and only can be read after it is created. With `readonly` before such a property in TypeScript, we can describe such a requirement:

```typescript
interface Point {
    readonly x: number;
    readonly y: number;
}

const p1: Point = { x: 10, y: 20 };
p1.x = 5; /** error */
```

TypeScript comes with a `ReadonlyArray<T>` type that is the same as `Array<T>`, which has removed all mutating methods:

```typescript
let data: number[] = [1, 2, 3];
let readonlyData: ReadonlyArray<number> = data;

readonlyData[0] = 2; /** error */
readonlyData.push(4); /** error */
readonlyData.length = 0; /** error */
```

As defined as readonly, the array type can not also be assigned to a normal array type:

```typescript
data = readonlyData; /** error */
```

Except for conversion:

```typescript
data = readonlyData as number[];
```

_Note: using `const` for variables while using `readonly` for properties._

### 3. Excess Property Checks

Also take `OutputObject` interface as an example, since it has been defined to describe an object, which should have a member, named `label`, which value should be a string. But what if we pass through an additional property like the following snippet?

```typescript
/** error: 'external' not expected in type 'OutputObject' */
const object: OutputObject = {
    label: 'string',
    external: 'external properties',
};
```

Error should be thrown by TypeScript, as the interfaces has also told TypeScript that the object expects only known properties, like `label` here.

The most simple way to get around this check is to using type assertion:

```typescript
const object: OutputObject = {
    label: 'string',
    external: 'external properties',
} as OutputObject;
```

Certainly, if we are sure that the object can have some extra properties that are used in some special way, it is suggested that describe like this, so that other developers can clearly know that such a interfaces can have excess properties (exactly dynamic key of objects in ES6):

```typescript
interface OutputObject {
    label: string;
    [propName: string]: any;
};
```

### 4. Function Types

Interfaces can also be used to describe a function type, shown as the following snippet:

```typescript
interface SearchFunc {
    (keyword: string): Array<Object>;
}

let search: SearchFunc = function (keyword: string): Array<Object> {
    return [{result: 1}];
};
```

For function types to correctly type-check, the names of the parameters do not need to match, like this example:

```typescript
interface SearchFunc {
    (keyword: string): Array<Object>;
}

let search: SearchFunc = function (kw: string): Array<Object> {
    return [{result: 1}];
};
```

No need to specify types at all, as type-checker of TypeScript will also infer the argument types with specified interfaces:

```typescript
interface SearchFunc {
    (keyword: string): Array<Object>;
}

let search: SearchFunc = function (kw) {
    return [{result: 1}];
};
```

### 5. Indexable Types

Similarly to excess types specification, we can also describe types that we can index, like `a[0]` or `map['china']`.

```typescript
interface StringArray {
    [index: number]: string;
};
```

The interface above has stated that when an array has values, which index is a `number`, it should be a `string`.

While string index signatures are a powerful way to describe the "dictionary" pattern, they also enforce that all properties match their return type.

```typescript
interface Dictionary {
    [index: string]: number;
    length: number; /** ok */
    name: string; /** error, the type of 'name' is not a subtype of the indexer */
}
```

Finally, indexable properties can be also specified as readonly so that we can prevent assignment to the indices:

```typescript
interface ReadonlyStringArray {
    readonly [index: number]: string;
    length: number;
}

const array: ReadonlyStringArray = ['str1', 'str2'];
array.length = 0; /** ok */
array[2] = 'str3'; /** error */ 
```

### 6. Class Types

Interfaces are commonly uses in languages like C#, Java, to enforce that a class meets a particular contract, which is also possible in TypeScript.

```typescript
interface ClockInterface {
    currentTime: Date;
}

class Clock implements ClockInterface {
    currentTime: Date;
    construct(hour: number, minute: number) {/** constructor */}
}
```

Certainly, we can also describe some methods in an interface that should be implemented in the class, like `setTime` in following example:

```typescript
interface ClockInterface {
    currentTime: Date;
    setTime(d: Date): void;
}

class Clock implements ClockInterface {
    currentTime: Date;
    construct(hour: number, minute: number) {/** constructor */}
    setTime(d) {
        this.currentTime = d;
    } 
}
```

_Note: interfaces only describe the public side of a class._

When working with classes and interfaces, we should know that there are _two_ types of interfaces for describing classes: **the type of the static side**, and **the type of the instance side**:

```typescript
/** static side */
interface ClockConstructor {
    new (hour: number, minute: number);
}

interface ClockInterface {
    tick(): void;
}
```

If you want to define a class to implement the type of static side, you may get errors. This is because when a class implements an interface, only the instance side of the class is checked, while the constructor sits in the static side.

```typescript
class Clock implements ClockConstructor {
    constructor(hour: number, minute: number): {}
}
```

The proper way to use them should be like this:

```typescript
class DigitalClock implements ClockInterface {
    constructor(hour: number, minute: number): {}
    tick() {
        console.log('beep beep');
    }
}

class AnalogClock implements ClockInterface {
    constructor(hour: number, minute: number): {}
    tick() {
        console.log('tick tock');
    }
}

const createClock = function (clock: ClockConstructor, hour: number, minute: number) {
    return new clock(hour, minute);
};

const digital = createClock(DigitalClock, 12, 17);
const analog = createClock(AnalogClock, 12, 17);
```

`ClockConstructor` is mainly used for class checking, while `ClockInterface` is mainly used for class implementing.

### 7. Extending Interfaces

Like classes, interfaces can extend each other, which allows us to copy members from one interface into another.

```typescript
interface Shape {
    color: string;
}

interface Square extends Shape {
    width: number;
}

const square: Square = { color: '#a1000', width: 10 };
```

What if extending multiple interfaces?

```typescript
interface Shape {
    color: string;
}

interface Stroke {
    strokeWidth: number;
}

interface Square extends Shape, Stroke {
    width: number;
}

const square: Square = {
    color: '#a1000',
    width: 10,
    strokeWidth: 2,
};
```

How about extending an interface with a class? The interface type can only be implemented by the class or a subclass of it, as the interface has inherited even the private and protected member of the base class.

```typescript
class Control {
    private state: any;
}

interface SelectableControl extends Control {
    select(): void;
}

class Button extends Control implements SelectableControl {
    select() {}
}

class TextBox extends Control {
    select() {}
}

/** error: property 'state' is missing in the type 'Image'. */
class Image implements SelectableControl {
    select() {}
}
```

### 8. Hybrid Types

For JavaScript's dynamic and flexible nature, TypeScript has allowed us to describe types as both a function and an object at the same time:

```typescript
interface Counter {
    (start: number): string;
    interval: number;
    reset(): void;
}

function getCounter(): Counter {
    const counter = function (start) { return 'counter'; } as Counter;
    counter.interval = 10;
    counter.reset = function() {};
    return counter;
}
```
