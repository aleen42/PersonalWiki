## Type [Back](./../Java.md)

### Value Type & Reference Type
```Java
int a = 3;	//基本類型(堆棧), 基本類型只有作為類的屬性時才有默認值
Integer a = new Integer(3);	//對象(堆) 
```

### Object Reference & Pointer
```Java
//in java
C q = new C();	//q is an Object Reference
```
```cpp
//in cpp
C *q = new C();	//q is an Pointer
```

### Array
```Java
int[] a = new int[10];
int[] b = a;
b[1] = 1;	//a[1] = 1

Employee[] emArray =  new Employee[1];	//an array which stores object
										//references point to nothing.
emArray[0] = new Employee();
emArray[1] = new Employee();

//arraycopy(from, fromindex, to, toindex, num);
```

### Equals() & ==
```Java
String s1 = "abc";
String s2 = "abc";
String s3 = new String("abc");

System.out.println(s1 == s2);	//true
System.out.println(s1 == s3);	//false
System.out.pritnln(s1.equals(s3));	//true

//equals() must be overrided when design a new class	
```

