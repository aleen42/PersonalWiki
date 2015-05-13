using System;
using System.Collections;       //System.Collections.IDictionary    加泛型需要两个参数
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class ForeachApp
    {
        public static void Main()
        {
            // 把环境变量中所有的值取出来，放到变量environment中
            IDictionary environment = Environment.GetEnvironmentVariables();    //System.Collections.IDictionary 表示键值/对的非通用集合
                                                                                //IDictionary Environment.GetEnvironmentVariables() 从当前进程检索所有环境变量名及其值
            // 打印表头
            Console.WriteLine("环境变量名\t=\t环境变量值");

            // 遍历environment中所有键值
            foreach (string environmentKey in environment.Keys)     //IDictionary.Keys  获取包含对象IDictionary的键
            {
                // 打印出所有环境变量的名称和值
                Console.WriteLine("{0}\t=\t{1}", environmentKey, environment[environmentKey].ToString());   //.ToString() 返回当前对象的字符串
            }
        }
    }
}
