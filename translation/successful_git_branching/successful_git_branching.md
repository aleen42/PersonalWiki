## A successful Git branching model - 一个成功的Git分支模型 [**Back**](./../translation.md)

> * 原文链接 : [A successful Git branching model](http://nvie.com/posts/a-successful-git-branching-model/)
* 原文作者 : [Vincent Driessen](http://nvie.com/about/)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者: 暂无
* 状态 :  翻译中

&#160; &#160; &#160; &#160;在这篇博文中，我将展示大概一年前我的一些项目（包括工作或者私人的项目）中，使用的开发模型。结果发现，这个模型的确是非常成功的一个模型。因此，我想把其记录成文档，但知道现在才腾出了时间。在这篇文章中，我并不会探讨项目的细节。我们将要讨论的将是分支的策略以及代码版本的控制。

<img src="./git-model@2x.png">

&#160; &#160; &#160; &#160;该模型将会使用 [Git](http://git-scm.com/) 作为工具，去对我们的源代码进行版本标记。（顺便一说的是，如果你对 Git 有兴趣，我们公司 [GitPrime](http://gitprime.com/) 会为你提供一些令人惊叹的实时数据分析工具，用于软件工程性能的分析）

### 为什么选择 Git？

&#160; &#160; &#160; &#160;因为我们通过集中几个源代码管理系统，就 Git 的优点以及缺点方面进行了彻底地讨论，详细可以[参考](http://whygitisbetterthanx.com/)我们的[网站](http://git.or.cz/gitwiki/GitSvnComparsion)。在这个问题上的斗争，可以说是非常的激烈。当今，作为一位开发人员，相比使用其他的工具，我更倾向于使用 Git。这是因为 Git 真正改变了开发人员对合并以及分支的思考

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
