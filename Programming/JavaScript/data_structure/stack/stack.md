## Stacks [Back](./../data_structure.md)

A **stack** is a list of elements that are accessible only from one end of the list, which is called the **top**, which is known as a last-in, first-out (LIFO) data structure, which means that you will firstly access the element stored most recently.

### A Stack implementation

```js
function Stack() {
    this.dataStore = [];
    this.top = 0;
    
    this.push = push;
    this.pop = pop;
    this.peek = peek;
}

function push(element) {
    this.dataStore[this.top++] = element;
}

function pop() {
    return this.dataStore.splice(--this.top, 1);
}
```
