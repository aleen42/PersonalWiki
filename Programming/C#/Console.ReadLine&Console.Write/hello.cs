using System;  

class easyInput  
{
	public static void Main()
	{
		string strName; 
		Console.Write("please input your name:");  		//输出语句
		strName = Console.ReadLine();					//输入语句
		Console.WriteLine("hello, {0}!", strName); 		//{}代表参数号
														//WriteLine 与 Write的区别在于 WriteLine后跟行终止符
		Console.Read();
	}
}


