## ETag [Back](./qa.md)

- **ETag**(Entity Tag): a part of *HTTP*.
	- HTTP協議提供的一種**Web緩存**驗證機制, 允許客戶端進行緩存協商
		- 當資源內容沒有發生改變時, Web服務器不需要發送一個完整的響應到客戶端
		- 可用於樂觀併發控制, 防止資源同步更新
- ETag比較只對同一個URL有意義.
- ETag支持**強校驗**和**弱校驗**：
	- 強校驗: 要求兩個資源內容的每個字節完全相同. ```"123456789"```
	- 弱校驗: 只要求兩個資源語義上相同(如服務器動態生成的內容) ```W/"123456789"```
- ETag可用於檢測: 因為ETag由瀏覽器保存, 切訪問統一資源時返回. 追蹤服務器可重複設定任何從瀏覽器返回的ETag, 以保持ETag不變, 相當於Cookie. [**Help**](http://www.arctic.org/~dean/tracking-without-cookies.html)
