public class EqualsDemo {
	int int1;
	SomeClass obj1;

	/** Constructor */
	public EqualsDemo(int i, SomeClass o) {
		int1 = i;
		obj1 = o;
	}

	public EqualsDemo() {
		this(0, new SomeClass());
	}

	/** Typical run-of-the-mill Equals method */
	public boolean equals(Object o) {
		if (o == null)		// caution
			return false;
		if (o == this)		// optimization
			return true;

		// Castable to this class?
		if (!(o instanceof EqualsDemo))
			return false;

		EqualsDemo other = (EqualsDemo)o;	// OK, cast to this class

		// compare field-by-field
		if (int1 != other.int1)			// compare primitives directly
			return false;
		if (!obj1.equals(other.obj1))	// compare objects using their equals
			return false;
		return true;
	}
}
