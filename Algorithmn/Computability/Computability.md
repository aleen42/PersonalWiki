## Computability	[Back](./../AlgorithmnMenu.md)
- 探索一個問題的Computability主要從兩個方面討論
	- In Theory
		- 並不是所有的數學問題都是理論上可解決的.
		- 如果某问题理論上不能解決, 我們稱之為**Undecidable** (不可判定的)
	- In Practices
		- 在實際項目中, 倘若一個算法它的時間複雜度達到**指數**級別, 我們則之為**Incomputable** (不可計算的). (量子計算機或許是一個特例, 如果能實現指數級計算)

- 問題的劃分
	- NP: 有多項式級別的判定算法
	- P: 有多項式級別的求解算法
	- EXP: 有指數式級別的求解算法
	- NP-Complete(NPC): 有多項式級別轉化成NP問題的算法(如果能有效地解決該類問題, 則所有NP都能有效解決)
		- **3-Color Problem**
		- **TSP**
		- **Circuit-SAT**

<img src="./problem.png">

###Reduction

- Reduction is a general technique for showing that one problem is harder (easier) than another.
- Reduction of **NPC**

<img src="./NPC.png">
