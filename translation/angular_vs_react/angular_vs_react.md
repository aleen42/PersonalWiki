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
