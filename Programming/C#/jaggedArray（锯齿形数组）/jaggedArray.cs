using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    public class JaggedArray
    {
        public static void Main()
        {
            // 声明一个锯齿型数组，该数组有两个元素
            int[][] myArray = new int[2][];         //开辟两行

            // 其中第一个元素是一个含有五个元素的数组
            // 初始化myArray[0]
            myArray[0] = new int[5] { 1, 3, 5, 7, 9 };


            // 其中第二个元素是一个含有4个元素的数组
            // 初始化myArray[1]
            myArray[1] = new int[4] { 0, 2, 4, 6 };     //总共开辟9个int
            Console.WriteLine(myArray.Length);      //输出2
            Console.WriteLine(myArray[0].Length);   //输出5
            Console.WriteLine(myArray[1].Length);   //输出4
            // 逐一打印出数组的数组中所有的元素
            for (int i = 0; i < myArray.Length; i++)
            {
                Console.Write("第({0})个数组: ", i);

                // 打印一维数组中的元素
                for (int j = 0; j < myArray[i].Length; j++)
                {
                    Console.Write("{0} ", myArray[i][j]);
                }

                Console.WriteLine();
            }
        }
    }

}
