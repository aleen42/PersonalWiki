## Max Sum Problem(最大和)	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- 求出某一段最大和
- <img src="./bj.png">: 以第j個結尾的最大和的值.

### Optimal Substructure
- 當我們求<img src="./bj.png">時, 若<img src="./dataj.png">的值為非正, 則<img src="./bj.png">肯定沒意義; 若<img src="./dataj.png">的值為正, 且<img src="./bj1.png">為非正, 則<img src="./bj.png">肯定為<img src="./dataj.png">; 而若<img src="./dataj.png">的值為正, 且<img src="./bj1.png">也為正, 則<img src="./bj.png">肯定為<img src="./bj1.png">加上<img src="./dataj.png">.

### Recursive Expression
<img src="./recursive_expression.png">
	

### Solution
- 最優解: 通過求解時指針指向i和j來找到最優解.
- 最優解的值: <img src="./bn.png">
