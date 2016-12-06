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
    this.insert = insert;
    this.append = append;
    this.remove = remove;
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
```
