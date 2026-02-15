## Listen [Back](./../Coding.md)

- listen to the port, waiting clients to connect
- based on TCP, there are two queues: one is for **already connected** clients, and the other is for **not connected yet**.

<img src="./two_queue.png">


##### method

```c
int listen(int sockfd, int qlen)
```

##### parameters
- sockfd: socket描述符
- qlen: 偵聽socket能處理的最大併發鏈接數

##### return value
- 0: success
- -1: failure
- errno: wrong code
