//: OnOffSwitch.java
// Why use finally?

class Switch 
{
	boolean state = false;
	boolean read() { return state; }
	void on() { state = true; }
	void off() { state = false; }
}

public class OnOffSwitch 
{
	static Switch sw = new Switch();
	public static void main(String[] args) 
	{
		try 
		{
			sw.on();
			// Code that can throw exceptions...
			//sw.off();	//must be down
		} 
		catch(NullPointerException e) 
		{
			System.out.println("NullPointerException");
			//sw.off();	//must be down
		} 
		catch(IllegalArgumentException e) 
		{
			System.out.println("IOException");
			//sw.off();	//must be down
		}
		finally
		{
			sw.off();
		}
	}
} ///:~