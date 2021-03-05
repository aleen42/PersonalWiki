## How to define a function with dynamical name [Back](./qa.md)

Sometimes, we may meet the case when we need to initialize a function with dynamical name, especially when we want to implement Class extending in JavaScript. Therefore, we may need to know the working around of this problem according to https://stackoverflow.com/a/28665860.

```js
function nameFunction(name, functionBody) {
    return name ?
        new Function ('cb', 'return function '
            + name
            + '(cb) { return cb.call(this, arguments); }')
        : body;
} 
```

Then, we can use this function to implement extending Class under ES5:

```js
function nameFunction(name, functionBody) { /** ... */ }
function extendClass(parent, name, prototype, initialize, callSuper) {
    var constructor = nameFunction(name, function () {
        var self = (this instanceof constructor) ?
            this
            : Object.create(constructor.prototype);
        self = (callSuper && parent.apply(self, arguments)) || self;
        return (initialize && initialize.apply(self, arguments)) || self;
    });
    
    constructor.prototype = Object.assign(Object.create(parent.prototype), prototype);
    constructor.prototype.constructor = constructor;
    return constructor;
}
```
