## Search(查詢)	[Back](./../Analysis.md)
- 當一個問題它的解是分量, 且只需求出可行解, 但我們沒有有效的算法時, 往往只能窮舉.
- 查詢策略只是在窮舉的基礎上, 給出一些約束條件. 其分為:
	- **Back-Tracking Search**
		- DFS(Depth-first Search)
	- **Branch & Bound Search**
		- BFS(Breadth-first Search): 靠左生成
			- 通過**Queue**實現(**FIFO**)
		- D-Search: 靠右生成
			- 通過**Stack**實現(**LIFO**)
		- LC-Search: 根據權值智能生成

- **約束條件**
	- 顯式約束: 分量的取值約束
	- 隱式約束: 分量之間的約束

- **Alive node**: a generated node whose sons have not all been generated.
- **E-node**: the node whose son is generating currently.
- **Dead node**: a node that all his sons have been generated or there is no need to generate his sons.
- Search策略往往以**Tree** (樹)作為數據結構
	- Back-Tracking Search: 每次Alive-node生成一個孩子節點後遍曆
<img src="./tree_backtrack.png">
	- Brach & Bound Search: 每次Alive-node生成所有孩子節點後才遍曆
<img src="./tree_bound_branch.png">



### 典型問題及算法
- **Back-Tracking**
	- **N-Queen Problem** [[**details**](./NQueen/NQueen.md)]
- **Branch & Bound**
	- **15-Puzzle Problem** [[**details**](./15Puzzle/15Puzzle.md)]
