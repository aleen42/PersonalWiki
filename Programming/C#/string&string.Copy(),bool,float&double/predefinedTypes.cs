using System;

class predefinedTypes
{
	public static void Main() 
	{
		string str = "this is a string.";	//string类型
        Console.WriteLine(str);
        //string.copy()拷贝出来的字符串基类与原来的不一样，但表面值是一样的
        string strCopy = string.Copy(str);      //string拷贝函数
        Console.WriteLine(strCopy);
        bool testbool = (str == strCopy);       //bool类型
        Console.WriteLine(testbool);
        testbool = ((object)str == (object)strCopy); 
        Console.WriteLine(testbool);  
            
        float testfloat = 2323.03F;            //float类型
        Console.WriteLine(testfloat); 
        double testdouble = 2323.03;            //double类型
        Console.WriteLine(testdouble);
        //float和double即使字义一样，但是值并不一样
        testbool = (testfloat == testdouble);  
        Console.WriteLine(testbool); 
        Console.Read();
	}
}
