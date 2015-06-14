## Close [Back](./../Coding.md)

- to close socket
- **close** method is just to decrease the number of references of **sockfd**, and clear sockfd when the number becomes **0**. That's because TCP will continue to  use this sockfd to complete transmissions of data

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

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
