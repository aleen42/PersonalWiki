## Queues [Back](./../data_structure.md)

A **queue** is a type of list where data are inserted at the end and retrieved from the front, which is an example of a first-in, first-out (FIFO) data structure.

### An array-based Queue Class implementation

```js
function Queue() {
    this.dataStore = [];
    
    this.enqueue = enqueue；
    this.dequeue = dequeue;
    
    this.front = front;
    this.back = back;
    this.toString = toString;
    this.empty = empty;
}
```
