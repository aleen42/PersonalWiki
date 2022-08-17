## How does JavaScript emulate `private` members? [Back](qa.md)

As we all know, the [proposal](../Programming/JavaScript/tc39/stage4/stage4.md#39-class-fields) of `private` instance fields in classes has been pushed towards stage 4 since ES2022. It means that we can define private members inside classes like other OOP languages, which are limited to access outside a class in user code.

How does JavaScript emulate such behaviour? Use [`WeakMap`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakMap). For why? The [MDN document](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakMap#emulating_private_members) has given us the answer:

- Compared to a [`Map`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Map), a `WeakMap` does not hold strong references to the object used as the key, so the metadata shares the same lifetime as the object itself, avoiding memory leaks.
- Compared to using non-enumerable and/or [`Symbol`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol) properties, a `WeakMap` is external to the object and there is no way for user code to retrieve the metadata through reflective methods like [`Object.getOwnPropertySymbols`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/getOwnPropertySymbols).

    ```js
    class A {
        constructor() {
            this[Symbol('#private')] = 'unreachable value?';
        }
    }
    
    // we can access it actually:
    const a = new A();
    a[Object.getOwnPropertySymbols(a)[0]]; // => "unreachable value?"
    ```

- Compared to a closure, the same `WeakMap` can be reused for all instances created from a constructor, making it more memory-efficient, and allowing different instances of the same class to read the private members of each other.

The detailed implementation when the runtime environment does not support the proposal:

```js
const A = (function () {
    // use a closure to ensure that the weak map cannot be accessed outside the class A
    const privates = new WeakMap();
    return class {
        constructor() {
            privates.set(this, {['#private'] : 'unreachable value?'});
        }
        getPrivateValue() {
            return privates.get(this)['#private'];
        }
    }
})();

const a = new A();
// the private member can only be accessed via an exposed method
a.getPrivateValue(); // => "unreachable value?"
```
