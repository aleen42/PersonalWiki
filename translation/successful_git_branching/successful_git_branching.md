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

&#160; &#160; &#160; &#160;因为我们通过集中几个源代码管理系统，就 Git 的优点以及缺点方面进行了彻底地讨论，详细可以[参考](http://whygitisbetterthanx.com/)我们的[网站](http://git.or.cz/gitwiki/GitSvnComparsion)。在这个问题上的斗争，可以说是非常的激烈。当今，作为一位开发人员，相比使用其他的工具，我更倾向于使用 Git。这是因为 Git 真正改变了开发人员对合并分支（merging）以及建立分支（branching）的思考。从经典的并发版本控制系统（CVS）/子系统（Subversion）世界过来的我，总是认为合并分支/建立分支是何等的吓人（“请小心合并分支时产生的冲突，因为它是会随时咬你的”）。而且，这又是你等会将需要做的唯一事情，而这事情又是你每次都需要做的。

&#160; &#160; &#160; &#160;然而，自从有了 Git 后，这一切的动作都将变得如此简单和便捷。而且，这一动作也将成为你日常工作流中的重要环节之一。举个例子来说，在并发版本控制系统/子系统的[相关书籍](http://svnbook.red-bean.com/)中，建立分支和合并分支都只是在最后的章节作出首次的提及（对于需要高级操作的用户有用），然而在[每一个讲述 Git 的书籍](http://pragprog.com/titles/tsgit/pragmatic-version-control-using-git)中，这将会在第三个章节就会被提及到（作为基础部分）。

&#160; &#160; &#160; &#160;作为简洁和自然重复的结果，建立分支与合并分支不再是一种可怕的存在。而版本控制工具则应该去协助建立分支/合并分支的操作。

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
