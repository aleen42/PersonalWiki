## 0-1 Knapsack Problem(0-1背包)	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- 每個item只能取值0或1, 求如何存放背包才能獲取利益最大值
- <img src="./cij.png">: 用容量j去裝i個items, 最多能裝多少個
- <img src="./wi.png">: 第i個item的重量
- <img src="./vi.png">: 第i個item的價值


### Optimal Substructure
- 當我們求<img src="./cij.png">時, 若不取第i個item, 則<img src="./cij.png">必定等於<img src="">;而若取, 則<img src="./cij.png">的值為<img src="./cij1.png">加上該item的價值<img src="./vi.png">.

### Recursive Expression
<img src="./recursive_expression.png">
	

### Solution
- 最優解的值: <img src="./cnw.png">
