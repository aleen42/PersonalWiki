## Dictionaries [Back](./../data_structure.md)

A dictionary is a data structure that stores data as **key-value** pairs. In JavaScript, the **Object** class is designed to operate as a dictionary. In this chapter, we'll use the features of the Object class to build a Dictionary class.

### The Dictionary Class

The basic for the Dictionary class is the **Array** class rather than the Object class, because we also want to sort the keys of a dictionary, which Object can not support.

```js
function Dictionary() {
    this.dataStore = [];
    this.add = add;
    this.find = find;
    this.remove = remove;
    this.showAll = showAll;
}

function add(key, value) {
    this.dataStore[key] = value;
}

function find(key) {
    return this.dataStore[key];
}

function remove(key) {
    delete this.dataStore[key];
}

function showAll() {
    var dataStore = this.dataStore;

    for (var i in dataStore) {
        console.log(i + ' -> ' + dataStore[i]);
    }
}
```

### Auxiliary (輔助性) Functions for the Dictionary Class

```js
function count() {
    var n = 0;
    
    for (var i in this.dataStore) {
        n++;
    }
    
    /**
     * in this case, you can not use this.dataStore.length
     * as the returned result.
     */
    return n;
}

function clear() {
    var dataStore = this.dataStore;
    
    for (var i in dataStore) {
        delete dataStore[i];
    }
}
```

### Adding Sorting to the Dictionary Class

Even if there is a method to sort for any Array object, it only works well with integer indexes but not string keys. Therefore, we can use another method `Object.keys()` function to solve this problem, which should return an object which has provied the sorting method `sort()`:

```js
function showAll() {
    var dataStore = this.dataStore;

    for (var i in Object.keys(dataStore).sort()) {
        console.log(i + ' -> ' + dataStore[i]);
    }
}
```
