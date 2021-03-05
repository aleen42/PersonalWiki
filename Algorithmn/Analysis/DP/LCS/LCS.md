## Longest Common Sub-sequence Problem(最長公共子序列)	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- 求出最短裝配時間
- 主程序的時間複雜度: <img src="./omn.png">
- 追溯最優解的時間複雜度: <img src="./omn1.png">
- <img src="./cij.png">: S1序列取前i個, S2序列取前j個時的最長公共子序列長度值. (用於求最優解的值)
- <img src="./bij.png">: S1序列取前i個, S2序列取前j個時, <img src="./cij.png">是如何求得. (用於求最優解)

### Optimal Substructure
- 當我們知道若求<img src="./cij.png">的時候, 若S1序列的最後一個字符與S2的最後一個字符相同, 則該字符一定在公共子序列中, 因此<img src="./cij.png">的值必定是<img src="./cij1.png">的值加一; 否則, <img src="./cij.png">的值將是<img src="./cij2.png">和<img src="./cij3.png">中較大的一個.

### Recursive Expression
<img src="./recursive_expression.png">
	

### Solution
- 最優解: 通過反向遍曆<img src="./bij.png">, 找到最優解.
- 最優解的值: <img src="./cmn.png">
