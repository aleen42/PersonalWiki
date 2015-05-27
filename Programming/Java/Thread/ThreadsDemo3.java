
/** 
 * Threaded demo application, using inner class as Runnable.
 *
 * @author	Ian Darwin
 *
 * @version	1.0
 */
public class ThreadsDemo3 {
	String mesg;
	Thread t;
	int count;

	/**
	 * Main program, test driver for ThreadsDemo3 class.
	 */
	public static void main(String[] argv) {
		new ThreadsDemo3("Hello from X", 10);
		new ThreadsDemo3("Hello from Y", 15);
	}

	/**
	 * Construct a ThreadDemo object
	 *
	 * @param	String m	Message to display
	 * @param	int n		How many times to display it
	 */
	public ThreadsDemo3(String m, int n) {
		count = n;
		mesg  = m;
		t = new Thread(new Runnable() {
			public void run() {
				while (count-- > 0) {
					println(mesg);
					try {
						Thread.sleep(100);	// 100 msec
					} catch (InterruptedException e) {
						return;
					}
				}
				println(mesg + " thread all done.");
			}
		});
		t.setName(m + " runner Thread");
		t.start();
	}

	void println(String s) {
		System.out.println(s);
	}
}
