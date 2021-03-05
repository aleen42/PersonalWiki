## Brief Description [Back](./../TypeScript.md)

Once you learn a new language, what you need firstly is an runtime tool for running your programs coded with this language. As TypeScript is a superset of JavaScript, which means that we can directly run it if we can convert the program into JavaScript. Microsoft has provided us a compiler, which is actually a command line tool, run with Node.js.

### 1. How to run TypeScript

The first step is to install a compiling tool:

```bash
npm i -g typescript
```

And then, create a new file written with TypeScript:

```typescript
/** hello.ts */
function hello(name) {
    return 'hello, ' + name;
}

console.log(hello('aleen'));
```

Compile it and run it:

```bash
tsc hello.ts && node hello.js
```

### 2. Try some new features provided by TypeScript

#### 2.1 Type Annotations

TypeScript has provided us a new feature like type annotations, and we can try it here. Take the example above as another instance, `hello()` method hopes to accept a string rather than other types when it is called, and if we can use type annotations to strictly define this situation in TypeScript, the compiler should throw an error during compilation rather than automatically convert the type of the parameter in JavaScript:

```typescript
/** hello.ts */
function hello(name: string) {
    return 'hello, ' + name;
}

console.log(hello(123));
```

When compiling the snippet above, you'll now see an error in the command line:

```
error TS2082: Supplied parameters do not match any signature of call target: Could not apply type 'string' to argument 1 which is of type 'number'.
error TS2087: Could not select overload for 'call' expression.
```

#### 2.2 Interfaces

What if the method hopes to accept an object like following defined:

```js
{
    firstName: 'PuiMan',
    lastName: 'Cheui'
}
```

TypeScript has provided `interfaces` for us to describes objects:

```typescript
/** hello.ts */
interface Person {
    firstName: string;
    lastName: string;
}

function hello(person: Person) {
    return 'hello, ' + person.firstName + ' ' + person.lastName;
}

console.log(hello({ firstName: 'PuiMan', lastName: 'Cheui' }));
```

#### 2.3 Classes

Furthermore, classes are another language features, which can be used to specify the type of a person like `Student`.

```typescript
class Student {
    fullName: string;
    firstName: string;
    lastName: string;
    schoolNumber: number;
    constructor(firstName: string, lastName: string, schoolNumber: number) {
        this.fullName = firstName + ' ' + lastName + ' (' + schoolNumber + ')';
    }
}
```

In addition, the use of `public` on arguments to the constructor is a shorthand that allows us to automatically create properties with the name:

```typescript
class Student {
    fullName: string;
    constructor(public firstName: string, public lastName: string, public schoolNumber: number) {
        this.fullName = firstName + ' ' + lastName + ' (' + schoolNumber + ')';
    }
}
```

Then, integrate it with the `hello()` methods:

```typescript
/** hello.ts */
/** ... */

interface Person {
    fullName: string;
}

function hello(person: Person) {
    return 'hello, ' + person.fullName;
}

console.log(hello(new Student('PuiMan', 'Cheui', 42)));
```

### 3. Summary

In conclusion, the most basic feature of TypeScript is its **typed** definition, which can help us to know typed error thrown during compilation time. Besides, classes definitions may be able to help us code with OOP (Object-oriented Programming).
