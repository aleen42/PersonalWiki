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