## Computed Properties and Watchers [Back](../vue.md)

### 1. Computed Properties

Even if single expression is supported in text interpolations, it is not reusable and sometimes we may event need a more complicated logical function to generate message for us. **Computed Properties** are what we need to do so. For instance, if we need to reverse a message in several places, it is quite hard to maintain if we code like this snippet:

```html
<div id="app">
    <span class="original">{{ message }}</span>
    <span class="reverse">{{ message.split('').reverse().join('') }}</span>
    <p>
        <h2>same</h2>
        <span class="reverse">{{ message.split('').reverse().join('') }}</span>
    </p>
</div>
```

How about using computed properties to implement this?

```html
<div id="app">
    <span class="original">{{ message }}</span>
    <span class="reverse">{{ reverseMessage }}</span>
    <p>
        <h2>same</h2>
        <span class="reverse">{{ reverseMessage }}</span>
    </p>
</div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {message : 'hello Vue'},
    computed: {
        reverseMessage: function () {
            return this.message.split('').reverse().join('');            
        },
    },
});
```

In additional, computed properties even react after modification of original data:

```js
console.log(vm.reverseMessage); /** => euV olleh */
vm.message = 'GoodBye';
console.log(vm.reverseMessage); /** => eyBdooG */
```

In comparison with computed properties, we can also define the same function as a method instead, and the two approaches are exactly functionally same.

```html
<div id="app">
    <span class="reverse">{{ reverseMessage() }}</span>
</div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {message : 'hello Vue'},
    methods: {
        reverseMessage: function () {
            return this.message.split('').reverse().join('');            
        },
    },
});
```

However, computed properties are cached base on their dependencies specified inside the method, which means that a computed property will only re-evaluate when some if its reactive dependencies, like `this.message` above, have been modified. (note: `Date.now()` is not a reactive dependency) In comparison, a method will always be invoked as long as the component has been re-rendered.

When it comes to **watch properties**, it is a powerful feature Vue has provided for developers to observe and react to data changes on a Vue instance. However, it is better to use computed properties rather than an imperative `watch` callback:

```html
<div id="app">{{ fullName }}</div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        firstName: 'PuiMan',
        lastName: 'Cheui',
        fullName: 'PuiMan Cheui',
    },
    watch: {
        firstName: function (v) { this.fullName = `${v} ${this.lastName}`; },
        lastName: function (v) { this.fullName = `${this.firstName} ${v}`; },
    },
});
```

And how about using computed properties:

```js
const vm = new Vue({
    el: '#app',
    data: {
        firstName: 'PuiMan',
        lastName: 'Cheui',
    },
    computed: {
        fullName: function () { return `${this.firstName} ${this.lastName}`; },
    },
});
```

Quite elegant, right?

Computed properties are by default getter-only, and means that you can't change it directly:

```js
vm.fullName = 'Jackie Chan';
```

What if I need to modify a computed property? We can set a setter for this:

```js
const vm = new Vue({
    el: '#app',
    data: {
        firstName: 'PuiMan',
        lastName: 'Cheui',
    },
    computed: {
        fullName: {
            get: function () { return `${this.firstName} ${this.lastName}`; },
            set: function (v) {
                const [firstName, lastName] = v.split(' ');
                this.firstName = firstName;
                this.lastName = lastName;
            },
        },
    },
});
```

### 2. Watchers

Watchers are mainly used for watching user interfaces like inputting, and it is useful to perform asynchronous or expensive operations in response to changing data.

```html
<div id="app">
    <input v-model="data" />
    {{ result }}
</div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        data: 'default',
        result: '',
    },
    watch: {
        data: function (newData, oldData) {
            /** expansive handling */
            this.handle(newData, oldData).then(result => {
                this.result = result;
            });
        },
    },
    methods: {
        handle: function (newData, oldData) {
            /** ... */
            /** return Promise */
        },
    },
});
```

