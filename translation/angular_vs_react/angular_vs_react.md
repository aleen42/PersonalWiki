## Angular vs. React - the tie breaker - Angulr 对比 React - 决胜局 [**Back**](./../translation.md)

> * 原文链接 : [Angular vs. React - the tie breaker](https://www.airpair.com/angularjs/posts/angular-vs-react-the-tie-breaker)
* 原文作者 : [Amit Kaufman](https://github.com/amitkaufman)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者 : 暂无
* 状态 : 翻译中

![](./EgrRejl.png)

## 1. 简介

&nbsp; &nbsp; &nbsp; &nbsp;在不久前，我们开发团队需要为 Wix 公司的其中一个旗舰产品 —— html wysiwyg 网页编辑器，选定一种开发框架技术。该产品是一个大型的单页面应用。由于里面含有复杂的逻辑、大量与其他内敛框架（iframe）和服务器之间的通信，以及许多的用户体验性操作，团队的开发人数多达40人。此前，我们对 ReactJS 和 AngularJS 都有一定的开发经验。但是，框架的选定却在两者间徘徊不定。这是因为，一方面，AngularJS 的声明式编程思想使得框架变得易于使用。另一方面，ReactJS 带给了我们开发的简易性。一系列的概念证明促使我们形成了这次的决胜局。下面，该文将带大家探讨一下两者之间的对决。

### 1.1 打包

&nbsp; &nbsp; &nbsp; &nbsp;打包（packaging）指的是一种能使得代码以预期方式运行并部署的方法。为了达到快速的加载，我们希望在前期只加载最低条件下所需要的代码，并在后期根据所需逐步加载。如果能这样的话，我们就不需要在开发新功能时，考虑是否会降低加载速度的问题。

&nbsp; &nbsp; &nbsp; &nbsp;对于这方面需求，AngularJS 只提供了少量限制的方法去实现（大部分是 html 模板），而且当我们尝试去实现的时候，我们发现我们其实只是在组装代码而已。

&nbsp; &nbsp; &nbsp; &nbsp;简而言之，Angular 框架太过于固执与死板。相反, React 并没有理会太多。它可以直接结合 plain JS使用，而我们只需要使用 requirejs，就能实现对部分代码的延迟加载。此外，React 还可以与其他像 webpack 的打包工具共同使用。

*胜者：React*

### 1.2 学习曲线

&nbsp; &nbsp; &nbsp; &nbsp;我相信每个人都知道，精通 Angular 之路颠簸且漫长：入门虽快，经久衰败，犹如婚姻……

&nbsp; &nbsp; &nbsp; &nbsp;至于 React，我们发现只需要花费大概一周的时间去学习，就能到达一个较高的层次。只需些许时间，我们就能习惯于该种单向流动。尤其是对于 web 开发者来说，一旦你能花那么点时间去学习 React 的话，那么整个框架都会变得清晰易懂。

&nbsp; &nbsp; &nbsp; &nbsp;Angular 的生命周期是非常复杂的，倘若不去细致查看框架的代码，是无法达到精通的境界。在该框架的编译和链接期间，它并不能给到你一个直观的界面去查看详细的过程。正因为这样，在某种的情况下，如若遇到异常，你会感到无比疑惑（该异常有可能是来自编译时的大量递归或指令间的冲突）。相对的，React 只含有少量的生命周期方法，而且这些方法的定义都是不言而喻。所以，使用 React 其中一个最大的特征就是你并不需要去阅读它自身的代码。

*胜者：React*

### 1.3 抽象

&nbsp; &nbsp; &nbsp; &nbsp;好的抽象是无比重要的，因为抽象能为我们开发者带来快速的开发接口并隐藏开发中不必要的细节。

&nbsp; &nbsp; &nbsp; &nbsp;Angular 的抽象存在有一定的纰漏。这就意味着只有清楚地了解基础模型后，我们才能真正地运用起这些抽象的方法。这就是为什么这么多开发者在调试自身代码的过程中需要大量调试 Angular 框架内部的代码。