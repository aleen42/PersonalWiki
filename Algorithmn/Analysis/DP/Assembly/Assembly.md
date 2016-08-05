## Assembly-line Scheduling Problem(裝配線調度)	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- 求出最短裝配時間
- <img src="./aij.png">: 第i條線, 第j個站所花時間
- <img src="./fij.png">: 第i條線, 到第j個站的最短時間
- <img src="./tij.png">: 從第i条线到另一條線的j+1站所花的時間
- <img src="./sij.png">: 第i條線, 第j個站它的前一個站應該是第几條裝配線

### Optimal Substructure
- 當我們知道<img src="./f1.png">和<img src="./f2.png">是最優的時候, 那麼<img src="./f1i.png">一定是在<img src="./first.png">和<img src="./second.png">之間取最小的值.

### Recursive Expression
<img src="./recursive_expression.png">

### Solution
- 最優解: 通過反向遍曆<img src="./sij_array.png">, 找到最優解.
- 最優解的值: <img src="./optimal_value.png">
