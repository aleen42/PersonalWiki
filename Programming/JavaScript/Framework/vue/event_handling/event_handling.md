## Event Handling [Back](../vue.md)

This chapter only aims to describe how to handle events with Vue.

### 1. DOM Events Listener

If we want to listen to DOM events and handle it, we can use `v-on:<event-type>` directive to do so:

```html
<div id="app" v-on:click="handler"></div>
```

```js
const vm = new Vue({
    el: '#app',
    methods: {
        handler: () => {/** event handler */},
    },
});
```

If you want to pass parameters through inline methods, you can also do this like the following snippet:

```html
<div id="app" v-on:click="handler('param')"></div>
```

```js
const vm = new Vue({
    el: '#app',
    methods: {
        handler: str => { console.log(str);/** => "param" */ },
    },
});
```

What if requiring the original event in the handler? Just pass it with `$event` variable:

```html
<div id="app" v-on:click="handler('param', $event)"></div>
```

```js
const vm = new Vue({
    el: '#app',
    methods: {
        handler: (str, event) => { console.log(event.target);/** => DOM Element */ },
    },
});
```

### 2. Modifiers

#### 2.1 Event Modifiers

As it is very common to call `event.preventDefault()` or `event.stopPropagation()` inside event handlers, and Vue has provided developers a more simple way to let handlers focus more purely on data logic rather than event details, which is named with **event modifiers**:

- `.stop`
- `.prevent`
- `.capture`
- `.self`
- `.once`
- `.passive`

```html
<!-- the click event's propagation will be stopped -->
<a v-on:click.stop="doThis"></a>

<!-- the submit event will no longer reload the page -->
<form v-on:submit.prevent="onSubmit"></form>

<!-- modifiers can be chained -->
<a v-on:click.stop.prevent="doThat"></a>

<!-- just the modifier -->
<form v-on:submit.prevent></form>

<!-- use capture mode when adding the event listener -->
<!-- i.e. an event targeting an inner element is handled here before being handled by that element -->
<div v-on:click.capture="doThis">...</div>

<!-- only trigger handler if event.target is the element itself -->
<!-- i.e. not from a child element -->
<div v-on:click.self="doThat">...</div>
```

_Note: order matters because the relevant code is generated in the same order, which means that different orders will have different impact. `v-on:click.prevent.self` will prevent **all clicks**, while `v-on:click.self.prevent` will only prevent clicks on the element itself._

- `.once`

Since `Vue@2.1.4`, Vue has provided us another modifiers to make sure that event will be only handled at most once:

```html
<!-- the click event will be triggered at most once -->
<a v-on:click.once="doThis"></a>
```

- `.passive`

Since `Vue@2.3.0`, Vue has provided us another modifiers, corresponding to `addEventListener`'s `passive` option:

```html
<!-- the scroll event's default behavior (scrolling) will happen -->
<!-- immediately, instead of waiting for `onScroll` to complete  -->
<!-- in case it contains `event.preventDefault()`                -->
<div v-on:scroll.passive="onScroll">...</div>
```

_Note:_

1. _the `.passive` modifier is especially useful for improving performance on mobile devices._
2. _do not use `.passive` and `.prevent` together, because `.prevent` will be ignored and warning info will be thrown by browsers._

#### 2.2 Key Modifiers

When listening to keyboard events, like `keyup`, `keydown`, etc., we may need to check for common key codes like `13` for the enter key. Vue has also provided developers modifiers for handling simply:

```html
<!-- only call `vm.submit()` when the `keyCode` is 13 -->
<input v-on:keyup.13="submit" />
```

At the same time, there are also aliases for that most commonly used keys:

- `.enter`
- `.tab`
- `.delete` (captures both "Delete" and "Backspace" keys)
- `.esc`
- `.space`
- `.up`
- `.down`
- `.left`
- `.right`

```html
<!-- same as above -->
<input v-on:keyup.enter="submit" />
```

Besides, custom key modifier aliases are also enabled via the global `config.keyCodes` object:

```js
Vue.config.keyCode.f1 = 112; /** enable `v-on:keyup.f1` */
```

Since `Vue@2.5.0`, Vue has supported for any valid key names exposed via [`KeyboardEvent.key`](https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/key/Key_Values) as modifiers by converting them to kebab-case:

```html
<input @keyup.page-down="onPageDown" />
```

_Note: a few keys have inconsistent key code in IE9._

Some system modifier keys have also been supported since `Vue@2.1.0`, which we can used with chained styles:

* `.ctrl`
* `.alt`
* `.shift`
* `.meta` (`⌘` on Macintosh Keyboards, while `⊞` on Windows keyboards, and while `◆` on Sun Microsystems keyboards.)

```html
<!-- Alt + C -->
<input @keyup.alt.67="clear" />
```

_Note: `keyup.ctrl` will only trigger if you release a key while holding down `ctrl`. It won't trigger if you release the `ctrl` key alone. If you do want such behaviour, use the `keyCode` for `ctrl` instead: `keyup.17`._

To specify exactly key code, we can use `.exact` modifier since `Vue@2.5.0`:

```html
<!-- this will fire even if Alt or Shift is also pressed -->
<button @click.ctrl="onClick">A</button>

<!-- this will only fire when Ctrl and no other keys are pressed -->
<button @click.ctrl.exact="onCtrlClick">A</button>

<!-- this will only fire when no system modifiers are pressed -->
<button @click.exact="onClick">A</button>
```

#### 2.3 Mouse button Modifiers

This is new feature since `Vue@2.2.0`:

- `.left`
- `.right`
- `.middle`
