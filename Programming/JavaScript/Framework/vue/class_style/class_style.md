## Class and Style Bindings [Back](../vue.md)

As mentioned above, we can bind some data of a Vue instance to the DOM via `v-bind:{attribute}`, and actually it is quite useful for binding element's class list and inline styles at the same time. For this reason, Vue provides special enhancements when `v-bind` is used with `class` and `style`, where we can bind a JavaScript object or array.

### 1. Binding HTML Classes

#### 1.1 Through an object

Like we bind an object to the class of an element through following snippet:

```html
<div v-bind:class="{ active: isActive }"></div>
```

It means that the DOM will toggle class `active` according to the value of the data `isActive`. As for enhancements, Vue has allowed us to bind more than one class name through an object:

```html
<div v-bind:class="{ active: isActive, 'f-dn': isHidden }"></div>
```

Certainly, the change of values of `isActive` or `isHidden` will also trigger changing of class names at the same time. It is a quite powerful feature of data bindings.

In addition, the bound object should not always be inline, and we can directly bind class to an defined object:

```html
<div id="app" v-bind:class="classObject"></div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        classObject: {
            active: false,
            'f-dn': true,
        },
    },
});
```

And of course we can also bind to a computed variable:

```js
const vm = new Vue({
    el: '#app',
    data: {
        isActive: false,
        isHidden: true,
    },
    computed: {
        classObject: function () {
            return {
                active: this.isActive,
                'f-dn': this.isHidden,
            };
        },
    },
});
```

#### 1.2 Through an array

We can pass an array to the class to apply a list of classes:

```html
<div id="app" v-bind:class="[activeClass, hiddenClass]"></div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        activeClass: 'active',
        hiddenClass: 'f-dn',
    },
});
```

And the example above will render:

```html
<div id="app" class="active f-dn"></div>
```

Certainly, what if we need to render class name conditionally, and we can do it with expressions directly:

```html
<div id="app" v-bind:class="[isActive ? activeClass : '', isHidden ? hiddenClass : '']"></div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        activeClass: 'active',
        hiddenClass: 'f-dn',
        isActive: false,
        isHidden: true,
    },
});
```

Uh, it is too redundant, and it is suggested using arrays only when we need to dynamically generate a class.

Vue has also provided us a mixed way to bind classes:

```html
<div id="app" v-bind:class="[{ active: isActive }, hiddenClass]"></div>
```

It means that you can simplify conditional classes when using arrays to bind.

#### 1.3. Components' Classes

When specifying classes for components, those classes will be added to the component's root element without any overwritten operations.

For example, if we declare a component like this:

```js
Vue.component('custom-component', {
    template: '<p class="foo bar"></p>',
});
```

And use with specifying classes:

```html
<custom-component class="baz boo"></custom-component>
```

And finally render like this:

```html
<p class="foo bar baz boo"></p>
```

When specifying bound classes, it is quite familiar:

```html
<custom-component v-bind:class="[activeClass]"></custom-component>
```

And finally render like this:

```html
<p class="foo bar active"></p>
```

### 2. Binding Inline Styles

#### 2.1 Through an object

When it comes to inline styles, passing an object for binding is quite similar with setting CSS sheets:

```html
<div id="app" v-bind:style="{ color: '#a10000', fontSize: fontSize + 'px' }"></div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        fontSize: 20,
    },
});
```

For more cleaner code, it is advised passing objects directly.

#### 2.2 Through an array

Arrays are mainly used for applying multiple style objects to the same element:

```html
<div id="app" v-bind:style="[baseStyle, schemaStyle]"></div>
```

Since `Vue@2.3.0`, we can also provide an array of multiple values to a style property like this, which is required for compatibility usages:

```html
<div id="app" v-bind:style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>
```
