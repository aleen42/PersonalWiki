//: NeverCaught.java
// Ignoring RuntimeExceptions

public class NeverCaught 
{
	static void f() 
	{
		throw new RuntimeException("From f()");		//programe breaks down here
	}
	static void g() 
	{
		f();
	}
	public static void main(String[] args) 
	{
		g();
		System.out.println("exit");
	}
} ///:~