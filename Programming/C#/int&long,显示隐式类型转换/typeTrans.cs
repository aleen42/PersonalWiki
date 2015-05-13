using System;
class typeTrans
{
	public static void Main() 
	{
		int intValue1, intValue2;           //int类型
        long longValue1, longValue2;        //long类型
        intValue1 = 123;
        longValue1 = 456;
        longValue2 = intValue1;             //隐式类型转换：int to long
        intValue2 = (int)longValue1;        //显示类型转换：long to int
        bool test = (intValue1 == longValue2);
        Console.WriteLine(test);
        Console.WriteLine("(long){0} = {1}", intValue1, longValue2);
        Console.WriteLine("(int){0} = {1}", longValue1, intValue2);

        long longValue3 = 2147483657L;      //c sharp是强制类型语言
        int intValue3 = (int)longValue3;      //发生溢出  
        Console.WriteLine("(int){0} = {1}", longValue3, intValue3);
        Console.Read();
	}
}
