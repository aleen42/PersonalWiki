## Inner Class [Back](./../Java.md)

- Inner Class(內部類): 指的是嵌套在類裏面的類.
- 內部類多了Private和Protected的修飾符(跟成員級別的修飾符含義一樣)

Type|Description
---|---
成員內部類|定義在類裏的類, 作為一個外部類的成員
局部內部類|定義在方法內的類
匿名內部類|只定義一次的內部類

###內部類訪問外部類
- 可直接訪問(但靜態內部類不能訪問外部類的非靜態成員)

###外部類訪問內部類
成員類型|訪問方式
---|---
靜態成員|```InnerClass.member;```
非靜態成員|```new InnerClass().member;```

###定義(Definition)
```Java
OutterClass oc = new OutterClass();
OutterClass.InnerClass a = oc.new Innerclass();	//define a reference
```

###作用域(Scope)
```Java
x = 1;	//method裏的局部成員
this.x = 1;	//內部類的成員
OutterClass.this.x = 1;	//外部類的成員
```

###匿名內部類(Unnamed Inner Class)
- 不能定義Constructor(只能使用默認無參數的Constructor)
- 不能是抽象類

```Java
addMouseListner(new MouseAdapter()
{
	//implements
	public void MouseEntered()
	{
		//...
	}
}
);
```

