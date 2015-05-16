## Thread [Back](./../Java.md)
- Thread(線程)指一個程序中的執行片段,且擁有併發執行的特性.
- Thread實現要extends Thread(一般還需要implements Runnable)

###同步&互斥
- 同步: 指事件處理存在一定的協作順序，而這個順序的改變將會導致結果的差錯. (Semaphore)
- 互斥: 指多個進程將要讀取同一區域(關鍵區)的數據時,將只能允許一個進程進入. (Mutex)

###States of a Thread

<!-- lang:Java -->
	class MyThread extends Thread implements Runnable
	{
		//Attributes
		MyThread()
		{
			//Constructor
		}
	
		@SuppressWarnings("deprecation")
		public void run()
		{
			//What you want this thread to do
			Thread.sleep(100);	//Blocked State
			wait();			//Blocked State (need other threads to call notify() or notifyall())
		}
	}	

```Java
Thread t = new MyThread()	//Initialize
t.start();	//Run State
			//Ready State: Waiting CPU to call it
```



=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
