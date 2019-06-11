## @augments [Back](../jsdoc.md)

> This tag is the same with @extends

The `@augments` or `@extends` tag indicates that a symbol inherits from, and potentially adds to, a parent symbol. It can be used to document class-based and prototype-based inheritance.

### 1. Prototype-based Inheritance

```js
/**
 * Animal
 * @constructor
 */
function Animal() {
    this.alive = true;
}

/**
 * Horse
 * @constructor
 * @extends Animal 
 */
function Horse() {
    this.name = 'horse';
}

Horse.prototype = new Animal();
Horse.prototype.speak = function() { this.alive && console.log(this.name); };
```

### 2. Class-based Inheritance

```js
/**
 * Animal
 * @class 
 */
class Animal {
    constructor() {
        this.alive = true;
    }
}

/**
 * Horse
 * @class
 * @extends Animal 
 */
class Horse extends Animal {
    constructor() {
        super();
        this.name = 'horse';
    }
    
    speak() { this.alive && console.log(this.name); }
}
```
