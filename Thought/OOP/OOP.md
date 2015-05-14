## OOP
<b style="font-size:40px;color:#a10000">When use them in practical, you'll know them.</b>
# SRP(Single Responsibility Principle) 
<b style="font-size:25px;">一个对象对应一个职责</b>
- 1.需要把对象设计成只有一个变化的原因
- 2.内聚(Cohension)是SRP的另一种表达，要尽可能设计成高内聚

# OCP(Open-Closed Principle)
<b style="font-size:25px;">对扩展开放，对修改关闭</b>
<p style="color:#a10000;">eg. 一个窗体类用于实现窗体应有的功能，这些功能的修改并不影响到外界的扩展(关闭)，而窗体上的内容扩展则是开放的，而不应该写在该窗体类里。</p>
- 1.设计一个模块时，要考虑到如何在不修改模块内部的情况下能进行扩展
- 2.实现的机制：封装、抽象、多态
- 3.完全对修改关闭是不现实的，因此我们不能滥用抽象

# LSP(Liskov Subsititution Priciple)
<b style="font-size:25px;">子类可以代替父类，父类不能代替子类</b>
<p style="color:#a10000;">eg. 动物是一个类，而猫这种物种是另外一个类。该原则的意思在于猫是一种动物，但动物不一定是猫。</p>
- 1.考虑如何良好地使用继承
- 2.IS-A关系是就行为方式而言，行为方式是可以进行合理假设的，是客户程序所依赖的


# DIP(Dependence Inversion Principle)
<b style="font-size:25px;">抽象不依赖于细节，细节依赖于抽象</b>
<p style="color:#a10000;">eg. 高层模块不应该依赖于底层模块，这样会导致高层模块的框架实现将依赖于细节，那么细节的改变必定会导致高层抽象模块的改变。</p>
- 1.Don't call us until we call you.
- 2.底层模块只是实现在高层模块的声明并为高层模块提供接口，高层模块并不涉及底层细节的实现