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

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="zKYdaZ" data-default-tab="js,result" data-user="aleen42" data-embed-version="2" data-pen-title="zKYdaZ" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/zKYdaZ/">zKYdaZ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

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

        document.getElementById(item.id).onfocus = (function(help) {
            return function () {
                showHelp(help);
            };
        })(item.help);
    }
}

setupHelp();
```

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="JRjyvQ" data-default-tab="js,result" data-user="aleen42" data-embed-version="2" data-pen-title="JRjyvQ" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/JRjyvQ/">JRjyvQ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Performance

It's not recommended to define functions inside another functions which will affect the performance of scripts.

```js
function MyObject(name, message) {
    this.name = name.toString();
    this.message = message.toString();

    this.getName = function () {
        return this.name;
    };

    this.getMessage = function () {
        return this.message;
    };
}
```

In the above case, what we should do is to use `prototype` to define outside:

```js
function MyObject(name, message) {
    this.name = name.toString();
    this.message = message.toString();
}

MyObject.prototype = {
    getName:  function () {
        return this.name;
    },

    getMessage: function () {
        return this.message;
    }
};
```

But what if the security of property `name` and `message` is important, what we should do is to give up performance to set `name` and `message` as private:

```js
function f(name, message) {
    var name = name;
    var message = message;

    this.getName = function () {
        return name;
    };

    this.getMessage = function () {
        return message;
    };
}
```
