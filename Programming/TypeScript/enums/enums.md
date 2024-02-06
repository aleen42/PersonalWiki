## Enums [Back](../TypeScript.md)

### 1. Numeric Enums

As far as ECMAScript 2018, enums are still not a basic type of JavaScript, which has been widely used in any other languages, especially when we want to use a constant name to define numeric values. In TypeScript, we can do so:

```typescript
enum Direction {
    UP = 1,
    DOWN,
    LEFT,
    RIGHT,
}
```

With specified `Direction.UP` as the value `1`, `DOWN` has `2`, while `3` for `LEFT` and `4` for `RIGHT`. Without specified, the first literal will be initialized as `0` by default.


In most cases, enums are mainly used with parameters, which have multiple numeric values, and we want to use a string literal to stand for them, so that code can be more readable.

However, we should remember that any enums should be defined with an initializer before. In other words, the following case is not allowed:

```typescript
enum E {
    A = calcualte(),
    B, /** Error, as 'A' is not content-initialized, which means that B needs an initializer */
}
```

### 2. String Enums

When specifying string enums, any member should be initialized at first:

```typescript
enum Direction {
    UP = 'up',
    DOWN = 'down',
    LEFT = 'left',
    RIGHT = 'right',
}
```

In the case when we want to read a more readable runtime value of a numeric enum, it is useful to convert them into string enums, by giving its meaning.

### 3. Heterogeneous(非同质) Enums (not advised)

Technically, you can define a enum mixed with both string and numeric members, but it is not advised.

### 4. Computed or Constant Members

An enum member is considered constant if:

- It is the first member in the enum and it has no initializer, in which case it's assigned the value `0`:
    ```typescript
    /** E.X is constant as 0 */
    enum E { X }
    ```

- It does not have any initializer or only first member is initialized with number:
    ```typescript
    enum E1 { X, Y, Z }
    enum E2 { X = 1, Y, Z }
    ```

- It is initialized with a constant enum expression (a subset of TypeScript expressions that can be fully evaluated at compile time.):
    ```typescript
    enum FileAccess {
        None,
        Read = 1 << 1,
        Write = 1 << 2,
        IO = Read | Write,
        /** computed member */
        G = 'string literal'.length,    
    }
    ```

### 5. Enum Member Types

There is a special subset of constant enum members that aren't calculated: literal enum members. A literal enum member is a constant enum member with no initialized value, or with values that are initialized to

- any string literal (e.g. `'foo'`, `'bar'`)
- any numeric literal (e.g. `1`, `100`)
- any minus number (e.g. `-1`, `-100`)

As a strong typed language, TypeScript allows us to specify enum member as a type specification like the following snippet:

```typescript
enum ShapeKind { Circle, Square }
interface Circle {
    kind: ShapeKind.Circle;
}

const c: Circle = {
    kind: ShapeKind.Square, /** Error */
};
```

Besides, enum type specification also means for a union of each enum member.

```typescript
enum E {
    Foo,
    Bar,
}

function f(x: E) {
    if (x !== E.Foo || x !== E.Bar) {
        /**             ~~~~~~~~~~~ */
        /** Error! Operator '!==' cannot be applied to types 'E.Foo' and 'E.Bar'. */
    }
}
```

In such a example, we can catch an error that `x` should be either `E.Foo` or `E.Bar`, and it does not make sense to see whether it is equal to both.

### 6. Enums at runtime

Enums are real objects when at runtime, which can be guaranteed With the following snippet:

```typescript
enum E { X }
function test(obj: { X: number }) {
    console.log(obj.X);
}

test(E); /** no error */
```

In addition to creating an object with property names for members, we can also use a *reverse mapping* to access enum names from enum values:

```typescript
enum E { X }
console.log(E.X); /** => 0 */
console.log(E[0]); /** => 'X' */
```

With checking the transformed JavaScript code, we can find that TypeScript has implemented enums with such a period of elegant code:

```javascript
const E;
((Enum = {}) => (Enum[Enum['X'] = 0] = 'X'))(E);
console.log(E.X); /** => 0 */
console.log(E[0]); /** => 'X' */
```

When it comes to string enums, they do not generate a reverse mapping at all.

```typescript
enum E { X = 'x' }
console.log(E.X); /** => 0 */
console.log(E['x']); /** => undefined */
```

### 7. Constant Enums

To avoid paying the cost of extra generated code and additional indirection when accessing enum values, it is possible to use `const` enums to defined constant enums.

```typescript
const enum E { X }
```

Unlike regular enums, constant enums can only have members with constant enum expressions. It means that compiler of TypeScript can directly generate code with constant value members should not be computed values.

```typescript
const arr = [E.X];
```

After generated:

```javascript
const arr = [0/** X */];
```

### 8. Ambient Enums

Ambient enums are used to describe the shape of already existing enum types.

```typescript
declare enum E {
    X = 1,
    C,
    Y = 2,
}

console.log(E.Z); /** TS2339: Property 'Z' does not exist on type 'typeof E' */
```

In fact, an ambient (and non-const) enum member that does not have initializer is *always* considered computed, and it is mainly used for declaration for any enums defined elsewhere. It does not actually create a real enum for you.
