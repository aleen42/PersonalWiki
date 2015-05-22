package Data_Structure.Iterator;
import java.util.*;
public class UseIterator 
{
	public static void  main(String args[] )
	{
		ArrayList mice = new ArrayList();
		for(int i=0;i<7;i++)
			mice.add(new Integer(i));
		Iterator e = mice.iterator();
		while(e.hasNext())
			System.out.println(e.next());
	}
}