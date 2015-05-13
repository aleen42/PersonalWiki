using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    
    class WhileApp 
    {
        // 这是一个支持单用户的服务器模型
        public static void Main()  
        {
            // 打印软件的欢迎信息
            Console.WriteLine("欢迎使用whileApp V0.1");
            // 提示正确用法
            Console.WriteLine("whileApp V0.1 支持的命令集有：");
            Console.WriteLine("\tget:\t获取文件");
            Console.WriteLine("\tput:\t传送文件");
            Console.WriteLine("\texit:\t退出程序");
            // 打印命令输入符
            Console.Write(">");

            // command用于存储用户的命令
            string command;

            // 读入用户的命令
            // 命令为exit表示退出程序
            while((command = Console.ReadLine()) != "exit")
            {
                switch(command)
                {
                    // 处理get命令
                    case "get":
                        doGet();
                        break;

                    // 处理put命令
                    case "put":
                        doPut();
                        break;

                    // 处理缺省命令
                    default:
                        doDefault();
                        break;
                }

                // 打印命令输入符
                Console.Write(">");
            }
        }

        // 处理get命令
        private static int doGet()
        {
            // 待加入真正的get处理动作
            Console.WriteLine("获取文件...ok");

            return 0;
        }

        // 处理put命令
        private static int doPut()
        {
            // 待加入真正的put处理动作
            Console.WriteLine("传送文件...ok");

            return 0;
        }

        // 处理缺省命令
        private static int doDefault()
        {
            // 打印出错信息
            Console.WriteLine("命令错误");

            // 提示正确用法
            Console.WriteLine("whileApp V0.1 支持的命令集有：");
            Console.WriteLine("\tget:\t获取文件");
            Console.WriteLine("\tput:\t传送文件");
            Console.WriteLine("\texit:\t退出程序");
            return 0;
        }

    }
}
