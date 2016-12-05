## Linked Lists [Back](./../data_structure.md)

**Linked lists** are sometimes preferred to arrays, and why should we still develop an object-based, linked-list implementation?

### Shortcomings of Arrays

There are several reasons arrays are not always the best data structure to use for organizing data.

In many programming languages, **arrays are fixed in length**, so it is hard to add new data when the last element of the array is reached. Adding and removing data from an array is also difficult because you have to move array elements up or down to reflect either an addition or a deletion. However, these problems do not come up with JavaScript arrays, since we can use the `splice()` function without having to perform additional array element accesses. 


