## Exception [Back](./../Java.md)

###Exception & Error
- **Throwable**: The Throwable class is the superclass of all **errors** and **exceptions** in the Java language. Only objects that are instances of this class (or one of its subclasses) are thrown by the Java Virtual Machine or can be thrown by the Java `throw` statement. Similarly, only this class or one of its subclasses can be the argument type in a `catch` clause.

>Throwable
>>Exception

>>Error

####Exception
- Exception是可控或不可控的
- Exception通常是由于程序员的错误所导致的
- Exception应该应用级别就要处理

####Error
- Error总是不可控的
- Error通常是由于系统的错误所导致的
- Error应该在系统级别处理

###Checked Exception & Unchecked Exception
- Checked Exception: 指可以通過代碼處理的異常
- Unchecked Exception: 指並不能通過代碼處理的異常(通常指RuntimeException)

###Syntax

```Java
try
{
	//Something will throw exceptions
	Exception e = new IOExcetpion;
	throw e;	//throw an Exception instance and goto 1:
}
//...
catch(IOException e)	//Smaller Exception must be before the bigger one
{
1:	e.printStackTrace();	//Trace the throw of Exceptions and goto 2:
}
catch(Exception e)
{
	e.printStackTrace();
	throw e;	//throw this exception to upper level 
}
finally
{
2:	//Something must be done even if there is an exception
}
```

###throws specifier
```Java
public void method() throws IOException
{
	//means that method will probably throw an IOException
}
```

