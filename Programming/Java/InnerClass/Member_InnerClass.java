//: c08:Member_InnerClass.java
// Creating inner classes.

public class Member_InnerClass {
	private int ll=5;
  class Contents {
    private int i = 11;
    public int value() { return i; }
  }
  class Destination {
    private String label;
    Destination(String whereTo) {
      label = whereTo;
    }
    String readLabel() { 
    	f();                         //in inner class, can visit the method or variable in the closing calss 
   	    System.out.println(ll);
   	     return label; 
   }
  }
  // Using inner classes looks just like
  // using any other class, within Parcel1:
  public void ship(String dest) {
    Contents c = new Contents();
    Destination d = new Destination(dest);
    System.out.println(d.readLabel());
  }  
  public void f() {}
  public static void main(String[] args) {
    Member_InnerClass p = new Member_InnerClass();
    p.ship("Tanzania");
  }
} ///:~
