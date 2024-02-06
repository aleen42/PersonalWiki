## Out of band(帶外數據) [Back](./../Transport.md)

- 帶外數據: 傳輸層用於發送**緊急數據**
- 一般使用**單獨通道**發送帶外數據
- TCP協議沒有真正的帶外數據, 而是用**URG標誌**的首部表示帶外數據
	- URG為帶外數據標誌位
	- 緊急指針 = 帶外數據位置 + 1 (在不同實現中會有所不同, 參考**RFC 793** 和 **RFC 1122**)
- TCP只支持**1字節**的帶外數據
- TCP協議中帶外數據包含在正常數據中發送

### 1. Send

<img src="./OOB.png">

- 發送過程:
	- 1. 將單字節帶外數據拷貝到發送緩衝區
	- 2. 設置URG標誌位, 緊急指針指向帶外數據的下一個位置
- 一旦寫帶外數據, TCP協議總是立刻發送該數字段
- 特殊情況:
	- TCP數據段大小不夠, 導致當前數據段無法包含帶外數據
		- 發送不包含帶外數據的URG標誌數據段.
	- 對方接送緩衝區已滿
		- 發送空的URG標誌數據段(數據長度為0)

##### method
```c
send(sockfd, "A", 1, MSG_OOB);		//'A' is the urgent data
send(sockfd, "ABC", 3, MSG_OOB);	//'C' is the urgent data
```

### 2. Receive
- 由於接收緩衝區大小和TCP字段大小限制, 帶外數據到達接收方之前, 接收方可能已經收到多個帶URG標誌的數據段
- 接受URG數據段時, 會確定是否帶有帶外數據
- socket選項SO_OOBINLNIE
	- 設置: 帶外數據保存在正常的數據流中
		- 普通的```read()```可以讀出, 並且不能設置```MSG_OOB```標誌, 否則返回錯誤
		- 讀之前應判斷下一字節是否含有帶外數據
		- 新到來的帶外數據不會覆蓋未處理的帶外數據, 但未處理的帶外數據將變成普通數據
	- 未設置: 帶外數據拷貝到**帶外數據緩衝區**中
		- 只能調用設置了```MSG_OOB```標誌的```recv()```, ```recvfrom```或```recvmsg()```
		- 新到來的帶外數據將會覆蓋未處理的帶外數據
		
		```c
		int sockfd;
		char oobdata;
		//...
		recv(sockfd, &oobdata, 1, MSG_OOB);
		```

- 接受緊急數據段時, 通知應用程序的方法:
	- 若設置了socket所有者(```fcntl()```), 則發送信號SIGURG給所有者
	- 若進程調用select等到socket描述符的異常情況, 則返回且對應的socket設置為**異常就緒**
		- 無論SO_OOBINLINE是否設置: 若進程還沒讀到帶外數據, 異常就緒條件總是滿足
- 接艘帶外數據可能出現的錯誤:
	- 設置了MSG_OOB標誌的```recv()```讀取帶外數據時, 對方沒有發送帶外數據. errno = EINVAL
	- 如果進程收到帶外數據通知, 但帶外數據沒有真正到達. errno = EWOULDBLOCK
	- 進程試圖多次讀取同一個帶外數據. errno = EINVAL
- **帶外數據標誌**用於標誌正常數據流中帶外數據的位置
	- 可同步正常數據和帶外數據
	- **存儲**和**修正**: <img src="./example.png" width="50%">
		- socket中有一字段記錄從接受緩衝區開始到帶外數據位置的**偏移量**
		- 收到帶外數據通知後, 偏移量有效
		- 正常数据讀取後將修改該偏移量
	- 當帶外數據標誌有效時, 正常數據讀取將在帶外數據標誌前停止
		- 如oob mask = 2, read(fd, buf, 5), 則返回值為2
		- 可通過```ioctl()```檢測讀指針是否到達帶外數據位置

		```c
		int sock_at_mark(int fd)	//return 1 for arrival, 0 for non-arrival, -1 for failure
		{
			int flag;
			if(ioctl(fd, SIOCATMARK, &flag) < 0)
				return -1;
			return flag != 0? 1: 0;
		}
		```
		- 無論SO_OOBINLINE是否設置, ```sock_at_mark()```總能檢測到讀指針是否到達帶外數據
		- 若SO_OOBINLINE設置: ```sock_at_mark()```返回1時, ```read()```讀取的數據將包含帶外數據
		- 若SO_OOBINLINE未設置: ```sock_at_mark()```返回1時, ```read()```讀取的數據將跳過帶外數據




