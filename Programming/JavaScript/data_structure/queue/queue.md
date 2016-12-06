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

function enqueue(element) {
    this.dataStore.push(element);
}

function dequeue() {
    this.dataStore.shift();
}

function front() {
    return this.dataStore[0];
}

function back() {
    var dataStore = this.dataStore;
    return dataStore[dataStore.length - 1];
}

/** to show all elements of an queue */
function toString() {
    var retStr = '';
    var dataStore = this.dataStore;
    var dataStoreLen = dataStore.length;
    
    for (var i = 0; i < dataStoreLen; i++) {
        retStr += dataStore[i] + '\n';
    }
    
    return retStr;
}
```

