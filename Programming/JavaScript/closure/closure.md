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

### A common mistake

```js
function showHelp(help) {
    document.getElementById('help').innerHTML = help;
}

function setupHelp() {
    var helpText = [
        {'id': 'email', 'help': 'Your e-mail address'},
        {'id': 'name', 'help': 'Your full name'},
        {'id': 'age', 'help': 'Your age (you must be over 16)'}
    ];
    
    for (var i = 0; i < helpText.length; i++) {
        var item = helpText[i];
        
        document.getElementById(item.id).onfocus = function() {
            showHelp(item.help);    /**
                                     * will always show the last help
                                     * because three functions have shared the same item
                                     */
        };
    }
}

setupHelp();
```

Resolution is that you should return a closure function which will create a separate environment for themselves.

```js
function showHelp(help) {
    document.getElementById('help').innerHTML = help;
}

function setupHelp() {
    var helpText = [
        {'id': 'email', 'help': 'Your e-mail address'},
        {'id': 'name', 'help': 'Your full name'},
        {'id': 'age', 'help': 'Your age (you must be over 16)'}
    ];
    
    for (var i = 0; i < helpText.length; i++) {
        var item = helpText[i];
        
        document.getElementById(item.id).onfocus = function() {
            showHelp(item.help);    /**
                                     * will always show the last help
                                     * because three functions have shared the same item
                                     */
        };
    }
}

setupHelp();
```