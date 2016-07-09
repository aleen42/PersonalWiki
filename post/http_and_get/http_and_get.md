## [轉載] 99%的人都理解錯了HTTP中GET與POST的區別 [Back](./../post.md)

> - Author: WebTechGarden
- Origin: http://mp.weixin.qq.com/s?__biz=MzI3NzIzMzg3Mw==&mid=100000054&idx=1&sn=71f6c214f3833d9ca20b9f7dcd9d33e4#rd
- Time: Jun, 6th, 2016

<br />

> 評論: 希望借此機會理解一下HTTP中 GET 與 POST 請求的本質區別  - aleen42

GET和POST是HTTP请求的两种基本方法，要说它们的区别，接触过WEB开发的人都能说出一二。

最直观的区别就是GET把参数包含在URL中，POST通过request body传递参数。

你可能自己写过无数个GET和POST请求，或者已经看过很多权威网站总结出的他们的区别，你非常清楚知道什么时候该用什么。

当你在面试中被问到这个问题，你的内心充满了自信和喜悦。

你轻轻松松的给出了一个“标准答案”：![](1.png)

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

请告诉我真相。。。![](2.png)
