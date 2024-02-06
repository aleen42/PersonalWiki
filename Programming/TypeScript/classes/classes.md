## Classes [Back](../TypeScript.md)

Usually before ECMAScript 2015, a.k.a ES6, JavaScript developers commonly use functions and prototype to build up useful components with inheritance. However, it is not a familiar way for most other language developers, where they uses *Classes* to do object-oriented programming. Since ES6, we can also use it to do so, and certainly, TypeScript has also supported this syntax for us.

### 1. Basic

```typescript
class Person {
    firstName: string;
    lastName: string;
    constructor(firstName: string, lastName: string) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    fullName() {
        return `${firstName} ${lastName}`;
    }
}

const Aleen = new Person('PuiMan', 'Cheui');
```

In such a class, we have declared its constructor and a method named as `fullName` which has return a string joined with two properties of this object. We will notice that if we want to access a property of this object, we can use `this`. Similar to any other object-oriented languages, we can also create an instance of this class by using `new` keyword.

### 2. Inheritance

Inheritance is one of the most important pattern commonly used in object-oriented programming. With inheritance, we can extend any class by using `extends` keyword like the following snippet:

```typescript
class Animal {
    move(distance: number = 0) {
        console.log(`The animal has moved ${distance} miles.`);
    }
}

class Dog extends Animal {
    bark() {
        console.log('Woof!');
    }
}

const bobby = new Dog();
bobby.move(1); // move one mile
bobby.bark(); // and bark
```

As we can see, `Animal` here is the base class of `Dog`, which has extend a method named `bark`.

A more complicated situation, where if we define a constructor of the base class?

```typescript
class Animal {
    name: string;

    constructor(name: string) { this.name = name; }
    move(distance: number = 0) {
        console.log(`The animal has moved ${distance} miles.`);
    }
}
```

By default, if we do not declare a constructor for classes, which extends this base class, they will automatically inherit from the base class:

```typescript
class Dog {
    /** automatically inherit constructor */
    bark() {
        console.log('${this.name}: Woof!');
    }
}
```

What if we need to override a new constructor in those classes? We can use `super` keyword to call constructor of their parent class.

```typescript
class Dog {
    constructor(name: string, position: number) {
        super(name); /** same as `this.name = name;` */
        this.position = position;
    }

    bark() {
        console.log('${this.name}: Woof! from ${this.position}');
    }
}
```

### 3. Modifiers

When you have learnt C++, you may know that we can use three keywords (`private`, `protected`, and `public`) to declare whether a member of a class can be accessed within an inherited class or outside the class directly. In TypeScript, we can also use modifiers to do so.

```typescript
class Animal {
    private name: string;
    protected position: number;
    
    public move(distance: number) {
        console.log(`${this.name} has moved ${distance} miles`);
    }
}
```

#### 3.1 Public

Without declaration explicitly, members are `public` by default, which means we can access members outside the class.

#### 3.2 Private

When using `private` modifier to specify members of a class, it can only be accessible within the class, and can not be accessed outside it, even in an inherited class.

```typescript
class Animal {
    private name: string;
    constructor(name: string) { this.name = name; }

    public move(distance: number) {
        console.log(`${this.name} has moved ${distance} miles`);
    }
}

class Dog extends Animal {
    public bark() {
        console.log(`{this.name}: Woof!`); /** Error */
    }
}

console.log(new Animal('bobby').name); /** Error */
```

#### 3.3 Protected

The `protected` modifier acts much like the `private` one, except that it can be accessed within inherited classes. Sometimes it is useful while we need to protect constructors of a base class

```typescript
class Animal {
    protected name: string;
    protected constructor(name: string) { this.name = name; }

    public move(distance: number) {
        console.log(`${this.name} has moved ${distance} miles`);
    }
}

class Dog extends Animal {
    public bark() {
        console.log(`{this.name}: Woof!`);
    }
}

const animal = new Animal('dog'); /** Error: The 'Animal' constructor is protected */
const dog = new Dog('dog'); 
```

#### 3.4 Readonly

In addition, `readonly` keyword can also used for declaring members for ensuring that it can not be edited once initialized.

```typescript
class Animal {
    readonly name: string;
}

const animal = new Animal('dog');
animal.name = 'horse'; /** Error: readonly member */
```

#### 3.5 Parameter Properties

When it comes to parameter properties, we can also define a member in a shorten way like the following snippet shown, by adding modifier before parameters of the constructor:

```
class Animal {
    constructor(readonly name: string) {}
}
```

### 4. Accessors

Getter or setter are most commonly used for taking control of accessing or modifying a member of an object.

*Note: notice side effects that AOP brings.*

Such accessors are quite useful in OOP (Object-oriented Programming), as developers can have some validations before accessing the member of a class. Take the following snippet as an example:

```typescript
class Person {
    public name: string;
}
```

The member `name` of the class `Person` has been set as `public` which means that it cannot avoid any unexpected change arisen from outside. In order to add some validation before setting, getter and setter are what we really need.

```typescript
class Person {
    private _name: string;

    get name(): string {
        return this._name;
    }
    
    set name(name: string) {
        if (isValid()) {
            this._name = name;
        } else {
            console.log('Error: value unvalidated.');
        }
    }
}
```

*Note: accessors are only available when targeting compiler options with ES5 or higher. (For example, a command line tool can accept such a script: `tsc --target ES5 test.ts`).*

### 5. Static Properties

Same as `static` keywords specified in ES6, we can also define some properties or methods of some classes like some util functions in TypeScript:

```typescript
class Email {
    static test(email: string): boolean {
        /** check email */
        /** ... */
        return true;
    }
}
```

Then with such util classes defined, we can directly call the method `test` without creating an instance of this class:

```typescript
Email.test('aleen42@vip.qq.com');
```

Besides, we can also create some *static* members of a class, which are only visible within the class itself, rather than the instance. It simply means that we can access any specified static members of an instance created based on the class, or even through `this` inside the class:

```typescript
class Person {
    static _name = 'person';
    getName(): string { return this._name; /** Error */ }
}

const person = new Person();
console.log(person.name); /** Error */
```

*Note: Any defined members of `Function`, like `name`, cannot be redefined as an static member, as it will throw an error: **Static property 'name' conflicts with built-in property 'Function.name' of constructor function**.*

### 6. Abstract Classes

Abstract classes are commonly used in other languages for describing the structure of a class, and they should be implemented by other classes. As a strong-typed language, TypeScript has also supported for us, but we can only use `extends` keyword to implement abstract classes.

```typescript
abstract class Animal {
    abstract makeSound(): void;
    move(): void {
        console.log('The animal has moved');
    }
}
```

As we can show the example above, `abstract` keyword can also be used to define any methods inside such a class, which means that any inherited classes should implement such a method.

```typescript
class Dog extends Animal {} /** Error */
```

Except that methods should be implemented by an inherited class, other methods can be overridden as an optional way as mentioned before:

```typescript
class Dog extends Animal {
    makeSound(): void {
        console.log('Woof!');
    }

    move(): void {
        console.log('The dog has moved');
    }
}
```

### 7. Advanced

#### 7.1 Constructor Functions

Once we declare any classes, we can use it to specify the type any variables:

```typescript
class Animal {}

let animal: Animal;
animal = new Animal();
```

As class declarations creates a type representing instances of the class, we can also use them in interfaces:

```typescript
class Point {
    x: number;
    y: number;
}

interface Point3d extends Point {
    z: number;
}

const point3d: Point3d = { x: 1, y: 2, z: 3 };
```

Besides, we also create another value after declaring a class that we call the **constructor function**, which should have all the static members of the class:

```typescript
class Animal {
    static animalName = 'animal';
    getName(): string {
        return Animal.animalName;
    }
}

const Dog: typeof Animal = Animal;
Dog.animalName = 'dog';
console.log(Dog.getName); /** => undefined */
const dog = new Dog();
console.log(dog.getName()); /** => "dog" */
```
