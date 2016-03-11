## Memory Leak Detection in C++ - 如何在 C++ 中检测出内存泄漏的情况 [**Back**](./../translation.md)

> * 原文链接 : [Memory Leak Detection in C++](http://www.linuxjournal.com/article/6556?page=0,0)
* 原文作者 : [Cal Erickson](http://www.linuxjournal.com/user/801087)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者: 暂无
* 状态 :  翻译中

&#160; &#160; &#160; &#160;谨记，千万不要延期修复内存泄漏的问题。而且，你可以使用一个或者多个的便捷检测工具，去作为你开发过程的一部分。

&#160; &#160; &#160; &#160;在早期，有那么一篇叫《在嵌入式系统中检测内存泄漏问题》，由LJ于2002年9月编写，并可在 [www.linuxjournal.com/article/6059](www.linuxjournal.com/article/6059) 查看的文章。该篇文章谈及到当我们使用 C 作为编程语言时，如何去检测内存泄漏的问题。而接下来，这篇文章将探讨如果是在 C++ 中，我们又如何检测呢？

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
