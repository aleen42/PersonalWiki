import java.util.*;
class RandomDemo 
{
    public static void main(String[] args) 
{
        Random r = new Random();
        System.out.println( r.nextInt() );  //取得下一个随机整型数
        System.out.println( r.nextInt() );
        System.out.println( r.nextInt(10) );
        System.out.println( r.nextInt(10) );
        System.out.println( r.nextBoolean() );
        System.out.println( r.nextBoolean() );
        System.out.println( r.nextBoolean() );
        // r.nextInt(-10);                      
		// IllegalArgumentException
    } 
}
