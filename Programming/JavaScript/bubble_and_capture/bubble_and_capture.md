## Event Bubbling and Capturing (事件冒泡與事件捕獲) [Back](./../JavaScript.md)

Both event bubbling and capturing are two ways of event propagation(事件傳播) in the HTML DOM APIs, when an event occurs in an element inside another element, and both elements have registered a handle for that triggered event.

#### Bubbling

**Bubbling** means that the event is first captured and handled by the inner element and then propagated to the outer one.

- IE 5.5: div -> body -> document
- IE 6.0: div -> body -> html -> document
- Mozilla 1.0: div -> body -> html -> document -> window

#### Capturing

**Capturing** means that the event is first captured by the outer element and propagated to the inner one.

Capturing is also called "trickling(滴落)", which helps to remember:

`trickle down, bubble up`

#### Useage

```js
ele.addEventListener('click', function () {
}, [useCapture]);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>