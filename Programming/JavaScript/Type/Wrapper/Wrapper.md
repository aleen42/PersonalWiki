## Wrapper Objects [Back](./../Type.md)
### Overview
- we can use properties to an object, a **value** or a **method**

```js
var s = "Aloha";
s.substring(s.indexOf("A"), s.length);	//s.length (value)
										//s.indexOf() (method)
```
- there are no wrapper objects for the **null** and **undefined** values, which will cause a **TypeError** when attempt to access.
- **strings**, **numbers** and **boolean** values behave like objects when you try to read the value of a property from them. But if you attempt to set the value of a property, that attempt is silently ignored. 

```js
var s = "test";
s.len = 4;		//s.len undefined
var t = s.len;	//t = undefined
```
- all string methods that appear to return a modified string are, infact, returning a new string value, cause **string** is **immutable**.

```js
var s = "Aloha"
s.toUpperCase();	//return a new string, but dosen't change s
s					// => "Aloha"
```
- **Object** is mutable

```js
var o = {x: 1};  
o.x = 2;		//change the value of x
o.y = 3;		//set a new property y
```
- **Array** is also mutable

```js
var a = [1, 2, 3];
a[0] = 0;	//Change the value of the first element
a[3] = 4;	//Add new element into the array

``` 

### Compare
- `===`: 嚴格相等
- `==`: 相等

```js
var a = 3;
var b = "3";
a == b			// => true: only when the values are the same
a === b			// => false: cause the type is not the same
```

- distinct **Array** and **Object** are never equal, but equal when two reference points to the same thing.

```js
var a = [], b = [];
a == b			// => false
a === b			// => false

var a = {x: 1}, b = {x: 1};
a == b			// => false
a === b			// => false

var a = [];
var b = a;
a == b			// => true
a === b			// => true
```
- when wanting to compare two arrays by checking their values, we can write a function.

```js
function equalArray(a, b){
	if(a.length != b.length) 			//first check length
		return false;
	for(var i = 0; i < a.length; i++)		//second check member
		if(a[i] !== b[i])
			return false;
	return true;
}
```
