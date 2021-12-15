## Call/Return	[Back](./../Style.md)
- Call/Return適用於任何有函數調用的系統

> Mainprogram & subroutines

> Object-oriented

> Layered

### 1. Mainprogram & subroutines(主程序&子程序)
- 存在層次結構, 過程嵌套(可整合成模塊)
- 組件: 主程序, 子程序
- 連接件: 過程調用
- 缺點: 並不能反應顯示生活中的實體

### 2. Object-Oriented(面向對象)
- 封裝, 繼承, 多態, 交互, 複用和維護(適合反應現實生活)
- 組件: 對象
- 連接件: 消息傳送
- 缺點: 缺乏層次, 導致代碼的扁平化

### 3. Layered
- 分層的Object-Oriented
- 層與層之間耦合度較低, 只能見到相鄰的兩層(通常是向上提供服務, 被下層服務)
- 組件: 層
- 連接件: 層間調用
- 缺點: 層層調用將導致效率降低
- 應用:
	- 兩層C/S: **Workstation**(顯示層, 業務層) - **Server**(數據訪問層)
	- 三層C/S: **Client**(顯示層) - **Application Server**(應用服務器業務層, 處理客戶端訪問數據庫的操作以保證安全性) - **Server**(數據訪問層)
	- B/S: 三層C/S的一個特例, 即顯示層是一個Browser而不是客戶端 
