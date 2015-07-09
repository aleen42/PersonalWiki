## Out of band(帶外數據) [Back](./../Coding.md)

- 帶外數據: 傳輸層用於發送**緊急數據**
- 一般使用**單獨通道**發送帶外數據
- TCP協議沒有真正的帶外數據, 而是用**URG標誌**的首部表示帶外數據
	- URG為帶外數據標誌位
	- 緊急指針 = 帶外數據位置 + 1 (在不同實現中會有所不同, 參考**RFC 793** 和 ** RFC 1122**)
- TCP只支持**1字節**的帶外數據
- TCP協議中帶外數據包含在正常數據中發送
- 由於接收緩衝區大小和TCP字段大小限制, 帶外數據到達接收方之前, 接收方可能已經收到多個帶URG標誌的數據段
- 接受URG數據段時, 會確定是否帶有帶外數據
- socket選項SO_OOBINLNIE
	- 設置: 帶外數據保存在正常的數據流中
	- 未設置: 帶外數據拷貝到**帶外數據緩衝區**中
		- 只能調用設置了```MSG_OOB```標誌的```recv()```, ```recvfrom```或```recvmsg()```
		
		```c
		int sockfd;
		char oobdata;
		//...
		recv(sockfd, &oobdata, 1, MSG_OOB);
		```

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


<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
