## Dynamic Programming(動態規劃)	[Back](./../Analysis.md)

- 當我們把分治的思想運用到優化問題上時, 我們稱之為**動態規劃** (Dynamic Programming)
- 當一個問題符合**最優子結構** (問題的最優解求解可以推給子問題的最優解, 且子問題最優解間互相獨立)時, 我們就可以通過動態規劃來解決問題
- 解決思路:
	- characterize the structure of the optimal solution. (**important**)
	- recursively define expressions.
	- compute the value of the solution in a bottom-up fashion. (避免重複計算)
	- construct the optimal solution using the computed information.

### 典型問題及算法

- **Assembly-line Scheduling Problem** [[**details**](./Assembly/Assembly.md)]
- **Matrix-chain Multiplication Problem** [[**details**](./Matrix/Matrix.md)]
- **Longest Common Sub-sequence Problem** [[**details**](./LCS/LCS.md)]
- **Max Sum Problem** [[**details**](./MaxSum/MaxSum.md)]
- **0-1 Knapsack Problem** [[**details**](./Knapsack/Knapsack.md)]
- **Single-source Shortest Path Problem**
	- **Bellman-Ford Algorithm** [[**details**](./Bellman/Bellman.md)]
- **All-Pairs Shortest Path Problem**
	- **DP Algorithm** [[**details**](./DP/DP.md)]
	- **Floyd-Warshall Algorithm** [[**details**](./Floyd/Floyd.md)]
