## Sets [Back](./../data_structure.md)

A set is a collection of unique elements, in which elements are also called **members**. 

### Sets Definition

A set containing no members is called the **empty** set. The **universe** is the set of all possible members.

If two sets contain exactly the same members, we consider them as equal.

A set is consider a **subset** of another set if all the members of the preceding set are contained in the following one.

```js
function Set() {
    this.dataStore = [];
    
    /** methods */
    this.add = add;
    this.remove = remove;
    this.size = size;
    this.union = union;
    this.interset = interset;
    this.subset = subset;
    this.difference = difference;
    this.show = show;
}
```