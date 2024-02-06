## IPC(進程間通信) [Back](./../pt.md)
- 由於Linux下各個進程在獨立地址空間運行, 因此無法通過**全局變量**和**參數傳遞**實現信息共享
- 主要方式
	- [**pipe & fifo**](./pipe_fifo/pipe_fifo.md)
	- [**message queue**](./queue/queue.md)
	- [**shared memory & memory mapped file**](./mmap/mmap.md)
	- [**semaphore**](./semaphore/semaphore.md)
	- [**UNIX socket**](./socket/socket.md)

