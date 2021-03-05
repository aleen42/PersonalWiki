## Functions [Back](../TypeScript.md)

> Functions are the fundamental building block of any applications in JavaScript.

As we can see, a lot things in JavaScript are constructed by Functions, including classes definitions, scopes of variables, and even modules. Within TypeScript, though all of them are reproduced during the layer of languages, functions are still playing a key role in defining any logic.

Just as in JavaScript, functions can be declared as a named function or as an anonymous function:

```typescript
/** named functions */
function add(x, y) {
    return x + y;
}

/** anonymous functions */
const mul = function (x, y) { return x * y; };
```

Similar to JavaScript, TypeScript has all the same mechanisms of functions, and if you want to know more about how **closures** work in functions, you can visit the note [here](../../JavaScript/closure/closure.md), which should not be within the scope of this note.

### 1. Function Types

For parameters defined in a function, we can specify their types, as well as the returned value from the function.

```typescript
function add(x: number, y: number): number {
    return x + y;
}

const mul = function (x: number, y: number): number { return x * y };
```

Besides, we can also type the whole function with arrow-like functions:

```typescript
const mul: (x: number, y: number) => number =
    function (x: number, y: number): number { return x * y };
```

Certainly, when typing the whole function, we can use a more specific name for parameters, helping with readability. Like the following snippet, as long as the type of functions meet as a valid type, any name we give the parameters in the function type can be regardless.

```typescript
const mul: (base: number, factor: number) => number =
    function (x: number, y: number): number { return x * y };
```

As we can see above, the declared returned type is used a flat arrow for specifying. In addition, we can also figure out the type of the whole function on one side of the equation, but not the other in TypeScript:

```typescript
const mul: (base: number, factor: number) => number =
    function (x, y) { return x * y };
```

This is so called "contextual typing", a form of type interfacing, which helps reducing amount of effort to keep programs typed.

### 2. Optional Parameters

In JavaScript, any parameters defined in the function are not assumed to be required, which means you can pass no parameters even the function needs. However, with strong typing principle, TypeScript has explicitly needed you to specify clearly which parameters are optional, while which are required.

```typescript
function mul(x: number, y: number): number {
    return x * y;
}

mul(1); /** Error, too few parameters */
mul(1, 2, 3); /** Error, too many parameters */
mul(1, 2); /** Alright */
```

If you want to specify an optional parameter, you can use `?` notation like the following snippet:

```typescript
function mul(x: number, y: number, z?: number): number {
    return x * y * (z || 1);
}

mul(1, 2, 3); /** Alright */
mul(1, 2); /** Alright */
```

What if using default value for optional parameters? Just assign with a value:

```typescript
function mul(x: number, y: number, z = 1): number {
    return x * y * z;
}

mul(1, 2, 3); /** Alright */
mul(1, 2); /** Alright */
```

*Note: any default-initialized parameter is treated as optional.*

Even if default-initialized parameters do not need to occur after required parameters according to the official document, it is not suggested as this should be a code principle in TypeScript, even in other languages.

### 3. Rest Parameters

Since ES6(ECMAScript 2015), rest operators has been widely used in JavaScript for accepting groups of parameters, instead of using `arguments. And in TypeScript, the feature are also supported.

```typescript
function mul(x: number, ...factors: number[]) {
    return x * factors.reduce(function (res: number, factor: number) {
        return res * factor;
    }, 1);
}
```

Although `factors` is a required parameter, it can be treated as a boundless number of optional parameters, when passed by an empty array.

### 4. Functions' Context

When it comes to the context of a function in JavaScript, it can also ben another rite of passage, especially when meeting with `this` parameter inside a function. As a superset of JavaScript, it is also important to know contexts of functions in TypeScript.

Take a simple example, `this` inside a function of an object should always refer to the object itself.

```typescript
const obj = {
    name: 'object',
    getName: function () { return this.name; },
};
console.log(obj.getName()); /** => "object" */
```

Except the case of returning a function or passing a function as an argument:

```typescript
const obj = {
    name: 'object',
    getNameFn: function () { return function () { return this.name; }; },
    getFn: function (fn): string { return fn(); },
};
console.log(obj.getNameFn()()); /** => Error, as `this` is referred to Window or undefined under strict mode */
console.log(obj.getFn(function () { return this.name; })); /** => Error, as `this` is referred to Window or undefined under strict mode */
```

In order to workaround, we always use a temporary variable to store `this`, or even use `Function.prototype.bind` after ES5 so that the context of the function can be changed.

```typescript
const obj = {
    name: 'object',
    getNameFn: function () {
        const self = this;
        return function () { return self.name; };
    },
    getFn: function (fn) { return fn.bind(this)(); },
};
console.log(obj.getNameFn()()); /** => "object" */
console.log(obj.getFn(function () { return this.name; })); /** => "object" */
```

Besides, within arrow functions released by ES6, we can also get right `this` context outside arrow functions like this:

```typescript
const obj = {
    name: 'object',
    getNameFn: function () {
        return () => { return this.name; };
    },
};
console.log(obj.getNameFn()()); /** => "object" */
```

In TypeScript, specifying types of `this` helping us avoiding problems of wrong contexts:

```typescript
class Obj {
    name: string;
    getName(this: void): void {
        console.log(this.name); /** Error: name is not a member of void type */
    }
}
```

### 5. Overloads

A quite useful feature of functions in TypeScript is **Overloads**, with which we can easily define multiple functions with same name, and returned different results based on parameters passed to such defined functions.

```typescript
/** overloads */
function mul(x: number, y: number): number;
function mul(x: number, y: number, z: number): number;
function mul(w: number, x: number, y: number, z: number,): number;
/** implements */
function mul(x, ...factors: number[]): number {
    return x * factors.reduce(function (result, factor) {
        return result * factor;
    }, 1);
}

console.log(mul(1, 2, 3, 4));
console.log(mul(1, 2, 3, 4, 5)); /** Error: Expected 2-4 arguments, but got 5 */
```

Not similar to other strong typed languages, you can only implement one function in TypeScript, even if you can declared multiple types of a function with a same name.
