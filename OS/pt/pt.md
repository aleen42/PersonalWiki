## Thread & Process	[Back](./../OS.md)
###Process
- **Process**: 指正在運行的一個程序
- Linux進程結構:
	- 數據段(Data)
	- 代碼段(Programe)
	- 堆棧段(Stack)
		- 返回地址
		- 局部變量
- Linux進程分類:
	- 核心進程(**swapd**): 內核態下運行, 系統活動期間不會終止
	- [守護進程](./daemon/daemon.md): 運行在後臺的進程
	- 用戶進程: 用戶創建的進程(init進程不能被終止)

- Linux進程樹: 所有進程構建成一棵樹的結構, 稱為**進程樹**. 一個進程只能有一個**父進程**, 可以有多個**子進程**. 進程樹的根節點是**init進程**(```pstree```命令可查看)
- [**Create Processes**](./create/create.md)
- [**Signal**](./Signal/Signal.md)
- [**Kill processes**](./kill/kill.md)
- [**Interprocesses Communication(IPC)**](./IPC/IPC.md)

###Thread
- **Thread**: 指程序中的片段, 這些片段能夠並行執行
