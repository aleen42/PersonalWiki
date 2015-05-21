/** An example of a Singleton implementation in Java.
 *
 * @author Ian F. Darwin, ian@darwinsys.com
 * @version $Id: Singleton.java,v 1.4 2000/11/25 17:54:20 ian Exp $
 */
public class Singleton {

	private static Singleton singleton;

	protected String name;

	/** The only constructor, the private no-argument constructor,
	 * can only be called from this class, i.e., within the factory method.
	 * It should be called exactly once, i.e., the first time the static 
	 * factory is called.
	 */
	private Singleton() {
		if (singleton == null)
			singleton = this;
		else throw new IllegalArgumentException(
			"Default constructor called more than once.");
	}

	// A static 'factory' methods

	static Singleton getInstance() {
		if (singleton == null)
			new Singleton();
		return singleton;
	}

	public static void main(String[] argv) {
		System.out.println("getInstance returns " + getInstance());
		System.out.println("getInstance returns " + getInstance());
		System.out.println("getInstance returns " + getInstance());
	}
}
