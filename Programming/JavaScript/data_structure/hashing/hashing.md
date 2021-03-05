## Hashing [Back](./../data_structure.md)

Hashing is a common technique for storing data in such a way hat the data can be inserted and retrieved very quickly, which mainly uses a data structure named **hash table**.

Although hash tables provide fast insertion, deletion and retrieval, they perform poorly for operations that involes searching.

### An overview of hashing

Each data element is stored in the array based on an associated data element called **key**, which is mapped into a number in the range of 0 through the hash table size, using a **hashing function**.

Ideally, the hash function stores each ke in its own array element. However, even with an efficient hash function, it's still possible for two keys to hash to the same value, and that's called **collision**. For this reason, we need a strategy for handling collisions when they occur.

### A Hash Table class

```js
function HashTable() {
    this.table = new Array(137);
    
    this.simpleHash = simpleHash;
    this.showDistro = showDistro;
    
    this.put = put;
}
```

#### Choosing a Hash Function

The choice of a hash function depends on the data type of the key. If your key is an integer, then the simplest hash function is to return the key within the size of the array. However, the array size should be a prime number (質數), like 137. Also, if the keys are random integers, then the hash function should more evenly distribute the keys. This type of hashing is known as **modular** hashing.

In many applications, the keys are strings. Choosing a hash function to work with string keys proves to be more difficult and should e chosen carefully.

A simple hash function that seems to work well well is to sum the ASCII value of the letters in the key.

```js
function simpleHash(data) {
    var total = 0;
    var dataLen = data.length;
    
    for (var i = 0; i < dataLen; i++) {
        total += data.charCodeAt(i);
    }
    
    return total % this.table.length;
}
```

Besides, we can also finish up the method `showDistro` and `put`:

```js
function put(data) {
    var pos = this.simpleHash(data);
    this.table[pos] = data;
}

/** show the whole table */
function showDistro() {
    var n = 0;
    var table = this.table;
    var tableLen = table.length;
    
    for (var i = 0; i < tableLen; i++) {
        if (table[i] !== undefined) {
            console.log(i + ': ' + table[i]);
        }
    }
}
```

### A better Hash Function

To avoid collisions, you may need to make sure the array you're using for the hash table is sized to a prime number. With experimentation, we found that to store data `["David", "Jennifer", "Donnie", "Raymond", "Cynthia", "Mike", "Clayton", "Danny", "Jonathan"]` can be stored in a hash table sized with 137. Besides, we may also need a better hash function to avoid collisions:

```js
function betterHash(data) {
    const H = 37;
    var tota = 0;
    var dataLen = data.length;
    
    for (var i = 0; i < dataLen; i++) {
        total += H * total + data.charCodeAt(i);
    }
    
    total = total % this.table.length;
    
    return parseInt(total);
}
```

### Storing and retrieving data in a hash table

```js
function put(key, data) {
    var pos = this.betterHash(key);
    this.table[pos] = data;
}

function get(key) {
    return this.table[this.betterHash(key)];
}
```

### Hash Collisions

A collision occurs when a hash function generates the same key for two or more values.

In this section, we will look at two means of collisions resolution: **separate chaining** and **linear probing**.

#### Separate Chaining

Separate chaining is a technique where each array element of a hash table stores another data structure, such as another array, so that it can physically store more than one piece of data in an array element.

To implement such a technique, we should create the chains firstly:

```js
function buildChains() {
    var table = this.table;
    var tableLen = table.length;
    
    for (var i = 0; i < tableLen; i++) {
        table[i] = [];
    }
}
```

Next, change the method `put()` and `get()` so that they can work with separate chaining.

```js
function put(key, data) {
    var pos = this.betterHash(key);
    var index = 0;
    var pointer = this.table[pos];
    
    while (pointer[index] !== undefined) {
        index++;
    }
    
    pointe[index] = key;
    pointer[index + 1] = data;
}

function get(key) {
    var pos = this.betterHash(key);
    var index = 0;
    var poiner = this.table[pos];
    var len = pointer.length;
    
    for (var i = 0; i < len; i += 2) {
        if (pointer[i] === key) {
            return pointer[i + 1];
        }
    }
    
    return undefined;
}
```

#### Linear Probing

A second technique for handling collisions is called **linear probing** (線性探測). With such a technique, when there is a collision, the program simple looks to see if the next element of the hash table is empty. If so, then store the key and value.

Linear probing should be chosen over separate chaining when your array for storing data can be fairly large.

```js
function HashTable() {
    this.values = [];
    
    /**
     * others
     * ...
     */
}
```

Change the method `put()` and `get()`:

```js
function put(key, data) {
    var pos = this.betterHash(key);
    var table = this.table;
    var valTable = this.values;
    
    while (table[pos] !== undefined) {
        pos++;
    }
    
    table[pos] = key;
    valTable[pos] = data;
}

function get(key) {
    var pos = this.betterHash(key);
    var table = this.table;
    var valTable = this.values;
    
    while (table[pos] !== undefined && table[pos] !== key) {
        if (table[pos] === key) {
            return valTable[pos];
        } else {
            pos++;
        }
    }
    
    return undefined;
}
```

