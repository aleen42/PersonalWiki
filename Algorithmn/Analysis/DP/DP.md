## Dynamic Programming(動態規劃)	[Back](./../Analysis.md)

- 當我們把分治的思想運用到優化問題上時, 我們稱之為**動態規劃** (Dynamic Programming)
- 當一個問題符合最優子結構(問題的求解可以推給子問題, 且子問題間互相獨立)時, 我們就可以通過遞歸來解決問題
- 解決思路:
	- characterize the structure of the optimal solution. (**important**)
	- recursively define expressions.
	- compute the value of the solution in a bottom-up fashion. (避免重複計算)
	- construct the optimal solution using the computed information.

### 典型問題及算法

- **Assembly-line Scheduling**
- **Matrix-chain Multiplication**
- **Longest Common Subsequence**
- **Max Sum**

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
