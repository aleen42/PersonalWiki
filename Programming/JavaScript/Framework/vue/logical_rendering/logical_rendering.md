## Logical Rendering [Back](../vue.md)

As we mentioned inside a forward note, around template syntax of Vue, we can use some directives to help rendering logically, like conditional rendering or cyclical rendering.

### 1. Conditional Rendering

#### 1.1 `v-if`

In Vue, we can use `v-if` directive to achieve conditional rendering:

```html
<h1 v-if="isTitleShown">Title</h1>
```

And in comparison, there is `v-else` directive to achieve a opposite rendering:

```html
<label v-if="ok">Yes</label>
<label v-else>No</label>
```

Since `Vue@2.1.0`, `v-else-if` directive has also been supported for conditional rendering:

```html
<label v-if="ok">Yes</label>
<label v-else-if="fine">Yes</label>
<label v-else>No</label>
```

But we should remember that `v-else` or `v-else-if` directives should be placed after `v-if`, so that Vue can recognize it.

Certainly, what if I don't want to register the same condition for a few elements like this:

```html
<h1 v-if="article">Title</h1>
<p v-if="article">Paragraph 1</p>
<p v-if="article">Paragraph 2</p>
```

The most common way to work around this is to wrap them with an invisible container like `<div>`. Vue has also provided us an element for grouping, `<template>`.

```html
<template v-if="article">
    <h1>Title</h1>
    <p>Paragraph 1</p>
    <p>Paragraph 2</p>
</template>
```

With conditional rendering, Vue tries to render elements as efficiently as possible, and always reuse some elements instead of rendering. For instance, there is a requirement for implementing different entries of login. It is quite efficient to reuse the same input area for different kinds of login forms.

```html
<template v-if="loginType === 'username'">
  <label>Username</label>
  <input name="id" placeholder="Enter your username">
</template>
<template v-else>
  <label>Email</label>
  <input name="id" placeholder="Enter your email address">
</template>
```

With upper snippet, if we switch the type of login, specified by `loginType`, Vue won't render a new DOM element for `input`, and only change the `placehoder` attribute instead. It means that user's input won't be erased after switching.

But what if we really need to implement two new DOM for `input` elements? Just adding a `key` attribute with unique values:

```html
<template v-if="loginType === 'username'">
  <label>Username</label>
  <input name="id" placeholder="Enter your username" key="username">
</template>
<template v-else>
  <label>Email</label>
  <input name="id" placeholder="Enter your email address" key="email">
</template>
```

_Note: the `<label>` elements are still efficiently reused in the example above._


#### 1.2 `v-show`

`v-show` is another directive, which is similar to `v-show` functionally, and the only difference is that DOM won't be removed when using `v-show`, as the directive only toggle the CSS property `display` of elements.

If we pay more attention to the overloads of unmounting elements from the DOM tree, especially when we toggle an element quite often, it is suggested to use `v-show`, rather than `v-if`.

### 2. Cyclical Rendering

When there is a list of items to loop for rendering, `v-for` directive is what we need, which requires a special syntax in the form of `item in items`:

```html
<ul id="app">
    <li v-for="item in items">{{ item.name }}</li>
</ul>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        items: [
            { name: 'item1' },
            { name: 'item2' },
            { name: 'item3' },
        ],
    },
});
```

Inside `v-for` blocks, we have full accesses to parent scope properties, and `v-for` also supports an optional second argument for the index of current item:

```html
<ul id="app">
    <li v-for="(item, index) in items">{{ parentMessage }}-{{ index }}: {{ item.name }}</li>
</ul>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        parentMessage: 'Todo List',
        items: [
            { name: 'item1' },
            { name: 'item2' },
            { name: 'item3' },
        ],
    },
});
```

_Note: we can use `item of items`, which is similar to `for...of``` in JavaScript._

In comparison with arrays, we can also use `v-for` directive to iterate through an object:

```html
<ul id="app">
    <li v-for="value in item">{{ value }}</li>
</ul>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        item: {
            key1: 'value1',
            key2: 'value2',
        },
    },
});
```

And the second optional argument is also supported for accessing keys:

```html
<ul id="app">
    <li v-for="(value, key) in item">{{ key }}: {{ value }}</li>
</ul>
```

The third optional argument is for accessing corresponding index:

```html
<ul id="app">
    <li v-for="(value, key, index) in item">{{ key }}({{ index }}): {{ value }}</li>
</ul>
```

_Note: when iterating over an object, the order is based on the key enumeration order of `Object.keys()`, which is not consistent across different browsers._

#### 2.1 Efficient Rendering with Patches

Quite similar to React, Vue has also use "in-place patch" strategy to replace DOM rather than to re-render a whole list after data has been modified. To give Vue a hint for tracking elements, we have to specify a unique key for each element of a list:

```html
<ul id="app">
    <li v-for="item in items" :key="item.id">{{ item.name }}</li>
</ul>
```

As for changing whole array through some mutation methods like `reverse()`, `filter()`, or `concat()`, etc, Vue has optimized the process of replacing DOM to reduce overloads as large as it can.

However, due to limitations in JavaScript, Vue **cannot** detect the following changes to an array:

- directly setting/adding/removing item with the index
- modifying the length of the array

```js
const vm = new Vue({
    el: '#app',
    data: {
        parentMessage: 'Todo List',
        items: [
            { name: 'item1' },
            { name: 'item2' },
            { name: 'item3' },
        ],
    },
});

vm.items[1] = 'x'; /** NOT reactive */
vm.items[4] = 'new'; /** NOT reactive */
vm.items.length = 2; /** NOT reactive */
```

To work around this problem, we can do so:

```js
/** set item through `Vue.set()` */
Vue.set(vm.items, 1, 'x');
/** remove item through `Array.prototype.splice` */
vm.items.splice(1, 1);
```

Certainly, with defined Vue instances, we can use `vm.$set` to replace `Vue.set`, and it is just an alias:

```js
vm.$set(vm.items, 1, 'x');
```

Additionally, Vue has also not allowed us to add new root-level property to an already created instance like this:

```js
vm.newItems = [/** ... */]; /** NOT reactive */
```

When we want to assign a number of new properties to an existing object through some functions like `Object.assign` or `_.extend`, we should create a fresh object, instead of changing the original one:

```js
/** DO NOT do that */
Object.assign(vm.items, { name: 'what' });
/** SHOULD create a fresh object instead */
vm.items = Object.assign({}, vm.items, { name: 'what' });
```

#### 2.2 Filtered/Sorted Results

We can use methods or computed properties inside `v-for` directive to implement filtered or sorted results during cyclical rendering:

```html
<ul id="app">
    <li v-for="item in even(items)">{{ item.name }}</li>
</ul>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        items: [
            { name: 'item1' },
            { name: 'item2' },
            { name: 'item3' },
        ],
    },
    methods: {
        even: items => items.filter((item, index) => index % 2 === 0),
    },
});
```

How about using computed properties?

```html
<ul id="app">
    <li v-for="item in evenItems">{{ item.name }}</li>
</ul>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        items: [
            { name: 'item1' },
            { name: 'item2' },
            { name: 'item3' },
        ],
    },
    computed: {
        evenItems: function () {
            return this.items.filter((item, index) => index % 2 === 0);
        },
    },
});
```

#### 2.3 Range Rendering

`v-for` directive can also take an integer for range specifying:

```
<div id="app">
    <span v-for="n in 10">{{ n }}</span>
    <!-- 1 2 3 4 5 6 7 8 9 10 -->
</div>
```

#### 2.4 Group Rendering

Similar to `v-if`, `v-for` directive can also take `<template>` to loop for rendering groups of templates.

```html
<ul id="app">
  <template v-for="item in items">
    <li>item: </li>
    <li>{{ item.name }}</li>
  </template>
</ul>
```

#### 2.5 Combined with conditional rendering

`v-for` directive can be used with `v-if` at the same time, where `v-for` has a higher priority.

```html
<ul id="app">
    <li v-for="item in items" v-if="!item.done">{{ item.name }}</li>
</ul>
```

#### 2.6 `v-for` with components

Like a normal element, we can directly use `v-for` inside a custom component, but what we should remember is specifying `key` since `Vue@2.2.0`. If we want to pass value to the component it self, `props` is the only way:

```html
<custom-component
    v-for="(item, index) in items"
    v-bind:item="item"
    v-bind:index="index"
    v-bind:key="item.id"
></custom-component> 
```
