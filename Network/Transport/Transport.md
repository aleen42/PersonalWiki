## Transport Layer	[Back](./../Network.md)
- 傳輸層協議包括兩種:
	- TCP(Transmission Control Protocol): reliable, connection-oriented
	- UDP(User Datagram Protocol): more effort, connectionless

- 傳輸協議的選擇不僅要依靠其特性來選擇, 而且要根據工程的具體情況來分析.
	- 若是UDP的出錯率可容忍, 則儘量選擇UDP, 由於其編程複雜度較TCP低
- Out of band(OOB, 帶外數據)[[**details**](./OOB/OOB.md)]

### TCP
<img src="./tcp_header.gif">

### UDP
<img src="./udp_header.gif">
