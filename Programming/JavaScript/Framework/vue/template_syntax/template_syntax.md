## Template Syntax [Back](../vue.md)

Templates used in Vue is like an extension of HTML, which allows us to declaratively bind data to the rendered DOM. For those templates, Vue has compiled them into Virtual DOM render functions, and figure out the minimal number of components to re-render through its reactivity system when states of components have been changed. (this design is familiar with React)

### 1. Interpolations (内插)

#### 1.1 Text

The most basic form of data biding is text interpolation with using double braces:

```html
<span>{{ message }}</span>
```

This interpolation will be updated when data has been modified, and if you want it to show with a consistent value during rendering, you can use `v-once` directive to do so:

```html
<span v-once>consistent {{ message }}</span>
```

#### 1.2 Raw HTML

Double braces interprets data as plain text, rather than HTML. If you want to inject HTML into an element, `v-html` directive is what you need (note: using `v-html` like `dangerouslySetInnerHTML` in React, will result in XSS vulnerabilities):

```html
<span v-html="rawHTML"></span>
```

#### 1.3 Attributes

In React, we can pass data through attributes with mustache style like following snippet:

```jsx
<component id={data.id}></component>
```

It is unfortunate that Vue has not supported such a feature, and if we want to pass through, we may need to use `v-bind:{attribute}` directive to do so:

```html
<component v-bind:id="data.id"></component>
```

In addition, boolean attributes may work a little differently:

```html
<button v-bind:disabled="isDisabled"></button>
```

`disabled` attribute won't be included in the button when `isDisabled` has the value of `null`, `undefined`, or `false`.

#### 1.4 Expressions

Full power of JavaScript expressions are supported inside all data bindings:

```html
{{ 'abc' + message }}
<div v-bind:id="'list-' + data.id"></div>
```

But only when the expression is **REAL** and **SINGLE** (note: `Math` and `Date` are only two available global variable you can access):

```html
<!-- not an expression -->
{{ const a = 1 }}

<!-- not a single expression -->
{{ if (true) { return message } }}

<!-- unavailable global variables -->
{{ window.navigator.userAgent }} 
```

### 2. Directives

Directives are a kind of attributes named with `v-` prefix, which value is expected to be a single JavaScript expression, except for `v-for`. Their job is to apply side effects to the DOM when the values of theirs have been modified. For instance, `v-if` will remove/insert an element based on the turthiness of the value.

#### 2.1 Arguments

Some directives can take an "argument" right following itself with a colon as a separator, like `v-bind:{attribute}`, `v-on:{event}`, etc.

#### 2.2 Modifiers

Modifiers are special postfixes separated by a dot, which indicate that a directive should be bound in some special way, like `.prevent`, which has told the `v-on` directive to call `event.preventDefault()` while triggered:

```html
<form v-on:submit.prevent="onSubmit"></form>
```

For more details of other modifiers, we can check [here](https://vuejs.org/v2/guide/events.html#Event-Modifiers) .

### 3. Shorthands

Even if the `v-` prefix help identifying Vue specific attributes in templates, sometimes we still feel that it is verbose to use frequently used directives. Therefore, Vue has provided two shorthands for two of the most often used directives, `v-bind` and `v-on`:

```html
<!-- full syntax -->
<a v-bind:href="url">...</a>
<!-- shorthands -->
<a :href="url">...</a>
```

```html
<!-- full syntax -->
<a v-on:click.prevent="handler">...</a>
<!-- shorthands -->
<a @click.prevent="handler">...</a>
```

Why using `:` or `@`? Maybe authors think that these are two valid characters for attribute names parsing under all Vue supported browsers.
