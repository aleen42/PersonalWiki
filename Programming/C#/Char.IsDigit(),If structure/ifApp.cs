using System;

class IfApp
{
    public static int Main(string[] args)
        {
            //如果命令行参数小于一个，则显示程序正确用法，退出程序
            if (args.Length < 1)
            {
                Console.WriteLine("Usage: ifApp char");
                Console.Read();
                return 1;
            }

            //获得第一个命令行参数第一个字母
            //把该字母赋给变量chLetter
            char chLetter = args[0][0];

            //如果字母大于等于字符'A'
            if (chLetter >= 'A')
            {
                //同时，字母小于字符'Z'
                //则该字母为大写字母
                if (chLetter <= 'Z')
                {
                    Console.WriteLine("{0} 是个大写字母", chLetter);
                    Console.Read();
                    return 0;
                }
            }

            //如果字母界与字符'a'和'z'之间
            //则该字母为小写字母
            if (chLetter >= 'a' && chLetter <= 'z')
            {
                Console.WriteLine("{0} 是个小写字母", chLetter);
                Console.Read();
                return 0;
            }

            //如果字母为数字
            if (Char.IsDigit(chLetter))
            {
                Console.WriteLine("{0} 是个数字", chLetter);
                Console.Read();
                return 0;
            }

            //缺省地(以上条件都不符合)，则该字母为特殊字符
            Console.WriteLine("{0} 是个特殊字符", chLetter);
            Console.Read();
            return 1;
        }
}
