//: CrashJava.java
// One way to crash Java
import java.util.*;

public class VectorDemo {
	int Value;
	VectorDemo(int i){Value = i;}
	public static void main(String[] args) 
	{
		Vector v = new Vector();
		VectorDemo obj;
		for(int i = 0; i < 8; i++)
			v.addElement(new VectorDemo(i));
      
		for(int i = 0; i < 8; i++)
		{
			obj = (VectorDemo)v.elementAt(i);
			System.out.println(obj.Value);
		}
		v.addElement(new Integer(11));
		v.addElement(new Integer(12));
		v.addElement(new Integer(13));
		System.out.println(((Integer)v.elementAt(8)).toString());  //vector may store different type object refferrnce
                                                               //but you must cast object type to the currect object type
		v.removeElementAt(8);      //delete the refered element
		System.out.println(v.contains(new Integer(12)));  //true //judge wether the vector contains the refered object
		System.out.println(v.contains(new VectorDemo(0)));  //false  why?
     
		System.out.println(v.capacity());  //return left capacity of current vector
     
		System.out.println(v.size());   //return element number in current vector
	}
} ///:~