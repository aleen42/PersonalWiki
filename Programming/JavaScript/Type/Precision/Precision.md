## Precision [Back](./../Type.md)

- JavaScrpit numbers also have the same problem of c++, and can approximate 0.1 very closely. But the fact that this number cannot be represented exactly can lead to problems.

```js
var x = .3 - .2;
var y = .2 - .1;
x == y;		//false: the two values are not the same!
x == 0.1;	//false
y == 0.1;	//true
```
