## DP Algorithmn for All-pairs Shortest Path Problem	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- All-pairs Shortest Path Problem在所有邊均是非負權值情況下, 若使用Dijkstra算法, 則時間複雜度則為<img src="./time.png">
- All-pairs Shortest Path Problem在有負權值的邊情況下, 若使用Bellma-Ford算法, 則時間複雜度則為<img src="./time1.png">
- 約束條件: 節點間最多能過多少條邊
- 時間複雜度: <img src="./on3lgn.png">
- <img src="./dmij.png">: 表示第i個節點到第j個節點在最多能過m條邊的情況下, 最短的路徑值.

### Recursive Expression
- <img src="./recursive_expression.png">

### Solution
- <img src="./solution.png">
