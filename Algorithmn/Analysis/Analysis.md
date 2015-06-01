## How to analyse an algorithmn	[Back](./../Algorithmn%20Menu.md)

- Sometimes, the **perfomance** of an algorithmn matters so much, when the size of a problem **n** is so big.

<img src="./overhead.png">

- But it's not always true for high perfomance, while an algorithmn depends on what is more important.
	- modularity(模塊性)
	- correctness(正確性)
	- maintainabillity(可維護性)
	- functionality(功能性)
	- robustness(健壯性)
	- user-friendliness(用戶友好性)
	- programmer time(編程效率)
	- simplicity(簡潔度)
	- extensibility(可擴展性)
	- reliability(可靠度)

- **Three** kinds of analysis
	- Worst-case
	- Average-case
	- Best-case(虛假的)

- **Three** notations of **time**
	- ***θ***: <img src="http://www.mathtran.org/cgi-bin/mathtran?D=2;tex=%5Ceqalign%7B%0D%0AT%28n%29%20%3D%20%5Ctheta%28g%28n%29%29%0D%0A%5CLongleftrightarrow%20c_1g%28n%29%20%5Cle%20T%28n%29%20%5Cle%20c_2g%28n%29%0D%0A%7D">(表達式中最高次項)

	<img src="http://www.mathtran.org/cgi-bin/mathtran?D=2;tex=%5Ceqalign%7B%0A%20%20T(n)%20%26%3D%203n%5E3%20%2B%2090n%5E2%20-%205n%20%2B%206046%20%5Ccr%0A%26%3D%203n%5E3%20%2B%2090n%5E2%20-%205n%20%2B%20%5Ctheta(1)%5Ccr%0A%26%3D%203n%5E3%20%2B%2090n%5E2%20-%20%5Ctheta(n)%5Ccr%0A%26%3D%203n%5E3%20%2B%20%20%5Ctheta(n%5E2)%5Ccr%0A%26%3D%20%5Ctheta(n%5E3)%5Ccr%0A%7D">
	
	


=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
