## Java OverView [Back](./../Java.md)
### Three main properties of Object-oriented Programming
- Inheritance(繼承)
- Encapsulation(封裝)
- Polymorphism(多態)

### Difference between C++ and Java
C++|Java
:----:|:-----:
編譯執行|解釋執行
兼容有C的面向過程|完全面向對象

### 平臺技術
- **JVM**

JVM(Java Virtual Machine): 屏蔽底層接口為上層提供統一接口, 從而實現平臺無關性

- **字節碼**(.class)

字節碼指Java源代碼編譯成機器代碼時的中間代碼

- **即用即插入**

一個.class文件可以引用多個.class文件

- **Java驗證器**

	- 類文件認證
	- 類型系統認證
	- 字節碼認證
	- 運行時類型與訪問檢查

- **JIT**(just in time)及時編譯技術

及時編譯技術指編譯時先把字節碼轉換成用戶機器的機器碼, 再執行該代碼指令.

### Properties of Java
- 多線程性
- 健壯性(Garbage Collection, Exception, Strict Type Check)
- 動態性
- 安全性
- 可移植性(平臺無關性)

### Some Syntax needed to pay attention to
- Legal identifiers(合法標識符) 
	- 不能以數字開頭
	- 除了_, $, ￥以外, 必須是英文字母或數字
	- 不能是關鍵詞(keyword)

- Operator(運算符)
	- Java中并没有運算符重載(C++含有該機制): 只能通過添加函數來解決
	- Java中並沒有sizeof(), 因為在JVM的基礎上, 各數據類型的佔用空間是一樣的, 並不需要通過sizeof()來獲取

- Statement(語句)
	- 無goto語句(C++含有該機制): goto的跳轉影響到代碼的結構性
	- break語句可帶標籤
	
		```Java
		label:
		{
			if(some_condition)
				break label;
			//...
		}
		```
	- for each語句的引入(C#含有該機制)

		```Java
		for(int element: a)
			System.out.println(element);
		```
		```cs
		// in c#
		foreach(int element in a)
			Console.WriteLine(element)；	
		```
		```java
		for(int element = 0; element < a.size(); element++)
			System.out.println(a[element]);
		```

- BigInteger 和 BigDecimal可以处理任意长度的数值

	```Java
BigInteger a = BigInteger.valueOf(100);
```

