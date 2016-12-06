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
```
