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
    this.isEmpty = isEmpty;
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

function isEmpty() {
    return (this.dataStore.length === 0 ? true : false);
}
```

### Priority Queues

A **priority queue** is one where elements are removed from the queue based on a priority constraint. Due to the priority, we will need another attribute to represent for it:

```js
function enqueue(element, weight) {
    this.dataStore.push({
        element,
        weight
    });
}

function dequeue() {
    var dataStore = this.dataStore;
    var dataStoreLen = dataStore.length;
    
    var index = 0;
    var priority = dataStore[index].weight;
    
    for (var i = 0; i < dataStoreLen; i++) {
        index = (dataStore[i].weight < priority ? i : index);
    }
    
    return dataStore.splice(index, 1);
}
```
