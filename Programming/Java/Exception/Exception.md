## Exception [Back](./../Java.md)
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

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
