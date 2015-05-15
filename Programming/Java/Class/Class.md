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
- 多態的本質: Dynamic Binding(動態綁定)
- Upcast: Base_Class p = new Derived_Class();

多態的實現| Code
:----:|------
Inheritance|```Java Class Derived_Cass extends Base_Cass{}```
Override|
Upcast|
Call Child's Method|



=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
