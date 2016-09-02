## Closures [Back](./../JavaScript.md)

**Closures are functions** that refer to independent (free) variables, which are usually defined in an enclosing scope. These functions **remember the environment** in which they were created.

```js
function f() {
    var independentVariable = 'test';
    
    function display() {
        /** using an independent variable `independentVariable` */
        console.log(independentVariable);
    }
    
    display();
}
```

### Emulating private property

```js
var counter = (function() {
    var privateCounter = 0;
    
    function changeBy(val) {
        privateCounter += val;
    }
    
    return {
        increment: function() {
            changeBy(1);
        },
        decrement: function() {
            changeBy(-1);
        },
        value: function() {
            return privateCounter;
        }
    };
})();

console.log(counter.value()); // logs 0
counter.increment();
counter.increment();
console.log(counter.value()); // logs 2
counter.decrement();
console.log(counter.value()); // logs 1
```
