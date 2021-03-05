## Class [Back](./../Java.md)

- 屬性有默認值且可直接初始化(C++需要用在構造函數初始化)
- 一旦函數有構造函數Constructor, 默認的Constructor將失效
- 可以通過調用super來調用父類

### The order of Initialization

初始化順序|
------------|
static 成員(main前初始化) |
(继承部分初始化) |
屬性初始化 |
構造函數初始化|

### Override & Overload
What|Description
--------|------
Override|對繼承的方法進行重寫
Overload|重載函數,接受不同的參數調用不同的方法

### Polymorphism
- 多態的理解: 指不同對象處理同一事件的方式並不同

eg.貓與狗同屬於動物類, 動物有叫的方法. 但是對於貓和狗來說, 叫的方式不同.

- 多態的本質: Dynamic Binding(動態綁定)
- Upcast: Base_Class p = new Derived_Class();

多態的實現| Code
:----:|------
Inheritance|```class Sub_Cass extends Super_Cass{}```
Override|```public void method(){}```
Upcast|```Super_Class p = new Sub_Class();```
Call Child's Method|```p.method();```

### Inheritance
- 抽象類與接口都不能實例化
- 一個類只能繼承一個抽象類,原因菱形多重繼承存在二義性
- 一個類可以實現多個接口(間接實現多重繼承)
- 抽象類中可以有已經實現的方法, 但接口中不能實現方法
- 接口中的所有成員均為public
- 先extends, 後implements

#### Super Class:
```java
class Super_Class
{
	protected void method()
	{
		//method of superclass
	}
}

class Sub_Class
{
	@Override
	//@Override起到斷言作用，檢測所重寫的方法是否拼寫正確，否則報錯。若無該句，編譯器會認為這是新方法
	public void method()
	{
		//method of subclass
	}
}
```

#### Abstract Class:
```Java
abstract class Abstract_Class
{
	public abstract void method();
}

class Derived_Class extends Abstract_Class
{
	//(override)...
	public void method(){//...} //子類重寫的函數訪問級別不能比父類低
}
```
#### Interface:
```Java
class Derived_Class implements Iinterface
{
	//(implements)...
}
```

### Specifers: Static & Final
####Static
- static成員給所有該類中的成員提供訪問性,且可以保證唯一性(構造函數私有)
- 可直接通過類名調用static成員

#### Final
修飾對象|作用
:-----:|-----
Variable|常量(若是一個Object reference, 則指向對象不能發生改變, 但所指對象的值是可以修改的)
Method|不能重寫
Class|封閉類(不能被繼承)

### Access Specifers: Public, Private, Protected & Omitted
####Member
修飾符|可訪問性
:-----:|-----
Public|所有包的類都可訪問該成員
Omitted(缺省)|該包內的類可訪問該成員
Protected|與該類有繼承關係的可跨包訪問該成員或該包內的類可訪問該成員
Private|成員訪問性只控制在類內
####Class
修飾符|可訪問性
:-----:|-----
Public|所有包都可訪問該類(在一個Java源文件必須有且僅有一個)
Omitted(缺省)|只能在該包內訪問該類(可有多個或沒有)

###How to get the type of an instance
```Java
Student me = new Student("PuiMan Cheui", "13121215");
System.out.println(me.getClass().getName());
```

