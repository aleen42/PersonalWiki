## Memory Leak Detection in C++ - 如何在 C++ 中检测出内存泄漏的情况 [**Back**](./../translation.md)

> * 原文链接 : [Memory Leak Detection in C++](http://www.linuxjournal.com/article/6556?page=0,0)
* 原文作者 : [Cal Erickson](http://www.linuxjournal.com/user/801087)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者: 暂无
* 状态 :  翻译中
* <img src="./cover110.small.jpg"> 来源问题：2013年7月第110号问题



&#160; &#160; &#160; &#160;谨记，千万不要延期修复内存泄漏的问题。而且，你可以使用一个或者多个的便捷检测工具，去作为你开发过程的一部分。

&#160; &#160; &#160; &#160;在早期，有那么一篇叫《在嵌入式系统中检测内存泄漏问题》，由LJ于2002年9月编写，并可在 [www.linuxjournal.com/article/6059](www.linuxjournal.com/article/6059) 查看的文章。该篇文章谈及到当我们使用 C 作为编程语言时，如何去检测内存泄漏的问题。而接下来，这篇文章将探讨如果是在 C++ 中，我们又如何检测呢？该文所谈及的检测工具，它们只能检测到应用程序的错误代码，但不能检测内核态下的内存泄漏情况。所有的这些工具，它们都被使用在 MontaVista Linux 专业版2.1和3.0产品上。其中的 dmalloc 更是被嵌入 MontaVista Linux 中。

&#160; &#160; &#160; &#160;当在嵌入式系统中开发应用程序时，设计师和工程师一定要对系统的内存资源，其使用情况要特别小心。不同于工作站（workstation）的是，嵌入式系统的内存资源非常有限。一般，只有理想的程序才不会占用任何的内存交换区（swap area）。当一个系统耗尽其资源时，它只能惊慌地扼杀掉部分的程序以腾出空间，给出所需要的资源。

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
