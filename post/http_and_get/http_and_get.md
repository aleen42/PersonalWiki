## [轉載] 99%的人都理解錯了HTTP中GET與POST的區別 [Back](./../post.md)

> - Author: WebTechGarden
> - Origin: http://mp.weixin.qq.com/s?__biz=MzI3NzIzMzg3Mw==&mid=100000054&idx=1&sn=71f6c214f3833d9ca20b9f7dcd9d33e4#rd
> - Time: Jun, 6th, 2016

<br />

> 評論: 希望借此機會理解一下HTTP中 GET 與 POST 請求的本質區別  - aleen42

GET和POST是HTTP请求的两种基本方法，要说它们的区别，接触过WEB开发的人都能说出一二。

最直观的区别就是GET把参数包含在URL中，POST通过request body传递参数。

你可能自己写过无数个GET和POST请求，或者已经看过很多权威网站总结出的他们的区别，你非常清楚知道什么时候该用什么。

当你在面试中被问到这个问题，你的内心充满了自信和喜悦。

你轻轻松松的给出了一个“标准答案”：![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/1.png)

- GET在浏览器回退时是无害的，而POST会再次提交请求。

- GET产生的URL地址可以被Bookmark，而POST不可以。

- GET请求会被浏览器主动cache，而POST不会，除非手动设置。

- GET请求只能进行url编码，而POST支持多种编码方式。

- GET请求参数会被完整保留在浏览器历史记录里，而POST中的参数不会被保留。

- GET请求在URL中传送的参数是有长度限制的，而POST么有。

- 对参数的数据类型，GET只接受ASCII字符，而POST没有限制。

- GET比POST更不安全，因为参数直接暴露在URL上，所以不能用来传递敏感信息。

- GET参数通过URL传递，POST放在Request body中。

（本标准答案参考自w3schools）

“很遗憾，这不是我们要的回答！”

请告诉我真相。。。![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/2.png)

如果我告诉你**GET和POST本质上没有区别**你信吗？ 

让我们扒下GET和POST的外衣，坦诚相见吧！

![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/3.png)

GET和POST是什么？HTTP协议中的两种发送请求的方法。

HTTP是什么？HTTP是基于TCP/IP的关于数据如何在万维网中如何通信的协议。

HTTP的底层是TCP/IP。所以GET和POST的底层也是TCP/IP，也就是说，GET/POST都是TCP链接。GET和POST能做的事情是一样一样的。你要给GET加上request body，给POST带上url参数，技术上是完全行的通的。 

那么，“标准答案”里的那些区别是怎么回事？

![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/4.png)

在我大万维网世界中，TCP就像汽车，我们用TCP来运输数据，它很可靠，从来不会发生丢件少件的现象。但是如果路上跑的全是看起来一模一样的汽车，那这个世界看起来是一团混乱，送急件的汽车可能被前面满载货物的汽车拦堵在路上，整个交通系统一定会瘫痪。为了避免这种情况发生，交通规则HTTP诞生了。HTTP给汽车运输设定了好几个服务类别，有GET, POST, PUT, DELETE等等，HTTP规定，当执行GET请求的时候，要给汽车贴上GET的标签（设置method为GET），而且要求把传送的数据放在车顶上（url中）以方便记录。如果是POST请求，就要在车上贴上POST的标签，并把货物放在车厢里。当然，你也可以在GET的时候往车厢内偷偷藏点货物，但是这是很不光彩；也可以在POST的时候在车顶上也放一些数据，让人觉得傻乎乎的。HTTP只是个行为准则，而TCP才是GET和POST怎么实现的基本。

但是，我们只看到HTTP对GET和POST参数的传送渠道（url还是requrest body）提出了要求。“标准答案”里关于参数大小的限制又是从哪来的呢？

![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/5.png)

在我大万维网世界中，还有另一个重要的角色：运输公司。不同的浏览器（发起http请求）和服务器（接受http请求）就是不同的运输公司。 虽然理论上，你可以在车顶上无限的堆货物（url中无限加参数）。但是运输公司可不傻，装货和卸货也是有很大成本的，他们会限制单次运输量来控制风险，数据量太大对浏览器和服务器都是很大负担。业界不成文的规定是，（大多数）浏览器通常都会限制url长度在2K个字节，而（大多数）服务器最多处理64K大小的url。超过的部分，恕不处理。如果你用GET服务，在request body偷偷藏了数据，不同服务器的处理方式也是不同的，有些服务器会帮你卸货，读出数据，有些服务器直接忽略，所以，虽然GET可以带request body，也不能保证一定能被接收到哦。

好了，现在你知道，**GET和POST本质上就是TCP链接，并无差别。但是由于HTTP的规定和浏览器/服务器的限制，导致他们在应用过程中体现出一些不同**。 


你以为本文就这么结束了？

![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/6.png)

我们的大BOSS还等着出场呢。。。

这位BOSS有多神秘？当你试图在网上找“GET和POST的区别”的时候，那些你会看到的搜索结果里，从没有提到他。他究竟是什么呢。。。

GET和POST还有一个重大区别，简单的说：
GET产生一个TCP数据包；POST产生两个TCP数据包。

长的说：
对于GET方式的请求，浏览器会把http header和data一并发送出去，服务器响应200（返回数据）；
而对于POST，浏览器先发送header，服务器响应100 continue，浏览器再发送data，服务器响应200 ok（返回数据）。

也就是说，GET只需要汽车跑一趟就把货送到了，而POST得跑两趟，第一趟，先去和服务器打个招呼“嗨，我等下要送一批货来，你们打开门迎接我”，然后再回头把货送过去。

因为POST需要两步，时间上消耗的要多一点，看起来GET比POST更有效。因此Yahoo团队有推荐用GET替换POST来优化网站性能。但这是一个坑！跳入需谨慎。为什么？
1. GET与POST都有自己的语义，不能随便混用。
2. 据研究，在网络环境好的情况下，发一次包的时间和发两次包的时间差别基本可以无视。而在网络环境差的情况下，两次包的TCP在验证数据包完整性上，有非常大的优点。
3. 并不是所有浏览器都会在POST中发送两次包，Firefox就只发送一次。

现在，当面试官再问你“GET与POST的区别”的时候，你的内心是不是这样的？

![](https://raw.githubusercontent.com/aleen42/PersonalWiki/master/post/http_and_get/7.png)

（本文原创，转载请注明转自微信公众号WebTechGarden）
（如文中有纰漏，请不吝更正）