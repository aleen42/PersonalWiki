## Type Inferences [Back](../TypeScript.md)

In TypeScript, type inferences are always happened anywhere, wherever you define a variable without explicitly declaring its type. For instance, the following variable `x` is inferred to be `number` directly.

```typescript
const x = 3;
```

### 1. Best Common Type

In advanced, TypeScript background engine will also calculate the best common type when given with an array:

```typescript
const arr = [0, 1, null];
```

Take the snippet above as an example, TypeScript will explore types of each members and calculated the best common type for such a variable:

```typescript
/** same as */
const arr: (number | null)[] = [0, 1, null];
```

However, not all the things can be ideal. In such an example, we hole that TypeScript can infer the variable to a type of `Animal[]`, but there are no members strictly defined as type `Animal` in the array.

```typescript
class Animal {}
class Cat extends Animal {}
class Dog extends Animal {}
class Horse extends Animal {}

const arr = [new Dog(), new Horse(), new Cat()];
```

So the best common type that infer to is just the union array type: `(Dog | Horse | Cat)[]`. To correct this, instead explicitly provide the type when no one type is a super type of all other candidates:

```typescript
const arr: Animal[] = [new Dog(), new Horse(), new Cat()];
```

### 2. Contextual Type

Contextual typing occurs when the type of an expression is implied by its location. For example:

```typescript
window.onmousedown = function (mouseEvent) {
    console.log(mouseEvent.clickTime); /** TS2339: Property 'clickTime' does not exist on type 'MouseEvent' */
};
```

As shown above, `mouseEvent` has been inferred to a type named `MouseEvent` according to its location. What if explicitly declaring the parameter accepted as `any`, the contextual type is ignored, and means no error any more.

```typescript
window.onmousedown = function (mouseEvent: any) {
    console.log(mouseEvent.clickTime); /** OK */
};
```

Besides, contextual typing applies in many cases including right hand sides of assignments, type assertions, members of object and array literals, and return statement.
