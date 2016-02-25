## Stack Overflow: The Architecture - Stack Overflow的系统架构 [**Back**](./../translation.md)

> * 原文链接 : [Stack Overflow: The Architecture - 2016](http://nickcraver.com/blog/2016/02/17/stack-overflow-the-architecture-2016-edition/)
* 原文作者 : [Nick Craver](https://github.com/NickCraver)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者: 暂无
* 状态 :  翻译中

为了弄明白所有的这些东西到底是在“做”什么，我一开始将以Stack Overflow更新的每日数据说明。与[之前2013年11份的数据](http://nickcraver.com/blog/2013/11/22/what-it-takes-to-run-stack-overflow/)相比，这里有一份2016年2月9日的日统计数据及之间的数据差异。
- **209,420,973** (+61,336,090) HTTP请求到达我们的负载均衡器
- **66,294,789** (+30,199,477) 属于页面加载
- **1,240,266,346,053** (+406,273,363,426) 字节 (1.24 TB) 的HTTP流量被发送
- **569,449,470,023** (+282,874,825,991) 字节 (569 GB) 的数据被接收
- **3,084,303,599,266** (+1,958,311,041,954) 字节 (3.08 TB) 的数据被发送
- **504,816,843** (+170,244,740) SQL查询(仅仅通过HTTP请求)
- **5,831,683,114** (+5,418,818,063) Redis命中数
- **17,158,874** (not tracked in 2013) Elastic searches

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
