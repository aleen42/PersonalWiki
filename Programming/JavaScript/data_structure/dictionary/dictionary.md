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
```
