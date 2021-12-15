## Independent Components	[Back](./../Style.md)
- Independent Components適用於**組件互相獨立**的系統

> Communication Processes

> Event System

### 1. Communication Processes(通信進程)
- Messages passed among named participants, 即需指定源和目的
- 適用於OS, Distributed System
- 組件: 進程
- 連接件: 進程間消息
	- 單播
	- 組播
	- 多播

### 2. Event System(事件系統)
- 類似於推送系統, 實時動態更新且靈活變化
- 消息的傳遞由系統來完成, 而關注者並不需要關心消息的發送對象
- 組件: 
	- 關注者
	- 接受者(頻繁變化)
- 連接件: 基於事件的隱式調用
- 優點: reconfigurable on fly(動態事件發送)
- 缺點: 構件放棄了對系統計算的控制, 從而存在計算正確性問題
