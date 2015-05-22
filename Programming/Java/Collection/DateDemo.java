//main.java
import java.util.*;
class DateDemo 
{
    public static void main(String[] args) 
{
//
        Date d = new Date();
		 // Sun Jan 10 15:25:03 PST 1999
        System.out.println( d );       
        Date copy = (Date)d.clone();
		 // Sun Jan 10 15:25:03 PST 1999
        System.out.println( copy );    
        // Changing the d does not affect copy.
        d.setTime(123);
		 // Wed Dec 31 16:00:00 PST 1969
        System.out.println( d );       
		 // Sun Jan 10 15:25:03 PST 1999
        System.out.println( copy );   
        
    } 
    
}
