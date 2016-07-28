## [轉載] 使用 AMD、CommonJS 及 ES Harmony 编写模块化的 JavaScript [Back](./../post.md)

> - Author: [Addy Osmani](http://twitter.com/addyosmani)
- Translate: [Gu YiLing](http://weibo.com/justineo)
- Origin: http://justineo.github.io/singles/writing-modular-js/

### 模块化（解耦应用程序的重要性）

当我们称一个应用程序是**模块化**的的时候，我们通常是指它由一组高度解耦的、存放在不同模块中的独特功能构成。你可能已经知道，[松散耦合](http://arguments.callee.info/2009/05/18/javascript-design-patterns--mediator/)通过尽可能地去除依赖性来让可维护性更加简单易得。当这一点被有效实现的时候，系统中某一部分的变化将如何影响其它部分就会变得显而易见。

然而，与一些更传统的编程语言不同的是，JavaScript 的当前版本（[ECMA-262](http://www.ecma-international.org/publications/standards/Ecma-262.htm) ）并没有为开发者们提供以一种简洁、有条理地的方式来引入模块的方法。规范的一大问题，就是未曾在这方面投入足够多的考量。直到近年来，人们对更为有序组织的 JavaScript 应用的需求变得越来越显著，这一情况才有所改观。

作为代替，当前的开发者们只能被迫降级使用模块模式或是对象字面量模式的各种变体。通过很多这样的方法，各模块的脚本被串在一起注入到 DOM 中（译注：感谢 @lkaihua 的确认，指的是作为 script 标签注入到 DOM 中），其命名空间是由单一的全局对象来描述的。你的整个体系架构在这种模式下，仍然有可能发生命名冲突。想要简洁地管理依赖关系，不通过一些手工处理或借助第三方库往往是不可能的。

尽管这些问题的原生解决方案在 ES Harmony 中才会被引入，但好消息是，编写模块化的 JavaScript 目前已经变得极为简单，甚至今天就可以开始动手。

在本文中，我们将会考察三种编写模块化 JavaScript 的格式：AMD、CommonJS 以及 JavaScript 下一个版本——Harmony 中的提案。

### 序言（关于脚本加载器的注解）


