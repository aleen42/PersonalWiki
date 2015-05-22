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

```js
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

```js
Math.pow(2,53)	//=>2^53
Math.round(.6)	//=>1.0
...
```

###Infinity & NaN
- JavaScript does not raise errors in case of **overflow**, **underflow**, or **devision by zero**, there is a special **not-a-number** value: **NaN**.
- JavaScript predefines global variables **Infinity** to distinguished from **NaN**.
- Infinity is **read/write** in **ECMAScript3**, while **read/only** in **ECMAScript5**.

```js
//Positive Infinity
Infinity	
Number.POSITIVE_INFINITY	
1/0
Number.MAX_VALUE + 1

//Negative Infinity
-Infinity
Number.NEGATIVE_INFINITY
-1/0		
-Number.MAX_VALUE - 1		

//NaN
NaN
Number.NaN
0/0

isNaN(x);	//return true when x is NaN
isFinite(x);	//return true when x is other than NaN, Positive or Negative Infinity
```

###Precision
- JavaScrpit numbers also have the same problem of c++, and can approximate 0.1 very closely. But the fact that this number cannot be represented exactly can lead to problems.

```js
var x = .3 - .2;
var y = .2 - .1;
x == y;		//false: the two values are not the same!
x == 0.1;	//false
y == 0.1;	//true
```

###Date and Times
```js
var later = new Date(2010, 0, 1, 17, 10, 30);	//5:10:30pm, local time
var then = new Date(2010, 0, 1);	//Jan 1st, 2010

var now = new Date();	//current time

//API
later.toString();	// => "Fri Jan 01 2010 17:10:30 GMT-0800 (PST)"
later.toUTCString();	// => "Sat, 02 Jan 2010 01:10:30 GMT"
later.toLocaleDateString();	// => "01/01/2010"
later.toLocaleTimeString();	// => "05:10:30 PM"
later.toISOString();		// => "2010-01-02T01:10:30.000Z"; ES5
```

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>