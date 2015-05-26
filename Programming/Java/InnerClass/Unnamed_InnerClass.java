//: c08:Parcel8.java
// An anonymous inner class that performs 
// initialization. A briefer version
// of Parcel5.java.

public class Unnamed_InnerClass {
  // Argument must be final to use inside 
  // anonymous inner class:
  public Destination dest(final String dest) {
    return new Destination() {
      private String label = dest;
      public String readLabel() { return label; }
    };
  }
  public static void main(String[] args) {
    Unnamed_InnerClass p = new Unnamed_InnerClass();
    Destination d = p.dest("Tanzania");
    System.out.println(d.readLabel());
  }
} ///:~
