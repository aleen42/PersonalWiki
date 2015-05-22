
import java.util.*;

public class StackDemo {
	public static void main(String args[])
	{
		Stack s = new Stack();
  
    	s.push(new Integer(0));
    	s.push(new Student(202));
    	s.push(new Integer(1));						//push in
  
    	System.out.println( (Integer)s.peek());		//get but not pop
    	System.out.println((Integer)s.pop());		//pop out
	    Student a =(Student)s.pop();
	    a.prt();
   		System.out.println((Integer)s.pop());    
	}
}

class Student 
{
	int no;
	Student(int i) {no = i;}
	void prt(){System.out.println(no);}
}