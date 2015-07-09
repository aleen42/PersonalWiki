## Model of Server [Back](./../Coding.md)

- 服務器分類:
	- 循環服務器: 同一時刻只能處理一個客戶端請求
	- 併發服務器: 同一時刻可處理多個客戶端請求
	- UDP/TCP服務器模型: 
		- UDP: 採用**循环服务器**模型
		- TCP: 採用**併發服務器**模型

### 循環服務器

- 每次循環執行一次客戶端請求
- 當請求未處理完的情況下, 將會阻塞其他客戶端的請求
- 

##### TCP

<img src="./loop_server_tcp.png">

##### UDP

<img src="./loop_server_udp.png">

### 併發服務器

##### UDP

###### Model 1: one datagram of requests

<img src="./parallel_server_udp.png">

- 用於**客戶請求需要較長處理時間**且**客戶發送時間大於服務器處理速度**的情況
- 避免因接收緩衝區滿而導致數據報丟失

###### Model 2: more than one datagram of requests



<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
