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

In many applications, the keys are strings. Choosing a hash function to work with string keys proveds to be more difficult and should e chosen carefully.

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

