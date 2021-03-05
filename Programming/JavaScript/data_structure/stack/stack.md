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
    
    this.clear = clear;
    this.length = length;
}

function push(element) {
    this.dataStore[this.top++] = element;
}

function pop() {
    if (this.top === 0) {
        return null;
    }

    return this.dataStore.splice(--this.top, 1);
}

function peek() {
    return this.dataStore[this.top - 1];
}

function length() {
    return this.top;
}

function clear() {
    this.dataStore.splice(0, this.top);
    this.top = 0;
}
```
