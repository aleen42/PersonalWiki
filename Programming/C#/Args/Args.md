## Args [Back](./../../C%23/C%23%20Menu.md)

- 命令行參數: Main函數開始時接受的參數

```C#
using System;

class listArg0
{
	public static void Main(String[] args)
	{
		string strName;  
		strName = args[0]; 
		Console.WriteLine("This is the first argument: {0}!", strName);  
		Console.Read();
	}
}
```

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
