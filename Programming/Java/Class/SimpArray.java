/*	Question: Write a class with name SimpleArray whose instance swill be shared across two or more threads.
 *	Date: 2015.05.26
 */
class SimpArray
{
	private ArrayList<Object> container;
	public SimpArray()
	{
		container = new ArrayList<Object>();
	}
	
	public void add(int i)
	{
		container.add(new Integer(i));
	}
}

class My_Threawd extends Thread
{
	private static SimpArray<Object> array = new SimpArray<Object>();
	
	public void run()
	{
		doing_with_array();
	}
	
	public synchronized void doing_with_array()		//do with sharing area
	{
		//...
	}
}