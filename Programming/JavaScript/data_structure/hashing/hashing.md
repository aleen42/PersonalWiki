## Hashing [Back](./../data_structure.md)

Hashing is a common technique for storing data in such a way hat the data can be inserted and retrieved very quickly, which mainly uses a data structure named **hash table**.

Although hash tables provide fast insertion, deletion and retrieval, they perform poorly for operations that involes searching.

### An overview of hashing

Each data element is stored in the array based on an associated data element called **key**, which is mapped into a number in the range of 0 through the hash table size, using a **hashing function**.

Ideally, the hash function stores each ke in its own array element. However, even with an efficient hash function, it's still possible for two keys to hash to the same value. That's called **collision**.
