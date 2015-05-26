//: c08:Parcel4.java
// Nesting a class within a method.

public class Local_InnerClass {
  public Destination dest(String s) {
    class PDestination
        implements Destination {
      private String label;
      private PDestination(String whereTo) {
        label = whereTo;
      }
      public String readLabel() { return label; }
    }
    return new PDestination(s);
  }
  
  public static void main(String[] args) {
    Local_InnerClass p = new Local_InnerClass();
    Destination d = p.dest("Tanzania");
  }
} ///:~
