## Compatibility problems of `for ... in ` [Back](./../underscore.md)

As we known, `for ... in` will only loop through all the **enumerable attributes**. Objects created by the inner constructors of Array and Object will inherit all the nonenumerable attributes like `indexOf()` from String, or `toString()` from Object.