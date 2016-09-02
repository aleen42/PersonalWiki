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
