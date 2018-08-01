## Quick Started [Back](../vue.md)

As a framework for building user interfaces, vue is mainly designed to focus on the view layer only, so that developers can easily integrate it with other libraries or existing projects. Here is a note for quick starting within Vue according to the official document, and if you want to learn it in deep, it is suggested that going through the whole tutorials step by step.

### 1. Declarative Rendering

With template syntax supported by Vue, we are allowed to declaratively render data to the DOM like following snippet:

```html
<div id="app">
    <!-- using double braces, while single under React -->
    {{ message }}
</div>
```

```js
const app = new Vue({
    el: '#app',
    data: {
        message: 'Hello Vue',
    },
});
```

Correspondingly, Vue will handle all data bindings underneath, which sometimes should be a complicated process, as when we set `app.message` with another text, we can feel its data bindings by checking the change of DOM. What if `data.message` can be generated directly as the element's title? Vue has provided us a specific property, named `v-bind:{property}`, for us, which apparently with `v-` as its prefix.

```html
<div id="app" v-bind:title="message">
    hover to check titles
</div>
```

```js
const app = new Vue({
    el: '#app',
    data: {
        message: `current time: ${new Date().toLocaleString()}`,
    },
});
```

Whenever you hover the application element, the title should be shown with a dynamic data message (like time in this instance).

### 2. Conditionals and Loops

Some logical operations upon templates, like conditional logic or circle logic, are quite a hard requirement for all developers as there are all kinds of data to show.

Take the conditional one as an example, Vue has provided us `v-if`, while `v-for` for circles.

```html
<div id="app">
    <span v-if="visible">Can you see me?</span>
</div>
```

```js
const app = new Vue({
    el: '#app',
    data: {
        visible: true,
    },
});
```

When there is cyclical data like `todo` lists:

```html
<div id="app">
    <p>TODO lists</p>
    <ol>
        <li v-for="todo in todos">{{ todo.content }}</li>
    </ol>
</div>
```

```js
const app = new Vue({
    el: '#app',
    data: {
        todos: [
            {content : 'task1'},
            {content : 'task2'},
            {content : 'task3'},
        ]
    },
});
```

### 3. Handling User Input

The most important thing for Vue is to handle inputs from users, like clicking, typing, etc. `v-on:{event}` directive can be simply used for those cases, like `v-on:click` for listening clicking from users. Certainly, we may also need to create an handler in the Vue instance:

```html
<div id="app">
    <p>{{ message }}</p>
    <button v-on:click="reverse">reverse message</button>
</div>
```

```js
const app = new Vue({
    el: '#app',
    data: {
        message: 'Hello Vue',
    },
    methods: {
        reverse: function () {
            this.message = this.message.split('').reverse().join('');
        },
    },
});
```

From the snippet above, we can apparently know that what we need to do inside an Vue instance is to change its state, rather than modifying its DOM directly, as Vue has given you a favor. What if handling users' typing? `v-model` is a great directive for making two-way biding between from input and the instance:

```html
<div id="app">
    <p>{{ message }}</p>
    <input v-model="message" />
</div>
```

### 4. Components

As projects become larger and larger, a component system is an important concept for developers to manage a large-scale system with different self-contained and reusable components, like React. In Vue, register a component is quite straightforward:

```js
Vue.component('todo-item', {
    template: '<li>this is a todo item</li>',
});
```

And then, in the template, we can import this component like this:

```html
<ol>
    <!-- an instance of the todo-item component -->
    <todo-item></todo-item>
</ol>
```

When we need to generate different items with different data, we can set up a defined property for this component before, named with `todo` here:

```js
Vue.component('todo-item', {
    props: ['todo'],
    template: '<li>{{ todo.content }}</li>',
});
```

As shown above, the component accept a `todo` property to access its `content` member so that it can generate different things. While using the component within template, we can pass data through it like this:

```html
<ol>
    <todo-item todo="task1></todo-item>
    <todo-item todo="task2></todo-item>
    <todo-item todo="task3></todo-item>
</ol>
```

Oops, circle logic has shown its charm here (note: `key` is required when loop Vue components, which will be explained in a later article):

```html
<ol>
    <todo-item
        v-for="task in tasks"
        v-bind:todo="task"
        v-bind:key="task.id"></todo-item>
</ol>
```
