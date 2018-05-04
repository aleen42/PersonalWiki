## Object [Back](./../JavaScript.md)

Object is another basic data structure used for describing an object in my real life. Each object in JavaScript can has its attributes, methods, or anything else. Even if an object can be described as a sufficient complicated things, objects can be simplified as a collection of key-value pairs.

### 1. Initialization

As same as an `Array`, we can construct an object with a literal or a class:

```js
const object = {}; /** literal */
```

```js
const object = new Object(); /** class */
```

Except that, `Object` has also provided us an method named `create()` to build an object:

```js
const object = Object.create();
```

When it comes to how to define properties (a.k.a keys) for objects, there are several ways we should know:

- Setup Duration
- Dotted/Array-like Assignment
- Property Defining Methods

### 1.1 Setup Duration

Actually, we can define an object and its properties at the same time when initiating it.

```js
const object = {
    prop: 'value',
};
```

When using constructors, we can define like the following snippet:

```js
const object = new Object({ prop: 'value' });
```

However, we may not need to define properties for an object exactly when initiating it in some cases. That's why we need another two ways to define.

### 1.2 Dotted/Array-like Assignment

As we want to define properties later after the initialization of an object, we can temporarily create it first and assign properties into it later:

```js
const object = {};

/** define when we need this property after initializations  */
object.prop = 'value';
object['its prop'] = 'value';
```

The snippet above has shown us how to define properties later with assignment. However, you may be confused what the difference between dotted and array-like is, and when should I use array-like assignment way to do so. Actually, the basic difference between them is that the latter way (array-like assignment) allows us to define properties with illegal characters in comparision with the former way (dotted assignment). For instance, when an define property name has some illegal characters like dot character, '.', JavaScript has considered it as an error in the level of a language:

```js
object.'prop.' = 'value';
```

Besides, when accessing members of an object, there can be some performance problems in some browsers between dotted and array-like accessing. Details can be checked [here](../high_performance/data_access/data_access.md#23-nested-members).

### 1.3 Property Defining Methods

`Object` has also provided a method named `defineProperty()` for developers to define properties for an object:

```js
const object = {};
Object.defineProperty(object, 'prop', { value: 'value' });
```

Probably, you may ask why I should code with a more complicated way to define properties rather than using dotted/array-like assignment to do this for me? The answer is **its power**. The method has actually given us another magical power do more things. Before grasping its power, you can firstly check its definition according to the MDN document:

> The `Object.defineProperty()` method defines a new property directly on an object, or modifies an existing property on an object, and returns the object.

And its syntax:

> Object.defineProperty(*obj*, *prop*, *descriptor*)

Is is the last parameter passed into the method, `descriptor`, which has given us the power to define a different property on an object, in comparison with using dotted/array-like assignment. When it comes to this parameter, we can only pass an object through it, which can be set with following specific properties:

- **value**: the value of the property you want to define
- **writable**: a boolean value for specifying whether the property of this object can be modify again (*Note: even if set with `false`, no error will be thrown if you try to modify the property*). The default value is `false`.

```js
const object = {};
Object.defineProperty(object, 'name', {
    value: 'aleen',
    writable: false,
});

console.log(object.name); /** => aleen */
object.name = 'other';
console.log(object.name); /** => aleen */
```

- **configurable**: a boolean value for specifying whether the property can be configured again after defined, like modifying its writable configuration, or modifying its value, even deleting it. The default value is `false`.

```js
const object = {};
Object.defineProperty(object, 'name', {
    value: 'aleen',
    configurable: false,
});

console.log(object.name); /** => aleen */
delete object.name;
console.log(object.name); /** => aleen */
```

- **enumerable**: a boolean value for specifying whether the property can be accessed by using `for...in` operators, or `Object.entries(obj)`. The default value is `false`.

```js
const object = {};
Object.defineProperty(object, 'name', {
    value: 'aleen',
    enumerable: false,
});

for (var i in object) {
    console.log(object[i]); /** not any output */
}

Object.entries(object).forEach(([, item]) => {
    console.log(item); /** not any output */
});
```

- **get**: a callback function called when there is any accessing operation.
- **set**: a callback function called when there is any assigning operation.

`get` and `set` are both the most powerful features, which have been widely used in many cases, like **data bindings**, **DOM setting**. However, they are only supported **OVER** IE8.

To improve how powerful they are, there is an example when animating. Sometimes, we may need to write some scripts for animating DOM elements by settings one of its CSS properties like `transform`. However, this property have to be set with some prefix like `-webkit-`, or even `-moz-` to support some specific browsers. So, when we try to set a new transformation for this element, we need to set it twice:

```js
const element = document.getElementById('element');
element.style['-webkit-transform'] = 'translateX(10px)';
element.style['-moz-transform'] = 'translateX(10px)';
element.style['transform'] = 'translateX(10px)';

element.style['-webkit-transform'] = 'rotateX(45deg)';
element.style['-moz-transform'] = 'rotateX(45deg)';
element.style['transform'] = 'rotateX(45deg)';
```

This can be a disaster when we need to implement a sufficient complicated animation. What if we use `get` or `set`?

```js
const element = document.getElementById('element');
['translateX', 'rotateX'].forEach(prop => Object.defineProperty(element, prop, {
    set: val => {
        element.style['-webkit-transform']
            = element.style['-moz-transform']
            = element.style['transform']
            = `${prop}(${val})`;
    },
}));

element.translateX = '10px';
element.rotateX = '45deg';
```

Quite elegant, right?

### 2. Loops

As a common sense, if we want to loop all members of an object in JavaScript, we cannot use some standard methods like `Array.prototype.forEach()`, which has been defined after ECMAScript 5.1 (ECMA-262). Sometimes, `for...in` is an alternative, but what if I want to access like an array? The answer is using `Object.entries()` to convert an object into an array:

```js
const Objects = {
    forEach: (obj, fn) => Object.entries(obj).forEach(([index, item]) => fn(item, index)),
};

Object.prototype.forEach = function (fn) {
    Objects.forEach(this, fn);
};
```

And then, we can easily loop an object like the following snippet:

```js
Objects.forEach(obj, item => console.log(item));
obj.forEach(item => console.log(item));
```
