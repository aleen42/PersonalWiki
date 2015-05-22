//: AlwaysFinally.java
// Finally is always executed


class Ex extends Exception 
{
	public Ex() {System.out.println("Ex constructor");}
}

public class AlwaysFinally 
{
	public static void main(String[] args) 
	{
		System.out.println("Entering first try block");
		try 
		{
			System.out.println("Entering second try block");
			try 
			{
				throw new Ex();
			} 
			finally 
			{
			System.out.println("finally in 2nd try block");
			}
		} 
		catch(Ex e) 
		{
			System.out.println("Caught Ex in first try block");
		} 
		finally 
		{
			System.out.println("finally in 1st try block");
		}
	}
} ///:~