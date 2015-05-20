## Types, Values, and Variables [Back](./../JavaScript.md)

- JavaScript's types can be divided into **primitive types** and **object types**.
- JavaScript's types can also be categorized as **mutable** and **immutable** types.
	- mutable types: value can change
		- Objects
		- Arrays
		- ...
	- immutable types: value can not change
		- Numbers
		- booleans
		- null
		- undefined
		- strings
		- ...

```javascript
var x;
x = 0;
x	//=>0

//JavaScript supports several types of values
x = 1;	//integers
x = 0.1;	//real
x = "Aloha";	//String in quatation marks
x = 'Aloha';	//String in single quatations 
x = true;	//boolean
x = null;	//no value
x = undefined;	//like null
```

###Arithmetic
- a set of functions and constants are defined as properties of the **Math** object.

```javascript
Math.pow(2,53)	//=>2^53
Math.round(.6)	//=>1.0
...
```
- JavaScript does not raise errors in case of **overflow**, **underflow**, or **devision by zero**, there is a special **not-a-number** value: **NaN**.

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
