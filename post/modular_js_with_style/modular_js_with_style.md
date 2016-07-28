## [轉載] 使用 AMD、CommonJS 及 ES Harmony 编写模块化的 JavaScript [Back](./../post.md)

> - Author: [Addy Osmani](http://twitter.com/addyosmani)
- Translate: [Gu YiLing](http://weibo.com/justineo)
- Origin: http://justineo.github.io/singles/writing-modular-js/

### 模块化（解耦应用程序的重要性）

当我们称一个应用程序是**模块化**的的时候，我们通常是指它由一组高度解耦的、存放在不同模块中的独特功能构成。你可能已经知道，[松散耦合](http://arguments.callee.info/2009/05/18/javascript-design-patterns--mediator/)通过尽可能地去除依赖性来让可维护性更加简单易得。当这一点被有效实现的时候，系统中某一部分的变化将如何影响其它部分就会变得显而易见。

然而，与一些更传统的编程语言不同的是，JavaScript 的当前版本（[ECMA-262](http://www.ecma-international.org/publications/standards/Ecma-262.htm) ）并没有为开发者们提供以一种简洁、有条理地的方式来引入模块的方法。规范的一大问题，就是未曾在这方面投入足够多的考量。直到近年来，人们对更为有序组织的 JavaScript 应用的需求变得越来越显著，这一情况才有所改观。

作为代替，当前的开发者们只能被迫降级使用[模块模式](http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth)或是[对象字面量模式](http://rmurphey.com/blog/2009/10/15/using-objects-to-organize-your-code/)的各种变体。通过很多这样的方法，各模块的脚本被串在一起注入到 DOM 中（译注：感谢 [@lkaihua](https://twitter.com/lkaihua/) 的确认，指的是作为 `script` 标签[注入](https://twitter.com/addyosmani/status/278514027892703232)到 DOM 中），其命名空间是由单一的全局对象来描述的。你的整个体系架构在这种模式下，仍然有可能发生命名冲突。想要简洁地管理依赖关系，不通过一些手工处理或借助第三方库往往是不可能的。

尽管这些问题的原生解决方案在 [ES Harmony](http://wiki.ecmascript.org/doku.php?id=harmony:modules) 中才会被引入，但好消息是，编写模块化的 JavaScript 目前已经变得极为简单，甚至今天就可以开始动手。

在本文中，我们将会考察三种编写模块化 JavaScript 的格式：**AMD**、**CommonJS** 以及 JavaScript 下一个版本——**Harmony** 中的提案。

### 序言（关于脚本加载器的注解）

要讨论 AMD 和 CommonJS 模块，我们必然会谈及一个显而易见的话题——脚本加载器。目前，脚本加载是为了让我们能在现今的各种应用中都能使用模块化的 JavaScript 这个目标而服务的。为此，使用一个兼容的脚本加载器不得不成为必须。为使大家能更好地读懂本文，我推荐大家先**大致**了解一下主流的脚本加载工具的工作原理，这样在这儿对模块格式所作的讨论也就更有意义了。

用来处理基于 AMD 和 CJS 格式进行模块加载的加载器为数众多，但我个人最偏爱的还是 RequireJS 和 curl.js。这些工具完整的入门教程已经在本文的讨论范围之外，但我还是推荐大家读一读 John Hann 关于 curl.js 的文章以及 James Burke 的 RequireJS 的 API 文档来了解更多相关内容。

从生产的角度，在处理这样的模块时，使用优化工具（例如 RequireJS Optimizer，即 RequireJS 优化器）来拼合脚本来进行部署是值得推荐的。有趣的是，只要有了 Almond AMD shim，RequireJS 甚至无须加入到部署完的站点之中，你当做脚本加载器的那个东西可以被轻松地从开发过程中移除出去。

尽管如此，James Burke 还是很可能会说，在页面加载完毕以后还能动态加载脚本的使用场景依然存在，并且 RequireJS 在这些场景下也有用武之地。带着上面的这些注解，让我们开始吧。
