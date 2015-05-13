using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class forapp
    {
        static void Main()
        {
            //打印表头
            Console.WriteLine("九九乘法表");

            //打印九九表
            for (int i = 1; i <= 9; i++)
            {
                //计算并格式化输出九九表的内容
                for (int j = 1; j <= i; j++)
                {
                    Console.Write("{0}*{1}={2}\t", i, j, i * j);
                }

                //换行
                Console.WriteLine();
            }
            
        }
    }
}
