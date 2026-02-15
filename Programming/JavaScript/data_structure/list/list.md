## Lists [Back](./../data_structure.md)

List are one of the most common organizing tools people use in their day-to-day lives, such as to-do lists, top-ten lists, etc.

### A List Class implementation

```js
function List() {
    this.dataStore = [];
    this.size = 0;
    this.pos = 0;
    
    this.clear = clear;
    this.find = find;
    this.toString = toString;
    
    /** Changement Operations */
    this.insert = insert;
    this.append = append;
    this.remove = remove;
    
    /** Traversing */
    this.front = front;
    this.end = end;
    this.prev = prev;
    this.next = next;
    
    this.length = length;
    this.currPos = currPos;
    this.moveTo = moveTo;
    this.getElement = getElement;
    this.isContain = isContain;
}

function append(element) {
    this.dataStore[size++] = element;
}

/** insert the element after the item */
function insert(element, item) {
    var index = this.find(item);
    
    if (index > -1) {
        this.dataStore.splice(index, 0, element);
        this.size++;
        return true;
    } else {
        return false;
    }
}

function find(element) {
    /** return this.dataStore.indexOf(element); */
    var dataStore = this.dataStore;
    var dataStoreLen = dataStore.length;
    
    for (var i = 0; i < dataStoreLen; i++) {
        if (dataStore[i] === element) {
            return i;
        }
    }
    
    return -1;
}

function clear() {
    this.dataStore.splice(0, this.size);
    this.size = 0;
    this.pos = 0;
}

function remove(element) {
    var index = this.find(element);
    
    if (index > -1) {
        this.dataStore.splice(index + 1, 1);
        this.size--;
        
        /** check position */
        if (this.pos > this.size - 1) {
            this.pos = this.size - 1;
        }
        
        return true;
    } else {
        return false;
    }
}

function length() {
    return this.size;
}

function toString() {
    return this.dataStore;
}

function isContain(element) {
    return (this.find(element) > -1);
}

function front() {
    this.pos = 0;
}

function end() {
    this.pos = this.size - 1;
}

function prev() {
    if (this.pos > 0) {
        this.pos--;
    }
}

function next() {
    if (this.pos < this.size - 1) {
        this.pos++;
    }
}

function curPos() {
    return this.pos;
}

function moveTo(pos) {
    if (Object.prototype.toString.call(pos).toLowerCase() === '[object number]' && pos > 0 && pos < this.size - 1) {
        this.pos = pos;
        return true;
    } else {
        return false;
    }
}

function getElement() {
    return this.dataStore[this.pos];
}
```
