//: ThrowOut.java
public class ThrowOut 
{
	public static void main(String[] args) throws Throwable 
	{
		try 
		{
			throw new Throwable();
			//The Throwable class is the superclass of all errors and exceptions in the Java language
		} 
		catch(Exception e) 
		{
			System.out.println("Caught in main()");
		}
	}
} ///:~