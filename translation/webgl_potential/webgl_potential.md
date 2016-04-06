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

&#160; &#160; &#160; &#160;[WebGL](http://www.khronos.org/webgl/) 基本上是一个对 OpenGL ES 2.0 功能集所开放的低级 JavaScript 接口（在场景后使用了 OpenGL/ES 2.0 或 DirectX）。大家都误以为 WebGL 是仅仅用于三维图像处理，而事实上并非所然。通过利用低级的基元，我们不仅能像 [three.js](https://github.com/mrdoob/three.js/) 那样为三维图像处理重建出高级的结构，还能简化二维图像处理的基元，用于支持二维图像处理。我们都知道，两个三角形能够形成一个方形，且该方形能承接一个纹理。这就是为什么二维图形 GPU 加速能出现我们的眼前。大部分像 [Cocos2D-x](http://www.cocos2d-x.org/) 或 [Pixi.js](https://github.com/GoodBoyDigital/pixi.js) 等框架都是通过回退到 Canvas 去实现加速，这是因为 WebGL 无法做到的。你需要滤波、颗粒度效果吗？通过使用像 WebGL 提供的一个可编程管道（着色程序），我们也能实现图像的可再生化。

&#160; &#160; &#160; &#160;在我们[为 Flash 开发 Stage3D 库时](http://www.youtube.com/watch?v=c0IwvN4IdH4)，我们就想着尽可能地揭露低级的基元，以使得人们可以在这基础上开发他们所需要的框架。特别是对于游戏开发者来说，他们迫切需要通过颗粒度等级来控制所有的一切事物，并获得超乎想象的高性能。另一方面，我们了解到大部分开发者会热衷于使用他们熟悉的高级别 API 分离基元，而不是低级别的 GPU 基元。因此，我们创造出了 [Starling](http://gamua.com/starling)。它可以基于 Stage3D 之上，快速成为二维图像内容的框架。Rivio 通过使用该框架，把 [Angry Birds](https://apps.facebook.com/angrybirds/?fb_source=timeline) 装载于 Facebook 中。此外，Zynga 最近也通过该框架装载了 [Ruby Blast](https://apps.facebook.com/rubyblast/?fb_source=search&ref=ts&fref=ts)。

&#160; &#160; &#160; &#160;除了帮助游戏开发之外， WebGL还能推动了交互的体验以及部分的数字化营销页面，像为人熟知多年的 [thefwa.com](http://www.thefwa.com/) 和传统通过 Flash 实现交互的交付物。不仅如此，它还彻底变更了开发者构件移动端应用的方式。所有你在手机上所能欣赏到的平缓 UI 组件，全都是通过 GPU 加速的，且由 OpenGL ES 2.0（iOS、Android）或 DirectX（Windows 8）所提供服务支持。当然，我希望能有越来越多的 UI 框架出现，以提供基于 WebGL 上通过 GPU 快速加速的 UI 组件。[Feathers](http://feathersui.com/) 就是一个很好的例子。

&#160; &#160; &#160; &#160;这意味着我们都通过 WebGL 去完成所有的事情？并不是，这取决于实际的情况。对于多文本内容来说，使用一个由 CSS 定义样式的传统 DOM，会更加的有效，像一个新闻页面、一个论坛或简单的表单应用。CPU 是善于处理像字体编译或矩阵计算等其他事情。因此，如果我们能结合好两者（基于 CPU 或 GPU 的编译器），这将会是一个很强大的混合。

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
