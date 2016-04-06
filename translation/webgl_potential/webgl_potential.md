## The WebGL potential - WebGL的潜在性 [**Back**](./../translation.md)

> * 原文链接 : [The WebGL potential](http://typedarray.org/the-webgl-potential/)
* 原文作者 : [typedarray.org](http://typedarray.org/)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者 : 暂无
* 状态 : 翻译中

### WebGL的潜在性

&#160; &#160; &#160; &#160;由于 WebGL 支持性将更加广泛的谣言，特别是 IE 浏览器，因此，关于真正跨平台的一组 GPU API 的承诺基本上已经出现。我个人认为，这承诺如果实现，那么将会对在 web 上许多的东西产生影响，特别是关于人们怎么开发交互性的内容。但是，我也希望这能推进 web 前进。

#### WebGL 也可用于二维图像处理

<img src="./grotto-uv.png"> 

&#160; &#160; &#160; &#160;WebGL 基本上是一个对 OpenGL ES 2.0 功能集所开放的低级 JavaScript 接口（在场景后使用了 OpenGL/ES 2.0 或 DirectX）。大家都误以为 WebGL 是仅仅用于三维图形处理，而事实上并非所然。通过利用低级的基元，我们不仅能像 three.js 那样为三维图形处理重建出高级的结构，还能简化二维图像处理的基元，用于支持二维图像处理。两个三角形能够形成一个方形，且该方形能承接一个纹理。

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
