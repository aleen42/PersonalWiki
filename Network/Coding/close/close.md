## Close [Back](./../Coding.md)

- to close socket
- **close** method is just to decrease the number of references of **sockfd**, and clear sockfd when the number becomes **0**. That's because TCP will continue to  use this sockfd to complete transmissions of data

### 1. close()
- 關閉後, 其他進程扔可以使用該socket描述符

##### method

```c
int close(int sockfd)
```

##### parameters
- sockfd: socket描述符

##### return value
- 0: success
- -1: failure
- errno: wrong code

### 2. shutdown()
- 關閉後, 其他進程不能再用已關閉的通道
- 提供更高級的關閉操作, 可以只關閉一個通道, 而另一個通道仍可以操作


##### method

```c
int shutdown(int sockfd, int howto)
```

##### parameters
- sockfd: socket描述符
- howto:指定關閉的方式
	- 0: 關閉**讀通道**, 丟棄尚未讀取的數據, 對後來收到的數據確認後丟棄.
	- 1: 關閉**寫通道**, 繼續發送緩衝區沒發送完的數據, 然後發送**FIN**字段關閉通道.
	- 2: 關閉**讀寫通道**, 任何進程再也不能操作該socket

##### return value
- 0: success
- -1: failure
