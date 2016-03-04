## Stack Overflow: The Architecture - Stack Overflow的系统架构 [**Back**](./../translation.md)

> * 原文链接 : [Stack Overflow: The Architecture - 2016](http://nickcraver.com/blog/2016/02/17/stack-overflow-the-architecture-2016-edition/)
* 原文作者 : [Nick Craver](https://github.com/NickCraver)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者: 暂无
* 状态 :  翻译中

&#160; &#160; &#160; &#160;为了弄明白我要说的这些东西到底是在“做”什么，我一开始将会以Stack Overflow更新的数据作出说明。与之前[2013年11份的数据](http://nickcraver.com/blog/2013/11/22/what-it-takes-to-run-stack-overflow/)相比，这里有一份2016年2月9日的统计数据及之间的数据差异。
- **209,420,973**（+61,336,090）HTTP请求到达我们的负载均衡器
- **66,294,789**（+30,199,477）属于页面加载
- **1,240,266,346,053**（+406,273,363,426）字节（1.24 TB）的HTTP流量被发送
- **569,449,470,023**（+282,874,825,991）字节（569 GB）的数据被接收
- **3,084,303,599,266**（+1,958,311,041,954）字节（3.08 TB）的数据被发送
- **504,816,843**（+170,244,740）的SQL查询（仅仅通过HTTP请求）
- **5,831,683,114**（+5,418,818,063）的Redis命中数
- **17,158,874**（在2013年的数据中并没有跟踪该项）的Elasticsearch使用数
- **3,661,134**（+57,716）的标签引擎（Tag Engine）请求数
- **607,073,066**（+48,848,481）毫秒（168 小时）用于执行SQL查询
- **10,396,073**（-88,950,843）毫秒（2.8 小时）用于Redis的命中
- **147,018,571**（+14,634,512）毫秒（40.8 小时）用于处理标签引擎（Tag Engine）的请求
- **1,609,944,301**（-1,118,232,744）毫秒（447 小时）用于ASP.Net的处理
- 平均**22.71**（-5.29）毫秒（在ASP.Net是19.12毫秒）用于49,180,275页面的呈现
- 平均**11.80**（-53.2）毫秒（在ASP.Net是8.81毫秒）用于6,370,076首页的呈现

&#160; &#160; &#160; &#160;也许，此刻你会在思考与2013年相比，为什么在每天有6100万以上请求数的情况下，ASP.Net的处理时间仍然会有明显的减少现象（减少了757小时）。这是因为我们[在2015年早期做了硬件升级](http://blog.serverfault.com/2015/03/05/how-we-upgrade-a-live-data-center/)，并且在应用级中对应用作出了大量的性能协调。请不要忘记，[性能这一点任然起着重要的作用](http://www.codinghorror.com/blog/2011/06/performance-is-a-feature.html)。听过我将要传达的信息后，如果你想知道更多关于硬件的细节——不用怕。我将会在下一次更新博文的时候，把关于所有正在运行的服务器，它们的硬件详情写在附录里。（而且只要它们还在运行，我都会更新这些详情）

&#160; &#160; &#160; &#160;那么，到底过去的两年发生了什么呢？除了更换部分的服务器和网络装置，没有其它。这里有一份现在还在运行的顶层硬件列表（并且指明了与2013年时的差别）：

- 4台使用Microsoft SQL Server的服务器（其中两部是新设备）
- 11台使用IIS Web Server的服务器（新设备）
- 2台使用Redis的服务器（新设备）
- 3台使用Tag Engine的服务器（其中三分之二是新设备）
- 3台使用Elasticsearch的服务器（没改变）
- 4台使用HAProxy的负载均衡器（其中新添置两台用于服务CloudFlare公司）
- 2个网络（每一个都使用Nexus 5596 Core + 2232TM Fabric Extenders，并且每处的宽度速率都提升到10Gbps）
- 2台使用Fortinet 800C的防火墙（替换了原来的Cisco 5525-X ASAs）
- 2台使用Cisco ASR-1001的路由器（替换了原来的Cisco 3945路由器）
- 2台使用Cisco ASR-1001-x的Routers（新设备！）

&#160; &#160; &#160; &#160;现在我们**需要**什么去运行Stack Overflow呢？这个与2013年相比并没有改变得太多，但归咎于性能的优化和上述的设备，我们至少还**需要**一台Web服务器。无意中，我们已经成功地测试了这台服务器几次。需要声明的是：我指的是它可以工作，但不是说这是一个好的方案。

&#160; &#160; &#160; &#160;既然有了用于构思的一些基准数字，那么我们来看看我们是怎么实现这个精致的网页。现在的系统几乎不会处于完全分离状态（我们的也不例外），如果架构师不用一副巨大的图像去展示如何将把部分组装成整体，那么他的决定往往不会起到作用。[后续的博文](https://trello.com/b/0zgQjktX/blog-post-queue-for-stack-overflow-topics)将会对特定的领域深入挖掘，而这里只是对需要强调的硬件设备作出逻辑性的概览。下次博文的更新将会有硬件的详情介绍。

&#160; &#160; &#160; &#160;为了能让你看看如今设备都是怎么样，这里有A架在2015年2月份更新期间的一些照片（它有一个对应的B架）

<img src="./TEb0jiPh.jpg">

……如果你要深入这种东西，[这里有这周的全部256张图的图集](http://imgur.com/a/X1HoY)。谈及到布局，我们要展示一张主要系统部分的逻辑概览图：

<img src="./layout.png">

### 基本法则

&#160; &#160; &#160; &#160;这里有一些为人熟知的法则，我就不一一去重复它们：

- 所有的东西都需要备份
- 所有服务器及网络设备都起码需要2 x 20Gbps的连接能力
- 所有服务器都需要两个电力供应点，而每个供应点都需要配额有两个UPS单元，而这些UPS单元都需要两个发电机和两个辅助设备供应。
- 所有服务器都有一组的备份：A架和B架
- 所有服务器都要备份多一个数据中心（位于科罗拉多州（Colorado））
- 所有的东西都需要备份！

### 因特网

&#160; &#160; &#160; &#160;首先你必须能找到我们——那就是通过[DNS](https://en.wikipedia.org/wiki/Domain_Name_System)。为了让你能快速地找到我们，我们（目前）把该业务外包给了[CloudFlare](https://www.cloudflare.com/)公司。原因在于他们在全世界分布着几乎能覆盖每一个人的DNS服务器，而我们只需要通过API去更新我们的DNS记录，然后把DNS的host查询交给他们。但是，根深蒂固的诚信问题仍然会烦扰着我们，因此我们也必须要有着属于自己的DNS服务器。末日将至（或许由GPL、[Punyon](https://twitter.com/JasonPunyon)或高速缓冲存储器导致），人类仍想着程序能脱离人类有着自己独立的思考。我们要推翻这种思想。

&#160; &#160; &#160; &#160;当你发现我们的秘密所在后，就会发现HTTP流量是会通过我们四台因特网服务提供者（ISP）中的其中一台（Level3、Zayo、Cogent和在纽约的Lightower）并经过我们四台边缘路由器的其中一台。对应着ISP，我们会使用[BGP](https://en.wikipedia.org/wiki/Border_Gateway_Protocol)（相当标准）。目的是为了控制访问流并提供几种访问途径使得你们可以有效地把我们搜索出来。[ASR-1001](http://www.cisco.com/c/en/us/products/routers/asr-1001-router/index.html)和[ASR-1001-X](http://www.cisco.com/c/en/us/products/routers/asr-1001-x-router/index.html)路由器都是采用对的形式，而且每一对都以active/active的形式服务于两个ISP——这就是我们的备份所在。虽然这两种路由器都是处于同样的10Gbps速率的网络当中，但是外部的访问都是分配在连接着负载均衡器的外部[VLAN](https://en.wikipedia.org/wiki/Virtual_LAN)当中。当经过路由器后，我们就会看到一个负载均衡器。

&#160; &#160; &#160; &#160;我认为是时候要告诉你们的是我们已经在两个数据中心之间建立了带有10Gbps能力的[MPLS](https://en.wikipedia.org/wiki/Multiprotocol_Label_Switching)，但它并不是直接用于服务。在我们遇到突发事件的情况下，我们会使用它来进行数据的拷贝和快速的恢复。或许，你会说“Nick，这并不是数据备份”。在技术上来说，你的观点是正确的（[最佳的正确](https://www.youtube.com/watch?v=hou0lU8WMgo)），因为在这策略上存在着单点失效的严重问题。但是我需要补充的是，我们还维护着两台以上具有故障转移能力的[OSPF](https://en.wikipedia.org/wiki/Open_Shortest_Path_First)路由器（MPLS只是其中的一台）经过我们的ISP。上述所涉及的所有这些东西，它们每一个都连接着位于科罗拉多（Colorado）对应的集，并在故障转移的情况下，对流量进行负载均衡处理。我们可以做的就是把各组集都连接在一起，并形成四个路径，然而，这个工作仍在继续。

### 负载均衡器（[HAProxy](http://www.haproxy.org/)）

&#160; &#160; &#160; &#160;负载均衡器是在[CentOS 7](https://www.centos.org/)上运行[HAProxy](http://www.haproxy.org/)的1.5.15版本，因为CentOS 7是我们较为喜欢的Linux版本。至于TLS（SSL）的流量，最终也会停留在HAProxy上。而Haroxy的1.7版本中支持HTTP/2的新特性是我们最为期待的。

&#160; &#160; &#160; &#160;与其他那些带有双10Gbps LACP网络连接的服务器不同的是，每一个负载均衡器都有两对的10Gbps网络接口：一个用于外部网络连接，而另一个则用于与隔离网络（DMZ）的连接。为了更有效地处理SSL协商，这些负载均衡器至少会使用64GB的内存。使用缓存时，越能命中更多内存中的TLS段去重用，我们在后面连接到同一个客户端时就越不需要再进行重新计算。这就意味着我们能更快更廉价地回到某一段中。只要RAM以美元计算足够的便宜，那么这就是一很好的方案。

&#160; &#160; &#160; &#160;其实，负载均衡器本身就是一种非常简单的装置。我们监听着不同的IP地址（大部分是为了确保安全和DNS的管理）并在host头的基础上路由至不同的后端服务器。这是因为我们有一件事情需要完成。那就是进行流量控制和对部分被写入[HAProxy系统日志的信息](https://cbonte.github.io/haproxy-dconv/configuration-1.5.html#3.1-log)，其HTTP头部进行获取（从我们的网络层发出）。通过这样，我们就能记录每一条请求，它们的性能指标。具体的细节我们[在后面会谈及到](https://trello.com/c/1Oc9cC6u/11-monitoring)。

### 网络层（IIS 8.5、ASP.NET MVC 5.2.3和.Net 4.6.1）

&#160; &#160; &#160; &#160;负载均衡器把流量分发到我们指定的9台主要服务器（01~09）和两个设备/元网络服务器（10~11， 我们搭建的环境）。除了[meta.stackoverflow.com](http://meta.stackoverflow.com/)和[meta.stackexchange.com](http://meta.stackexchange.com/)这两个页面是运行在后面的两台网络服务器之外，像Stack Overflow、Careers和所有的Stack Exchange页面都是运行在我们的主要服务器上。至于主要的Q&A应用，它本身是一个多架构的应用。这就意味着一个独立的应用就能服务于所有来自Q&A页面的请求。换句话说，那就是我们能用一个仅仅配有一台服务器的应用去运行整个Q&A网络。而其他的运用，像Careers、API v2、Mobile API等，它们都是相互独立的。下面的图片展示了在IIS上我们的主要层和设备层是怎么分布的：

<img src="./SO-Architecture-IIS-NY-WEB01.png"><img src="./SO-Architecture-IIS-NY-WEB10.png">

&#160; &#160; &#160; &#160;这张是展示Stack Overflow如何把穿梭在网络层的服务器分布式存储在[Opserver](https://github.com/Opserver/Opserver)（我们的内部镜像面板）：

<img src="./SO-Architecture-Opserver-HAProxy.png">

……还有一张是展示这些服务器的利用效率是怎样的：

<img src="./SO-Architecture-Opserver-WebTier.png">

&#160; &#160; &#160; &#160;后面的文章我会提及为什么我们会如此过度供应，但是目前最应该考虑的应该是：滚动构建、净空值以及冗余度。

### 服务层（IIS、ASP.Net MVC 5.2.3、.Net 4.6.1和HTTP.SYS）

&#160; &#160; &#160; &#160;在这些网络服务器后是一层十分相像的“服务层”。它也是运行安装在Windows 2012R2上的IIS 8.5版本。该层会运行内部服务以支持网络层和其他内部系统的使用。其中，基于`http.sys`（不是IIS服务之后）运行着标签引擎的“Stack Server”和Providence API（基于IIS）分别扮演着重要角色。有趣的是，其实我们还需要为这两个处理器都设置锁定关系。这是为了能使数据降落于互相隔离的socket上。因为，Stack Server每两分钟刷新问题列表时，都会给L2和L3缓存造成巨大的压力。

&#160; &#160; &#160; &#160;这些服务器通过引擎标签和后端API进行着繁重的数据提取操作，而这些后端API我们都需要进行备份，但并不需要9x备份。例如，在加载所有的post文章和它们的标签时并不是一件非常容易的事情，而且这些东西在数据库中每`n`分钟就会改变一次（目前平均是2分钟）。因此我们不想在网络层加载9次这些数据；3次便已足够，并且数据通过3次读取能足够安全地传达到我们的手里。另外，我们还为了能更好的根据不同的计算性加载操作时标签引擎的特点和弹性索引工作特点（这项工作也是在该层进行）进行优化，对这些服务器进行了硬件层面上不同的配置。“标签引擎”本身就是一个相当复杂的话题，因我们将会专门为其[写文讨论](https://trello.com/c/DqklJDSF/29-tag-engine)。基本来说就是：当你访问`/questions/tagged/java`,你就是正在使用标签引擎去查看哪个问题匹配上。因为它会在文件`/search`外对所有的标签进行一次遍历匹配，因此我们的[新型导航](http://meta.stackoverflow.com/questions/308875/new-navigation-release-candidate)等应用都是全部使用这个服务去获取数据。

### 缓存 & 发布/订阅（[Redis](http://redis.io/)）

&#160; &#160; &#160; &#160;在这里，我们使用[Redis](http://redis.io/)去完成一些事情。那是因为，Redis其坚如磐陀。尽管每个月需要处理1600亿的操作，但是每个Redis实体都只是占用了不到2%的CPU资源。而且更多时候是比这个要少得多：

<img src="./SO-Architecture-Redis-Utilization.png">

&#160; &#160; &#160; &#160;我们有一个配有Redis的L1/L2缓存系统。“L1"用于缓存网络服务器上的HTTP缓存，或者是任何一个正在运行的应用其缓存。”L2"则用于回落到Redis去取出所需要的值。我们的值是通过使用Marc Gravell发明的[protobuf-dot-net](https://github.com/mgravell/protobuf-net)组成[Protobuf格式](https://developers.google.com/protocol-buffers/)存储起来。对于客户端来说，我们会使用[StackExchange.Redis](https://github.com/StackExchange/StackExchange.Redis)——内部编写并开源。当一部网络服务器不能从L1和L2中获取到缓存时，它会从数据源（通过数据库查询、APIdia）取出所需要的值

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
