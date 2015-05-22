import java.util.*;

class HashTableDemo
{
    public static void main(String[] args)
{
        Hashtable h = new Hashtable();
        h.put("dog", "spot");
        h.put("cat", "luck");
        h.put("cow", "spot");
        h.put("yak", "spot");
        //! h.put("2",1);  //error
     
       // h.put("1",new Integer(1));
        h.put("1",new Integer(2));
        String s = (String)h.get("dog");  //get a object
        System.out.println((Integer)h.get("1"));
       
        Collection col = h.values();
	    // [luck, spot, spot, spot, ]
        printCol( col );                     
        // true
        System.out.println( col.contains(new String("spot")) );  

        // remove() removes one entry from the h.
        col.remove("spot");
        // {cat=luck, cow=spot, yak=spot}
        System.out.println( h );             
        // removeAll() removes all entries with the value "spot".
        col.removeAll(Collections.singleton("spot"));
        // {cat=luck}
        System.out.println( h );             
        // Add to the h and check the collection
        h.put("dog", "spot");
        // [luck, spot, ]
        printCol( col );                     
        // You can't add to the collection.
        //col.add("bess");                   
// UnsupportedOperationException
    }

    static void printCol(Collection c) 
	{
        System.out.print("[");
        for (Iterator it=c.iterator(); it.hasNext(); )
		{
            System.out.print(it.next()+", ");
        }
        System.out.println("]");
    }
}
