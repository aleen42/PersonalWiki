## Event Bubbling and Capturing (事件冒泡與事件捕獲) [Back](./../JavaScript.md)

Both event bubbling and capturing are two ways of event propagation(事件傳播) in the HTML DOM APIs, when an event occurs in an element inside another element, and both elements have registered a handle for that triggered event.

#### Bubbling

**Bubbling** means that the event is first captured and handled by the inner element and then propagated to the outer one.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>