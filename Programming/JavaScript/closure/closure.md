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

```html
<p id="help">Helpful notes will appear here</p>
<p>E-mail: <input type="text" id="email" name="email"></p>
<p>Name: <input type="text" id="name" name="name"></p>
<p>Age: <input type="text" id="age" name="age"></p>
```

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

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/zKYdaZ/?height=300&theme-id=21735&default-tab=js,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/zKYdaZ/'>zKYdaZ</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>

function setupHelp() {
    var helpText = [
        {'id': 'email', 'help': 'Your e-mail address'},
        {'id': 'name', 'help': 'Your full name'},
        {'id': 'age', 'help': 'Your age (you must be over 16)'}
    ];
    
    for (var i = 0; i < helpText.length; i++) {
        var item = helpText[i];
        
        document.getElementById(item.id).onfocus = (function(help) {
            return function () {
                showHelp(help);
            }; 
        })(item.help);
    }
}

setupHelp();
```

<iframe height='300' scrolling='no' src='//codepen.io/aleen42/embed/JRjyvQ/?height=300&theme-id=21735&default-tab=js,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/aleen42/pen/JRjyvQ/'>JRjyvQ</a> by aleen42 (<a href='http://codepen.io/aleen42'>@aleen42</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>