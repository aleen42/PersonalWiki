## Matrix-chain Multiplication Problem(矩陣鏈相乘)	[Back](./../DP.md)

### Overview
<img src="./overview.png">

- 求出乘次數最少的順序
- 主程序時間複雜度: <img src="./on3.png">
- 添加括號時間複雜度: <img src="./on2.png">
- 子問題個數(m數組的填寫): <img src="./sum.png">
- <img src="./mij.png">: 第i個矩陣到第j個矩陣次數的最少值 (用於記錄最優解的值)
- <img src="./sij.png">: 第i個矩陣到第j個矩陣相乘時, 應該先乘前<img src="./sij.png">個 (用於記錄最優解)
- <img src="./pi.png">: 第i個矩陣的兩個維數

### Optimal Substructure
- 當我們知道<img src="./mik.png">和<img src="./mkj.png">都是所乘次數最少的, 那麼<img src="./mij.png">的值一定是這兩個值相加後, 再加上<img src="./ppp.png">.

### Recursive Expression
<img src="./recursive_expression.png">

### Solution
- 最優解: 通過反向遍曆<img src="./sij.png">, 找到最優解.
- 最優解的值: <img src="./m1n.png">
