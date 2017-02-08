## The internal function: `createAssigner()` [Back](./../underscore.md)

In underscore, you may have to know this important function, which is named `createAssigner()`. Before discussing about what it has done, we may also have to know another three APIs calling this function firstly. They're `_.extend()`, `_.extendOwn()`, and `_.defaults()`.

Firstly, when we want to merge all properties from an object b to an object a, we may remember the function `Object.assign(a, b)`. That's exactly what `_.extend()` has done. And `_.extendOwn()`will only copy own properties of one object to another one.

