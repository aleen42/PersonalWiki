## Modular System Style [Back](./../JavaScript.md)

Today’s websites are evolving into web apps:

- More and more JavaScript is being used.
- Modern browsers are offering a wider range of interfaces.
- Fewer full page reloads → even more code in a page.

As a result there is **a lot of code** on the client side!

Module systems offer the option to split your code base into modules.

### Style

There are multiple standards for how to define dependencies and export modules:

- `<script>`-tag style (without a modular system)
- CommonJS
- AMD
- ES Harmony
- ...

#### `<script>`-tag style

```html
<script src="module1.js"></script>
<script src="module2.js"></script>
<script src="libraryA.js"></script>
<script src="module3.js"></script>
```

Modules export an interface to the global object, i.e. the `window` object.