
/** 
 * Threaded demo application, using Runnable.
 *
 * @author	Ian Darwin
 *
 * @version	1.0
 */
public class ThreadsDemo2 implements Runnable {
	String mesg;
	Thread t;
	int count;

	/**
	 * Main program, test driver for ThreadsDemo2 class.
	 */
	public static void main(String[] argv) {
		//error:  new ThreadsDemo2("Hello from X", 10).start();   //because Runable only have one method run()
		//error:  new ThreadsDemo2("Hello from Y", 15).start();
		new ThreadsDemo2("Hello from X", 10);
		new ThreadsDemo2("Hello from Y", 15);
	}

	/**
	 * Construct a ThreadDemo object
	 *
	 * @param	String m	Message to display
	 * @param	int n		How many times to display it
	 */
	public ThreadsDemo2(String m, int n) {
		count = n;
		mesg  = m;
		//illustrate how to start a thread when use implements Runable
		t = new Thread(this);
		t.setName(m + " runner Thread");
		t.start();
	}

	/** Run does the work. We override the run() method in Runnable. */ 
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

	void println(String s) {
		System.out.println(s);
	}
}
