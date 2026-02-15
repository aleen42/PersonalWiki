## File [Back](./../../CSharp/CSharpMenu.md)

- 文件操作: FileStream, StreamWriter, StreamReader, BinaryReader, FileInfo

```C#
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;    //FileStream,

namespace ConsoleApplication1
{
    public class FileApp
    {
        public static void Main()
        {
            // 在当前目录创建一个文件myfile.txt，对该文件具有读写权限
            FileStream fsMyfile = new FileStream("F:\\School\\Programing\\C# Programing\\笔记程序\\实例16\\myfile.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite);   
            //FileStream name=new FileStream(path,FileMode,FileAccess)
            //FileMode.Append:若存在，打开文件并查找到文件尾；若无则新建
            //FileMode.Create:创建新文件，若存在则覆盖之
            //FileMode.CreateNew:创建新文件，若存在则出现异常
            //FileMode.Open:打开文件，若不存在则出现异常
            //FileMode.OpenOrCreate:打开文件，若不存在则新建文件
            
            //FileAccess.Read:只读
            //FileAccess.ReadWrite:读写

            // 创建一个数据流写入器，和打开的文件关联
            StreamWriter swMyfile = new StreamWriter(fsMyfile);
            //StreamWriter name=new StreamWriter(file_name)

            // 以文本方式写一个文件
            swMyfile.WriteLine("Hello, World");
            swMyfile.WriteLine("abcdefghijklmnopqrstuvwxyz");
            swMyfile.WriteLine("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            swMyfile.WriteLine("0123456789");

            // 冲刷数据(把数据真正写到文件中去)
            // 注释该句试试看，程序将报错
            swMyfile.Flush();
            //StreamWriter.Flush();  将缓冲流数据写到文本去

            // 打印提示信息
            Console.WriteLine("****************以文本方式读文件*********************");
            // 以文本方式读文件
            // 创建一个数据流读入器，和打开的文件关联
            StreamReader srMyfile = new StreamReader(fsMyfile);
            //StreamReader name= new StreamReader(file_name)

            // 把文件指针重新定位到文件的开始
            srMyfile.BaseStream.Seek(0, SeekOrigin.Begin);  //0代表开头
            //StreamReader.BaseStream.Seek(offset,origin);
            //SeekOrigin.Begin:表示流的开头

            // 打印文件文本内容
            string s1;
            while ((s1 = srMyfile.ReadLine()) != null)       
            {
                Console.WriteLine(s1);
            }
            Console.WriteLine();
            // 以文本方式读文件结束
/*
            // 打印提示信息
            Console.WriteLine("****************以二进制方式读文件*********************");
            // 以二进制方式读文件
            // 创建一个二进制数据流读入器，和打开的文件关联
            BinaryReader brMyfile = new BinaryReader(fsMyfile);
            //BinaryReader name = new BinaryReader(file_name);

            // 把文件指针重新定位到文件的开始
            brMyfile.BaseStream.Seek(0, SeekOrigin.Begin);

            // 打印文件文本内容
            Byte b1;
            while (brMyfile.PeekChar() > -1)
            {
                b1 = brMyfile.ReadByte();
                // 13为"\n"，表示回车；10为"\r"，表示换行
                if (b1 != 13 && b1 != 10)
                {
                    Console.Write("{0}", b1.ToString());
                    Console.Write(".");
                }
                else
                {
                    Console.WriteLine();
                }
            }
            Console.WriteLine("\n");
            // 以二进制方式读文件结束
*/
            // 关闭以上new的各个对象
            //brMyfile.Close();
            srMyfile.Close();
            fsMyfile.Close();

            // 读取文件属性
            // 打印提示信息
            Console.WriteLine("****************读取文件属性*********************");

            FileInfo fiMyfile = new FileInfo("F:\\School\\Programing\\C# Programing\\笔记程序\\实例16\\myfile.txt");
            //FileInfo name=new FileInfo("path");
            Console.WriteLine("文件名          : {0}", fiMyfile.Name);
            Console.WriteLine("文件名(含路径)  : {0}", fiMyfile.FullName);
            Console.WriteLine("文件大小(bytes) : {0}", fiMyfile.Length);
            Console.WriteLine("文件创建时间    : {0}", fiMyfile.CreationTime);
        }
    } 
}
```

