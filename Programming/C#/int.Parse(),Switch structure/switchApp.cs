using System;
using System.IO;

class SwitchApp 
{
   public static void Main()  
   {
       //显示提示
      Console.WriteLine("三种选择型号: 1=(小杯, ￥3.0) 2=(中杯, ￥4.0) 3=(大杯, ￥5.0)"); 
      Console.Write("您的选择是: "); 

       //读入用户选择
       //把用户的选择赋值给变量n
      string s = Console.ReadLine(); 
      int n = int.Parse(s);             //string to int
       
       //根据用户的输入提示付费信息
      switch( n ) 
      {
         case 1:
            Console.WriteLine("小杯，请付费￥3.0。");
            break;
         case 2:
            Console.WriteLine("中杯，请付费￥4.0。");
            break;
         case 3:
            Console.WriteLine("大杯，请付费￥5.0。");
            break;
         //缺省为中杯
          default:
              Console.WriteLine("中杯，请付费￥4.0。");
              break;
      }

       //显示结束使用提示
      Console.WriteLine("谢谢使用，欢迎再次光临！");
      Console.Read();
   }
}

