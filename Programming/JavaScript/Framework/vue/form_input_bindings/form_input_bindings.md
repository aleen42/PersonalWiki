## Form Input Bindings [Back](../vue.md)

With using `v-model` directive, we can create two-way data bindings on form input, textarea, and select elements.

_Note:_

1. _`v-model` will ignore the initial `value`, `checked` or `selected` attributes found on any form elements. It means that we should declare the initial value inside the `data` option of components._
2. _For languages that require an [IME](https://en.wikipedia.org/wiki/Input_method) (Chinese, Japanese, Korean etc.), we should use `input` event instead to detect the change during IME composition._

### 1. Basic Usages

#### 1.1 Text

```html
<input v-model="message" placeholder="input text" />
<p>Message is: {{ message }}</p>
```

#### 1.2 Multiline Text

```html
<textarea v-model="message" placeholder="input multiline text"></textarea>
<p>Message is: {{ message }}</p>
```

#### 1.3 Checkbox

```html
<input type="checkbox" id="checkbox" v-model="checked" />
<label for="checkbox">{{ checked }}</label>
```

If binding multiple checkboxes to an array:

```html
<div id="app">
    <input type="checkbox" id="jack" value="Jack" v-model="checkedNames">
    <label for="jack">Jack</label>
    <input type="checkbox" id="john" value="John" v-model="checkedNames">
    <label for="john">John</label>
    <input type="checkbox" id="mike" value="Mike" v-model="checkedNames">
    <label for="mike">Mike</label>
    <br>
    <span>Checked names: {{ checkedNames }}</span>
</div>
```

```js
const vm = new Vue({
    el: '#app',
    data: {
        checkedNames: [],
    },
});
```

#### 1.4 Radio

```html
<input type="radio" id="one" value="One" v-model="picked" />
<label for="one">One</label>
<br>
<input type="radio" id="two" value="Two" v-model="picked" />
<label for="two">Two</label>
<br>
<span>Picked: {{ picked }}</span>
```

#### 1.5 Select

Single select:

```html
<select v-model="selected">
    <option disabled value="">Please select one</option>
    <option>A</option>
    <option>B</option>
    <option>C</option>
</select>
<span>Selected: {{ selected }}</span>
```

_Note: If the initial value of your `v-model` expression does not match any of the options, the `<select>` element will render in an "unselected" state. On iOS this will cause the user not being able to select the first item because iOS does not fire a change event in this case. It is therefore recommended to provide a disabled option with an empty value, as demonstrated in the example above._

Multiple select (bound to an array):

```html
<select v-model="selected" multiple>
    <option>A</option>
    <option>B</option>
    <option>C</option>
</select>
<br>
<span>Selected: {{ selected }}</span>
```

### 2. Dynamic Bindings

If we need to bind value of form input items to a dynamic property, we can use `v-bind` to achieve that. In addition, it also allows us to bind the input value to non-string values.

#### 2.1 Checkbox

```html
<input
    type="checkbox"
    v-model="toggle"
    true-value="yes"
    false-value="no" />
```

```js
console.log(vm.toggle); /** => yes (checked); no (unchecked) */
```

#### 2.2 Select Options

```html
<select v-model="selected">
    <!-- inline object literal -->
    <option v-bind:value="{ number: 123 }">123</option>
</select>
```

```js
console.log(vm.selected.number); /** => 123 */
```

### 3. Modifiers

- `.lazy`

By default, `v-model` syncs the input with the data after each `input` event (except IME composition), and we can add `.lazy` modifier to instead sync after `change` event.

```html
<!-- synced after "change" instead of "input" -->
<input v-model.lazy="msg" />
```

- `.number`

Even if specify an input element with `number` as its type, its returned should be string. Rather than parse with `parseFloat` each time, we can use `.number` modifier to achieve that.

```html
<input v-model.number="age" type="number" />
```

- `.trim`

If we want to trim user input automatically, we can use `.trim` modifier:

```html
<input v-model.trim="msg" />
```
