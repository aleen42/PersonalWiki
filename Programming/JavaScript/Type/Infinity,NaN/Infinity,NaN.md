## Infinity & NaN [Back](./../Type.md)


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
