using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class ArrayApp
    {
        public static void Main()
        {
            // 声明一个2行3列的两维数组，用于存放矩阵A
            int[,] matrixA = new int[2, 3];

            // 声明一个3行4列的两维数组，用于存放矩阵B
            // 初始化矩阵B
            int[,] matrixB = new int[3, 4] { { 4, 2, 1, 7 }, { 3, 6, 1, 0 }, { 5, 3, 2, 4 } };

            // 声明一个2行4列的两维数组，用于存放矩阵A和矩阵B的乘积
            int[,] matrixC = new int[2, 4];

            // 初始化矩阵A
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    matrixA[i, j] = (i + 2) * (j + 2) + 1;
                }
            }

            // 计算矩阵A和矩阵B的乘积
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    // 初始化矩阵C
                    matrixC[i, j] = 0;

                    // 计算矩阵A和矩阵B的乘积，并把值存放在矩阵C中
                    for (int k = 0; k < 3; k++)
                    {
                        matrixC[i, j] += matrixA[i, k] * matrixB[k, j];
                    }
                }
            }
            
            // 打印矩阵A
            Console.WriteLine("\n********矩阵A********");
            outputMatrix(matrixA, 2, 3);

            // 打印矩阵B
            Console.WriteLine("\n********矩阵B********");
            outputMatrix(matrixB, 3, 4);

            // 打印矩阵C
            Console.WriteLine("\n********矩阵A X 矩阵B********");
            outputMatrix(matrixC, 2, 4);
        }

        // 功能： 输出矩阵
        // 参数： 
        //        matrixX       : 待打印的矩阵
        //        rowCount      : 矩阵的行数
        //        columnCount   : 矩阵的列数
        private static void outputMatrix(int[,] matrixX, int rowCount, int columnCount)
        {
            // 如果行列数错误，则不打印矩阵
            Console.WriteLine(matrixX.Length);
            if (matrixX.Length != rowCount * columnCount)       //.Length 表示该数组所有元素个数
            {
                Console.WriteLine("行列数错误!");
                return;
            }

            // 打印矩阵
            for (int i = 0; i < rowCount; i++)
            {
                // 逐一打印各行中所有元素
                for (int j = 0; j < columnCount; j++)
                {
                    Console.Write(matrixX[i, j] + "\t");
                }

                // 换行
                Console.WriteLine();
            }
        }
    }
}
