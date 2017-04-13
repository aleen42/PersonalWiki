## [轉載] 使用 AMD、CommonJS 及 ES Harmony 编写模块化的 JavaScript [Back](./../post.md)

> - Author: [Addy Osmani](http://twitter.com/addyosmani)
> - Translate: [Gu YiLing](http://weibo.com/justineo)
> - Origin: http://justineo.github.io/singles/writing-modular-js/

### 模块化（解耦应用程序的重要性）

当我们称一个应用程序是**模块化**的的时候，我们通常是指它由一组高度解耦的、存放在不同模块中的独特功能构成。你可能已经知道，[松散耦合](http://arguments.callee.info/2009/05/18/javascript-design-patterns--mediator/)通过尽可能地去除依赖性来让可维护性更加简单易得。当这一点被有效实现的时候，系统中某一部分的变化将如何影响其它部分就会变得显而易见。

然而，与一些更传统的编程语言不同的是，JavaScript 的当前版本（[ECMA-262](http://www.ecma-international.org/publications/standards/Ecma-262.htm)）并没有为开发者们提供以一种简洁、有条理地的方式来引入模块的方法。规范的一大问题，就是未曾在这方面投入足够多的考量。直到近年来，人们对更为有序组织的 JavaScript 应用的需求变得越来越显著，这一情况才有所改观。

作为代替，当前的开发者们只能被迫降级使用[模块模式](http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth)或是[对象字面量模式](http://rmurphey.com/blog/2009/10/15/using-objects-to-organize-your-code/)的各种变体。通过很多这样的方法，各模块的脚本被串在一起注入到 DOM 中（译注：感谢 [@lkaihua](https://twitter.com/lkaihua/) 的确认，指的是作为 `script` 标签[注入](https://twitter.com/addyosmani/status/278514027892703232)到 DOM 中），其命名空间是由单一的全局对象来描述的。你的整个体系架构在这种模式下，仍然有可能发生命名冲突。想要简洁地管理依赖关系，不通过一些手工处理或借助第三方库往往是不可能的。

尽管这些问题的原生解决方案在 [ES Harmony](http://wiki.ecmascript.org/doku.php?id=harmony:modules) 中才会被引入，但好消息是，编写模块化的 JavaScript 目前已经变得极为简单，甚至今天就可以开始动手。

在本文中，我们将会考察三种编写模块化 JavaScript 的格式：**AMD**、**CommonJS** 以及 JavaScript 下一个版本——**Harmony** 中的提案。

### 序言（关于脚本加载器的注解）

要讨论 AMD 和 CommonJS 模块，我们必然会谈及一个显而易见的话题——脚本加载器。目前，脚本加载是为了让我们能在现今的各种应用中都能使用模块化的 JavaScript 这个目标而服务的。为此，使用一个兼容的脚本加载器不得不成为必须。为使大家能更好地读懂本文，我推荐大家先**大致**了解一下主流的脚本加载工具的工作原理，这样在这儿对模块格式所作的讨论也就更有意义了。

用来处理基于 AMD 和 CJS 格式进行模块加载的加载器为数众多，但我个人最偏爱的还是 [RequireJS](http://requirejs.org/) 和 [curl.js](https://github.com/unscriptable/curl)。这些工具完整的入门教程已经在本文的讨论范围之外，但我还是推荐大家读一读 John Hann 关于 [curl.js](http://unscriptable.com/index.php/2011/03/30/curl-js-yet-another-amd-loader/) 的文章以及 James Burke 的 [RequireJS](http://requirejs.org/docs/api.html) 的 API 文档来了解更多相关内容。

从生产的角度，在处理这样的模块时，使用优化工具（例如 RequireJS Optimizer，即 RequireJS 优化器）来拼合脚本来进行部署是值得推荐的。有趣的是，只要有了 [Almond](https://github.com/jrburke/almond) AMD shim，RequireJS 甚至无须加入到部署完的站点之中，你当做脚本加载器的那个东西可以被轻松地从开发过程中移除出去。

尽管如此，James Burke 还是很可能会说，在页面加载完毕以后还能动态加载脚本的使用场景依然存在，并且 RequireJS 在这些场景下也有用武之地。带着上面的这些注解，让我们开始吧。

### AMD（一种在浏览器中编写模块化 JavaScript 的格式）

AMD（异步模块定义，Asynchronous Module Definition）格式总体的目标是为现在的开发者提供一个可用的模块化 JavaScript 的解决方案。它诞生于 Dojo 在使用 XHR+eval 时的实践经验，其支持者希望未来的解决方案都可以免受由于过去方案的缺陷所带来的麻烦。

AMD 模块格式本身是一个关于如何定义模块的提案，在这种定义下模块和依赖项都能够[异步](http://dictionary.reference.com/browse/asynchronous)地进行加载。它有很多独特的优势，包括天生的异步及高度灵活等特性，这些特性能够解除常见的代码与模块标识间的那种紧密耦合。它被许多开发者所青睐，可以认为它是迈向 ES Harmony 中提出的[模块系统](http://wiki.ecmascript.org/doku.php?id=harmony:modules)的一块可靠基石。

AMD 最初是一份 CommonJS 列表中模块格式的规范草案，但因为没能达成完整的共识，格式的后续开发就被移到了 [amdjs](https://github.com/amdjs) 讨论组中。

目前它已经被包括 Dojo (1.7)、MooTools (2.0)、Firebug (1.8) 甚至 jQuery (1.7) 这样的项目所接纳。尽管我们时不时还是会遇到 CommonJS AMD 格式 这个说法，但由于不是所有 CJS 列表上的参与者都愿意支持它，我们最好还是称它为 AMD 或是异步模块支持。

> 注：曾经有一段时间，这个提案还被称为 Modules Transport/C，但是这个规范并不适合用来传输现有的 CJS 模块，而是适合用来定义模块，所以选择 AMD 这个命名约定就显得更为合理了。

#### 从模块说起

这里你需要先对下面这两个重要的概念有一定的了解：一个用来进行模块定义的 `define` 方法以及一个用来处理依赖项加载的 `require` 方法。define 根据如下的方法签名来定义具名或匿名的模块：

```js
define(
    module_id /*可选*/,
    [dependencies] /*可选*/,
    definition function /*用来初始化模块或对象的函数*/
);
```

正如你在注释中看到的，`module_id` 是一个可选参数，通常只在使用非 AMD 拼合工具时必须给出（不过也可能在一些极端情况下会很有用）。当这个参数被省略的时候，我们说这个模块是匿名的。

当使用匿名模块时，由于这样的模块符合 DRY（译注：Don't Repeat Yourself）的理念，从而让避免文件名或代码的重复变得轻而易举。因为这样的代码可移植性更高，可以被轻松地移到其它地方（或在文件系统中移动）使用，而不须要修改代码本身及其 ID。`module_id` 的作用就像是简单程序包中的文件路径，在有些程序包中甚至都没有被用到。只要使用一个能在例如 [r.js](https://github.com/jrburke/r.js/) 这样的 CommonJS 环境下运行的 AMD 优化器，开发者就可以在多个不同环境中运行相同的代码。

回到定义的方法签名，dependencies 参数代表了一组对所定义的模块来说必须的依赖项。第三个参数（'definition function'）是一个用来为你的模块执行初始化的函数。一个最简单的模块可以以如下方式定义：

##### 理解 AMD：define()

```js
// 这里的 module_id（myModule）仅作为示例使用

define('myModule',
    ['foo', 'bar'],
    // 模块定义函数
    // 依赖项（foo 和 bar）被映射为函数的参数
    function ( foo, bar ) {
        // 返回一个定义了模块导出接口的值
        // （也就是我们想要导出后进行调用的功能）

        // 在这里创建模块
        var myModule = {
            doStuff:function(){
                console.log('Yay! Stuff');
            }
        };

        return myModule;
});

// 另一个例子可以是...
define('myModule',
    ['math', 'graph'],
    function ( math, graph ) {

        // 请注意这是一个和 AMD 有些许不同的模式，但用几种不同的方式
        // 来定义模块也是可以的，因为语法在某些方面还是比较灵活的
        return {
            plot: function(x, y){
                return graph.drawPie(math.randomGrid(x,y));
            }
        };
});
```

另一方面，*require* 则主要用来在顶层 JavaScript 文件中或需要动态读取依赖时加载代码。用法的一个实例如下：

##### 理解 AMD：require()

```js
// 假设 'foo' 和 'bar' 是两个外部模块
// 在本例中，这两个模块被加载后的 'exports' 被当做两个参数传递到了回调函数中
// 所以可以像这样来访问他们

require(['foo', 'bar'], function ( foo, bar ) {
    // 这里写其余的代码
    foo.doSomething();
});
```

##### 动态加载的依赖项

```js
define(function ( require ) {
    var isReady = false, foobar;

    // 请注意在模块定义内部内联的 require 语句
    require(['foo', 'bar'], function (foo, bar) {
        isReady = true;
        foobar = foo() + bar();
    });

    // 我们仍可以返回一个模块
    return {
        isReady: isReady,
        foobar: foobar
    };
});
```

##### 理解 AMD：插件

下面的例子定义了一个 AMD 兼容的插件：

```js
// With AMD, it's possible to load in assets of almost any kind
// including text-files and HTML. This enables us to have template
// dependencies which can be used to skin components either on
// page-load or dynamically.
// 在 AMD 中，我们可以加载几乎任意类型的资源，包括文本文件以及 HTML。这让我们
// 同时能够在页面加载时以在及此后动态地得到可用于皮肤组件的模板依赖项。

define(['./templates', 'text!./template.md', 'css!./template.css'],
    function( templates, template ){
        console.log(templates);
        // 在这里做一些有趣的模板处理
});
```

> 注：尽管在上面的例子中在加载 CSS 依赖时已经包含了 css!，但我们要牢记这个方法需要注意的地方：无法真正确认何时 CSS 会被加载完毕。根据你构建代码方式的不同，可能会导致 CSS 作为一个依赖项加入到优化完的文件中，所以在这种情况下将 CSS 作为依赖项来加载需要倍加小心。

##### 使用 require.js 加载 AMD 模块

```js
require(['app/myModule'],
    function( myModule ){
        // 启动主模块，用来轮流加载其它模块
        var module = new myModule();
        module.doStuff();
});
```

##### 使用 curl.js 加载 AMD 模块

```js
curl(['app/myModule.js'],
    function( myModule ){
        // 启动主模块，用来轮流加载其它模块
        var module = new myModule();
        module.doStuff();
});
```

##### 包含需要延迟加载的依赖项的模块

```js
// 这可以兼容 jQuery 的 Deferred 实现、future.js（语法稍有不同）或多种其它实现
define(['lib/Deferred'], function( Deferred ){
    var defer = new Deferred();

    require(['lib/templates/?index.html','lib/data/?stats'],
        function( template, data ){
            defer.resolve({ template: template, data: data });
    });

    return defer.promise();
});
```

##### 为什么 AMD 对于编写模块化 JavaScript 是一个更好的选择？

- 为如何定义高灵活性的模块提供了一个清晰的方案。
- 相对目前我们很多人使用的全局命名空间加注入 `<script>` 标签的解决方案来说，要简洁得多。它有一个简洁的方式来声明独立的模块以及他们可能包含的依赖项。
- 模块定义都被封装了起来，帮我们避免了全局命名空间的污染。
- 比其它替代方案（例如 CommonJS，我们马上会讨论到）效果更好。没有跨域、本地或调试带来的问题，也不依赖于服务器端工具。大多数 AMD 加载器都支持在浏览器中加载模块，而不须要一个构建的过程。
- 提供了一个“传输”方法来用在单个文件中包含多个模块。其它例如 CommonJS 这样的方式都尚没有对传输格式达成共识。
- 当需要时可以进行延迟加载。

> **相关阅读**

> [The RequireJS Guide To AMD](http://requirejs.org/docs/whyamd.html)

> [What's the fastest way to load AMD modules?](http://unscriptable.com/index.php/2011/09/21/what-is-the-fastest-way-to-load-amd-modules/)

> [AMD vs. CJS, what's the better format?](http://unscriptable.com/index.php/2011/09/30/amd-versus-cjs-whats-the-best-format/)

> [AMD Is Better For The Web Than CommonJS Modules](http://blog.millermedeiros.com/2011/09/amd-is-better-for-the-web-than-commonjs-modules/)

> [The Future Is Modules Not Frameworks](http://unscriptable.com/code/Modules-Frameworks/)

> [AMD No Longer A CommonJS Specification](http://groups.google.com/group/commonjs/browse_thread/thread/96a0963bcb4ca78f/cf73db49ce267ce1?lnk=gst#)

> [On Inventing JavaScript Module Formats And Script Loaders](http://tagneto.blogspot.com/2011/04/on-inventing-js-module-formats-and.html)

> [The AMD Mailing List](http://groups.google.com/group/amd-implement)

#### Dojo 下的 AMD 模块

用 Dojo 来定义 AMD 兼容的模块是相当直截了当的。像前面说过的那样，每个模块依赖项被定义在数组中作为第一个参数，然后提供一个会在依赖项加载完毕后执行的回调（工厂）函数，例如：

```js
define(["dijit/Tooltip"], function( Tooltip ){
    //我们的 dijit 浮层提示现在就可以在本地进行调用了
    new Tooltip(...);
});
```

注意，这种模块天生的匿名特性使它能够被一个 Dojo 异步加载器、Require JS 或标准的 [dojo.require()](http://docs.dojocampus.org/dojo/require) 等你惯用的模块加载器所使用。

如果想了解模块引用的话，有一些有趣的小陷阱，在这里了解一下会很有帮助。虽然 AMD 主张的引用模块的方式是将它们声明在依赖列表中，与一组参数相对应，但 Dojo 1.6 的构建系统却不支持这种方式——这只能在完全遵循 AMD 的加载器中正常工作。比如：

```js
define(["dojo/cookie", "dijit/Tooltip"], function( cookie, Tooltip ){
    var cookieValue = cookie("cookieName");
    new Tree(...);
});
```

这相对嵌套的命名空间而言有很多优势，因为模块不再需要每次都直接用完整的命名空间来引用——我们须要的只是在依赖项中的 'dojo/cookie' 这种路径，一旦通过参数生成了别名，就可以用那个变量来引用了，这样也就无须在应用程序中反复地敲打出 'dojo.' 了

> 注：虽然 Dojo 1.6 对基于用户的 AMD 模块并没有提供正式的支持（也不支持异步加载），但是用一些其它的脚本加载器也可以让它们在 Dojo 下正常工作。目前，所有 Dojo 核心与 Dijit 模块都被转换成了 AMD 语法，并且很可能会在 1.7 到 2.0 版本之间从整体上提高对 AMD 的支持。

最后需要注意的小陷阱是，如果你希望继续使用 Dojo 的构建系统或是希望把旧的模块移植到新的 AMD 风格下，那么下面这种更为详细的版本会更易于移植。请注意 dojo 和 dijit 也都被作为依赖项引用：

```js
define(["dojo", "dijit", "dojo/cookie", "dijit/Tooltip"], function(dojo, dijit){
    var cookieValue = dojo.cookie("cookieName");
    new dijit.Tooltip(...);
});
```

#### AMD 模块设计模式（Dojo）

如果你关注过我之前任何有关设计模式好处的文章，你就会知道它们能非常有效地改进我们探索结构上解决方案的方式。[John Hann](http://twitter.com/unscriptable) 最近作了一个关于 AMD 模块设计模式的报告，内容涵盖了单例模式（Singleton）、装饰者模式（Decorator）、中介模式（Mediator）等等。我强烈推荐如果有机会的话去看看他的[幻灯片](http://unscriptable.com/code/AMD-module-patterns/)。

下面有几个这些模式的实例：

##### 装饰者（Decorator）模式：

```js
// mylib/UpdatableObservable：dojo/store/Observable 的一个装饰者
define(['dojo', 'dojo/store/Observable'], function ( dojo, Observable ) {
    return function UpdatableObservable ( store ) {
        var observable = dojo.isFunction(store.notify) ? store : new Observable(store);

        observable.updated = function( object ) {
            dojo.when(object, function ( itemOrArray ) {
                dojo.forEach( [].concat(itemOrArray), this.notify, this );
            });
        };

        return observable; // 让 `new` 成为可选的
    };
});


// 装饰者使用者
// mylib/UpdatableObservable 的一个使用者

define(['mylib/UpdatableObservable'], function ( makeUpdatable ) {
    var observable, updatable, someItem;
    // ... 获取或得到 `observable` 的代码

    // ... 让 observable store 也变得 updatable
    updatable = makeUpdatable(observable); // `new` is optional!

    // ... 之后，当一条 cometd 消息带着新的数据项到达时
    updatable.updated(updatedItem);
});
```

##### 适配器（Adapter）模式

```js
// 'mylib/Array' 将 `each` 函数适配为仿 jQuery 的接口:
define(['dojo/_base/lang', 'dojo/_base/array'], function (lang, array) {
    return lang.delegate(array, {
        each: function (arr, lambda) {
            array.forEach(arr, function (item, i) {
                lambda.call(item, i, item); // 就像 jQuery 的 each
            });
        }
    });
});

// 适配器使用者
// 'myapp/my-module':
define(['mylib/Array'], function ( array ) {
    array.each(['uno', 'dos', 'tres'], function (i, esp) {
        // 这里 `this` == item
    });
});
```

#### jQuery 下的 AMD 模块

##### 基础

不像 Dojo，jQuery 真就是只来自一个文件。然而因为其类库的本质是基于插件的，我们下面还是可以展示一下定义一个使用它的 AMD 模块是多么直截了当。

```js
define(['js/jquery.js','js/jquery.color.js','js/underscore.js'],
    function($, colorPlugin, _){
        // 这里我们传入了 jQuery、color 插件以及 Underscore
        // 我们在全局作用域中无法访问其中的任何一个，但我们可以轻易地在
        // 下面引用他们。

        // 伪随机生成一个颜色数组，选中打乱后数组中的第一项
        var shuffleColor = _.first(_.shuffle(['#666','#333','#111']));

        // 给页面中任意 class 带有 'item' 的元素用随机得到的颜色为
        // background-color 添加动画效果
        $('.item').animate({'backgroundColor': shuffleColor });

        return {};
        // 我们返回的东西可以被其它模块所使用
});
```

但是这个例子中有一些缺失的地方，也就是注册的概念。

##### 将 jQuery 注册为一个异步兼容的模块

jQuery 1.7 增加的一个关键特性，就是支持将 jQuery 注册为一个异步模块。有很多兼容的脚本加载器（包括 RequireJS 和 curl）都可以用一个异步模块格式来加载模块，这也就表示不需要太多 hack 就能让一切运行起来。

由于 jQuery 的流行，各种 AMD 加载器需要考虑到在同一个页面里加载这个库的多个版本，而本来理想中你并不希望几个不同的版本同时加载。加载器要么对这个问题作专门考虑，要么提示用户对于第三方脚本及其类库会有一些已知的问题。

1.7 版本带来的新特性是，它能够帮助避免在同一个页面内的其它第三方代码意外地加载了作者本不期望的某个版本的 jQuery。你不希望自己的内容被其它实例破坏掉，所以这是有益的。

其工作的原理是，所使用的脚本加载器通过指定一个属性，即 `define.amd.jQuery` 为 true，来标明自己可以支持多个 jQuery 版本。如果有兴趣了解特定的实现细节的话，我们可以将 jQuery 注册为一个具名模块，因为可能会有这样的风险，即它可能被与其它使用了 AMD 的 `define()` 方法的文件拼合在一起，而没有使用一个合适的、理解匿名 AMD 模块定义的拼合脚本。

具名的 AMD 为大多数用例提供了一个健壮又安全的保护层。

```js
// 让文档中存在多个 jQuery 的全局实例，以便测试 .noConflict()

var jQuery = this.jQuery || "jQuery",
$ = this.$ || "$",
originaljQuery = jQuery,
original$ = $,
amdDefined;

define(['jquery'] , function ($) {
    $('.items').css('background','green');
    return function () {};
});

// 易实现的声明支持的标志，会被 AMD 加载器所使用
define.amd = {
    jQuery: true
};
```

##### 更智能的 jQuery 插件

最近我在这里讨论了一些关于如何用通用模块定义（UMD，Universal Module Definition）来编写 jQuery 的思路和例子。UMD 定义那些既能在客户端又能在服务器端工作的模块，这样的模块同时也能和目前可用的主流脚本加载器一同工作。虽然这仍然是一个许多概念都还没最终确定的新领域，还是不妨看看标题为 AMD 与 CommonJS 的章节中的代码示例。如果你觉得我们哪里还可以改进，请告诉我。

##### 哪些脚本加载器和框架支持 AMD?

###### 浏览器端：

- RequireJS http://requirejs.org
- curl.js http://github.com/unscriptable/curl
- bdLoad http://bdframework.com/bdLoad
- Yabble http://github.com/jbrantly/yabble
- PINF http://github.com/pinf/loader-js
- (还有更多)

###### 服务器端

- RequireJS http://requirejs.org
- PINF http://github.com/pinf/loader-js

#### AMD 总结

上面的都只是关于 AMD 模块到底能有多有用的简单例子，但我期望它们能为理解 AMD 模块如何工作提供基础。

如果你知道许多我们可以看见的许多大型应用或公司正在将 AMD 模块作为其基础架构中一部分来使用，你可能会感兴趣。这包括 [IBM](http://www.ibm.com/) 与 [BBC iPlayer](http://www.bbc.co.uk/iplayer/)，这明显体现了企业级开发者们目前有多么真看待这种格式。

想了解更多那么多开发者选择在应用中使用 AMD 模块的理由，你可能会想看一看 James Burke 的 [这篇](http://tagneto.blogspot.com/2011/04/on-inventing-js-module-formats-and.html) 文章。

### CommonJS（为服务器端优化的模块格式）

[CommonJS](http://www.commonjs.org/)是一个志愿性质的工作组，它致力于设计、规划并标准化 JavaScript API。至今为止他们已经尝试着认可了[模块](http://www.commonjs.org/specs/modules/1.0/)标准以及[程序包](http://wiki.commonjs.org/wiki/Packages/1.0)标准。CommonJS 的模块提案为在服务器端声明模块指定了一个简单的 API。不像 AMD，它试图覆盖更宽泛的方面比如 IO、文件系统、promise 模式等等。

#### 入门

从结构的角度来看，一个 CJS 模块是一段可重用的 JavaScript，它导出一系列特定的对象给依赖它的代码调用——通常来说这样的模块外围没有函数包裹（所以你在这里的例子中不会看到 `define`）。

从高一点的层次来看，他们主要包含两个部分：一个名叫 `exports` 的自由变量，它包含模块希望提供给其它模块的对象；以及一个 `require` 函数，让模块用来导入其它模块的导出。

##### 理解 CJS：require() 与 exports

```js
// package/lib 是我们须要的一个依赖项
var lib = require('package/lib');

// 我们的模块的一些行为
function foo(){
    lib.log('hello world!');
}

// 把 foo 导出（暴露）给其它模块
exports.foo = foo;
```

##### exports 的基本用法

```js
// 定义我们希望暴露的更多行为
function foobar(){
    this.foo = function(){
        console.log('Hello foo');
    };

    this.bar = function(){
        console.log('Hello bar');
    };
}

// 把 foobar 暴露给其它模块
exports.foobar = foobar;


// 一个使用了 'foobar' 的应用

// 相对于使用文件与模块文件所在的同一目录路径获取模块

var foobar = require('./foobar').foobar,
    test   = new foobar();

test.bar(); // 'Hello bar'
```

##### 第一个 CJS 例子的 AMD 等价写法

```js
define(['package/lib'], function(lib){
    // 我们的模块的一些行为
    function foo(){
        lib.log('hello world!');
    }

    // 把 foo 导出（暴露）给其它模块
    return {
        foobar: foo
    };
});
```

##### 使用多个依赖项

###### app.js

```js
var modA = require('./foo');
var modB = require('./bar');

exports.app = function(){
    console.log('Im an application!');
}

exports.foo = function(){
    return modA.helloWorld();
}
```

###### bar.js

```js
var modA = require('./foo');
exports.name = 'bar';
```

###### foo.js

```js
require('./bar');
exports.helloWorld = function(){
    return 'Hello World!!';
}
```

##### 哪些加载器和框架支持 CJS?

###### 浏览器端：

- curl.js http://github.com/unscriptable/curl
- SproutCore 1.1 http://sproutcore.com
- PINF http://github.com/pinf/loader-js
- （还有更多）

###### 服务器端：

- Nodehttp://nodejs.org
- Narwhal https://github.com/tlrobinson/narwhal
- Perseverehttp://www.persvr.org/
- Wakandahttp://www.wakandasoft.com/

##### CJS 适用于浏览器吗？

有些开发者觉得 CommonJS 更适合于服务器端开发，这一定程度上说明了为什么在目前这个 Harmony 到来前的时代，对于哪个格式更适合用来作为事实标准存在某种程度的**分歧**。不利于 CJS 的论据包括：很多处理面向服务器端特性的 CommonJS API 根本无法用 JavaScript 在浏览器级别实现——比如 io、system 以及 js 就因为其天生的功能特性无法实现。

尽管这样，了解如何架构 CJS 模块还是很有用的，这样当我们在定义在所有地方都可能会用到的模块时，我们就能更好地体会它们是否合适了。在客户端与服务器端都有所应用的模块包括验证、转换和模板引擎。一些开发者选择使用哪个格式的方法是，当一个模块可以在服务器端环境中使用时选择 CJS，否则就选择 AMD。

因为 AMD 模块可以使用插件，也可以定义更细粒度的东西比如构造器与函数，这时用 AMD 就有意义了。CJS 模块只能定义对象。当你试图从中获取构造器时，处理这种模块就会变得冗长乏味了。

虽然在超出了本文的范围，但是你可能已经注意到在讨论 AMD 和 CMJ 的过程中我们提到了不同类型的 'require' 方法。

相似命名约定让人担忧的一点，当然是它会导致混乱。而且社区目前在用一个全局 require 函数带来的优缺点上尚有分歧。John Hann 对此的建议是，与其称它为 'require'，从而很可能无法成功让用户了解全局与内层 require 间的区别，把全局加载器方法重命名为别的东西反而会更有意义（例如这个类库的名字）。也就是这个原因使类似 curl.js 这样的加载器用 `curl()` 而非 `require`。

> 相关阅读

> [Demystifying CommonJS Modules](http://dailyjs.com/2010/10/18/modules/)

> [JavaScript Growing Up](http://www.slideshare.net/davidpadbury/javascript-growing-up)

> [The RequireJS Notes On CommonJS](http://requirejs.org/docs/commonjs.html)

> [Taking Baby Steps With Node.js And CommonJS - Creating Custom Modules](http://elegantcode.com/2011/02/04/taking-baby-steps-with-node-js-commonjs-and-creating-custom-modules/)

> [Asynchronous CommonJS Modules for the Browser](http://www.sitepen.com/blog/2010/07/16/asynchronous-commonjs-modules-for-the-browser-and-introducing-transporter/)

> [The CommonJS Mailing List](http://groups.google.com/group/commonjs)

### AMD 与 CommonJS（相互竞争，但同样有效的标准）

虽然本文相对 CJS 来说更侧重于 AMD，但事实上两者都是有效的格式而且都有用武之地。

AMD 采取了一种浏览器优先的方式来开发，选择了异步行为与简化的向后兼容性，但它完全没有文件 I/O 的概念。它支持对象、函数、构造器、字符串、JSON 以及其它许多类型的模块，运行在浏览器本地环境之中。它有着难以想象的灵活性。

CommonJS 则采用了服务器优先的策略，采取同步行为、没有 John Hann 所说的那种全局的累赘（译注：John Hann 说的应该是全局所有的模块都需要用 `define()` 包裹起来，而 CJS [不需要](http://unscriptable.com/code/AMD-vs-CommonJS/#34)）、并且着眼于适应未来的场景（在服务器上）。这么说的意思是，CJS 支持未包裹的模块，感觉上更接近 ES.next/Harmony 规范，把你从 AMD 要求的 `define()` 包裹函数中解放了出来。但 CJS 模块只支持将对象作为模块。

尽管可能还会有另一个模块格式的想法令人有些气馁，但是你还是可能会有兴趣看一些 AMD/CJS 混合模块和通用 AMD/CJS 模块相关工作的例子。

##### 基本 AMD 混合格式（John Hann）

```js
define( function (require, exports, module){
    var shuffler = require('lib/shuffle');

    exports.randomize = function( input ){
        return shuffler.shuffle(input);
    };
});
```

##### AMD/CommonJS 通用模块定义（变体 2，[UMDjs](https://github.com/umdjs/umd)）

```js
/**
 * 如果你需要做一些循环依赖或是需要兼容非 Node 的类
 * commonjs 环境，导出基于对象的版本。
 */
(function (define) {
    //'id' 是可选的，但如果这是一个流行的 web 类库而且
    //通常被用于非 AMD/Node 的环境下，还是推荐给出。然
    //而如果希望生成匿名模块，去掉下面的 'id'，并且去掉
    //define 兼容方案中使用的 id。
    define('id', function (require, exports) {
        //如果有兼容项，把它们加载进来
        var a = require('a');

        //给 exports 绑定属性。
        exports.name = value;
    });
}(typeof define === 'function' && define.amd ? define : function (id, factory) {
    if (typeof exports !== 'undefined') {
        //commonjs
        factory(require, exports);
    } else {
        //创建一个全局函数。仅在代码没有依赖项、或
        //是依赖项符合下面的调用模式时可用。
        factory(function(value) {
            return window[value];
        }, (window[id] = {}));
    }
}));
```

##### 可扩展的 UMD 插件（Thomas Davis 和我自己修改的变体）

###### core.js

```js
// 模块/插件 core
// 注：你在模块周围看到的包裹代码是用来让我们支持多个模块格式与规范
// 的，这须要把参数映射到某种特定格式所期望的样子。我们实际的模块功
// 能定义在下方，那里展示了一个具名模块和导出。
(function ( name, definition ){
    var theModule = definition(),
        // 这被认为是“安全”的:
        hasDefine = typeof define === 'function' && define.amd,
        // hasDefine = typeof define === 'function',
        hasExports = typeof module !== 'undefined' && module.exports;

    if ( hasDefine ){ // AMD 模块
        define(theModule);
    } else if ( hasExports ) { // Node.js 模块
        module.exports = theModule;
    } else { // 分配到常见的命名空间，或简单地分配到全局对象（window）
        (this.jQuery || this.ender || this.$ || this)[name] = theModule;
    }
})( 'core', function () {
    var module = this;
    module.plugins = [];
    module.highlightColor = "yellow";
    module.errorColor = "red";

    // 在这里定义 core 模块并返回公用 API

    // 这是 core 的方法 highlightAll() 和所有插件使用的 highlight 方法
    // 用来把元素高亮显示为不同颜色
    module.highlight = function(el,strColor){
        // 这个模块使用了 jQuery，但是老式的普通 JavaScript 或者 Dojo
        // 也可以很简单地使用。
        if(this.jQuery){
            jQuery(el).css('background', strColor);
        }
    };

    return {
        highlightAll:function(){
            module.highlight('div', module.highlightColor);
        }
    };
});
```

###### myExtension.js

```js
(function ( name, definition ) {
    var theModule = definition(),
        hasDefine = typeof define === 'function',
        hasExports = typeof module !== 'undefined' && module.exports;

    if ( hasDefine ) { // AMD 模块
        define(theModule);
    } else if ( hasExports ) { // Node.js 模块
        module.exports = theModule;
    } else {
	// 分配到常见的命名空间，或简单地分配到全局对象（window）
        // for 循环用来处理扁平文件/全局模块扩展名
        var obj = null;
        var namespaces = name.split(".");
        var scope = (this.jQuery || this.ender || this.$ || this);
        for (var i = 0; i < namespaces.length; i++) {
            var packageName = namespaces[i];
            if (obj && i == namespaces.length - 1) {
                obj[packageName] = theModule;
            } else if (typeof scope[packageName] === "undefined") {
                scope[packageName] = {};
            }
            obj = scope[packageName];
        }

    }
})('core.plugin', function () {
    // 在这里定义你的模块并返回公用 API
    // 这段代码可以轻易地与 core 代码相适应，来允许那些覆盖/扩展 core
    // 功能的方法，让你在需要时扩展 highlight 方法来做更多事。
    return {
        setGreen: function ( el ) {
            highlight(el, 'green');
        },
        setRed: function ( el ) {
            highlight(el, errorColor);
        }
    };
});
```

###### app.js

```js
$(function(){

    // 'core' 插件在本例中被暴露在了一个命名空间 core 下，我们
    // 先将它缓存起来
    var core = $.core;

    // 然后使用一些原生的 core 功能来用黄色高亮页面中所有的 div
    core.highlightAll();

    // 访问被载入 core 模块的 'plugin' 命名空间的插件（扩展）：

    // 把页面中的第一个 div 设为绿色背景。
    core.plugin.setGreen("div:first");
    // 这里我们通过一个在其之后加载的插件从底层使用 core 的 'highlight' 方法

    // 把最后一个 div 的背景色设为我们在 core 模块/插件中定义的
    // 'errorColor' 属性的颜色。如果你更仔细地查看代码，就会发现
    // 在 core 和其它插件间使用属性和方法是多么简单
    core.plugin.setRed('div:last');
});
```

### ES Harmony（未来的模块）

[TC39](http://www.ecma-international.org/memento/TC39.htm)——负责制定 ECMAScript 语法和语义以及其未来迭代的标准团体，是由一部分非常聪明的开发者组成的。其中的一些人（比如 [Alex Russell](http://www.ecma-international.org/memento/TC39.htm)）在近几年一直在密切关注 JavaScript 在大规模开发中的使用情况的演进，而且也敏感地意识到了需要有更好的语言特性来编写更加模块化的 JS。

基于这个原因，目前有提案已经提出了一系列令人振奋的对语言的补充，包括灵活的、可以同时在客户端与服务器端使用的 [模块](http://wiki.ecmascript.org/doku.php?id=harmony:modules)、一个[模块加载器](http://wiki.ecmascript.org/doku.php?id=harmony:module_loaders)以及[其它](http://wiki.ecmascript.org/doku.php?id=harmony:proposals)。在这个章节中，我将向你展示一些 ES.next 中语法的代码样例，让你能对即将到来的东西一睹为快。（译注：关于 ES.next 与 ES Harmony 的关系，可以参考[这篇](http://www.2ality.com/2011/06/ecmascript.html)文章。）

> 注：尽管 Harmony 仍然在提案阶段中，多亏了 Google 的 [Traceur](http://code.google.com/p/traceur-compiler/) 编译器，你已经可以（部分地）尝试 ES.next 引入的对编写模块化 JavaScript 进行原生支持的特性。想要立刻获取并运行 Traceur，请阅读这篇[入门](http://code.google.com/p/traceur-compiler/wiki/GettingStarted)指南。如果你有兴趣对这个项目了解更多的话，还有一个 JSConf 上相关的[演讲](http://traceur-compiler.googlecode.com/svn/branches/v0.10/presentation/index.html)也值得一看。

#### 包含导入与导出的模块

如果你已经读完了关于 AMD 与 CJS 模块的章节，你可能已经对模块依赖（导入）以及模块导出（或者说公用 API/我们允许其它模块使用的变量）的概念比较熟悉了。在 ES.next 中，这些概念被以一种更为精简的方式提出，用了一个关键字 `import` 来指定模块的依赖项。`export` 则和我们想象的没有多大差别，我认为很多开发者看了下面的代码就能立刻明白。

- **import**声明把某个模块的导出绑定为本地变量，并可以重命名来避免命名冲突。
- **export**声明声明了某个模块的本地绑定是外部可见的，这样其它模块就能够读取它们但却无法进行修改。有趣的是，模块可以导出子模块，却无法导出已经在别处定义过的模块。你同样可以给导出重命名来让它们不同于本地的名字。

```js
module staff{
    // 指定其它模块可以使用的（公用）导出
    export var baker = {
        bake: function( item ){
            console.log('Woo! I just baked ' + item);
        }
    };
}

module skills{
    export var specialty = "baking";
    export var experience = "5 years";
}

module cakeFactory{
    // 指定依赖项
    import baker from staff;

    // 通过通配符导入所有东西
    import * from skills;

    export var oven = {
        makeCupcake: function( toppings ){
            baker.bake('cupcake', toppings);
        },
        makeMuffin: function( mSize ){
            baker.bake('muffin', size);
        }
    };
}
```

#### 远程载入的模块

模块提案同样也适用于远程存放的模块（比如一个第三方 API 包裹器），使其简化了从外部位置载入模块的过程。这里是一段拉取我们上面定义的模块来使用的例子：

```js
module cakeFactory from 'http://addyosmani.com/factory/cakes.js';
cakeFactory.oven.makeCupcake('sprinkles');
cakeFactory.oven.makeMuffin('large');
```

#### 模块加载器 API

被提出的模块加载器为在高度受控的上下文中读取模块描述了一个动态的 API。加载器支持的方法签名有，用来加载模块的 `load( url, moduleInstance, error)`，以及 `createModule( object, globalModuleReferences)` 等等。下面是我们动态加载最开始定义的模块的例子。注意和上一个例子中我们从远程拉取一个模块不同，这里的模块加载器 API 更适合用于动态上下文。

```js
Loader.load('http://addyosmani.com/factory/cakes.js',
    function(cakeFactory){
        cakeFactory.oven.makeCupcake('chocolate');
});
```

#### 针对服务器的类 CommonJS 模块

对于面向服务器的开发者来说，在 ES.next 中提出的模块系统并非局限于对浏览器端模块的关注。通过下面的例子，你可以看见一个被提出用于服务器的类 CJS 模块：

```js
// io/File.js
export function open(path) { ... };
export function close(hnd) { ... };
```

```js
// compiler/LexicalHandler.js
module file from 'io/File';

import { open, close } from file;
export function scan(in) {
    try {
        var h = open(in) ...
    }
    finally { close(h) }
}
```

```js
module lexer from 'compiler/LexicalHandler';
module stdlib from '@std';

//... scan(cmdline[0]) ...
```

#### 带有构造器、Getter 与 Setter 的类

类的记号向来都是和语言纯正癖们间有争议的问题。我们目前一直沿用的是要么退回到 JavaScript 基于原型的天生特性，要么使用可让人使用类进行定义的、实质上在脱糖（译注：desugar，意为去掉语法糖，把代码转换为语法上更严密的形式，可参考[李松峰](http://weibo.com/lisf)老师的[这篇](http://www.cn-cuckoo.com/2008/08/20/how-to-translate-syntactic-sugar-251.html)文章）以后同样是原型行为的框架或抽象。

在 Harmony 中，类与构造器一同作为语言的一部分出现，（终于）有了一些真正的私有性。在下面的例子中，我引入了一些行内的注释来帮助你理解类是如何组织的，但是你可能会注意到这里缺少了“函数”这个词汇。这并非一个排印错误：TC39 一直以来都在有意识地努力减少我们对 `function` 关键字的到处滥用，希望这有助于帮助我们简化代码的编写。

```js
class Cake{
    // 我们可以用 'constructor' 关键字后面紧跟一个公有及私有声明
    // 的参数列表来定义一个类的构造器主体。
    constructor( name, toppings, price, cakeSize ){
        public name = name;
        public cakeSize = cakeSize;
        public toppings = toppings;
        private price = price;

    }

    // 作为 ES.next 对于减少不必要的到处使用 function 的努力的一部
    // 分，你会看到它在如同下面那样的使用场景中被抛弃了。在这里一个标
    // 识符后面紧跟一个参数列表和一个定义了新方法的主体。

    addTopping( topping ){
        public(this).toppings.push(topping);
    }

    // Getter 可以通过在标识符、方法名以及花括号主体前
    // 声明一个 get 来定义。
    get allToppings(){
        return public(this).toppings;
    }

    get qualifiesForDiscount(){
        return private(this).price > 5;
    }

    // 与 getter 类似，setter 也能通过在标识符前使用 'set'
    // 关键字来定义。
    set cakeSize( cSize ){
        if( cSize < 0 ){
            throw new Error('Cake must be a valid size -
            either small, medium or large');
        }

        public(this).cakeSize = cSize;
    }
}
```

#### ES Harmony 总结

如你所见，ES.next 带来了一些令人振奋的新东西。虽然 Traceur 可以在某种程度上用来在当前尝试一下这样的特性，但是要记住可能用 Harmony 来规划你的系统可能并不是个好主意（只是说目前还不是）。规范发生变化以及潜在的在跨浏览器层面的问题都会带来风险（比如 IE9 可能会要过较长的时间才会消亡），所以在标准最终确定及其覆盖率不成问题之前，你最好还是把注下在 AMD（用于浏览器内运行的模块）与 CJS（用于服务器）身上。

> **相关阅读**

> [A First Look At The Upcoming JavaScript Modules](http://www.2ality.com/2011/03/first-look-at-upcoming-javascript.html)

> [David Herman On JavaScript/ES.Next (Video)](http://blog.mozilla.com/dherman/2011/02/23/my-js-meetup-talk/)

> [ES Harmony Module Proposals](http://wiki.ecmascript.org/doku.php?id=harmony:modules)

> [ES Harmony Module Semantics/Structure Rationale](http://wiki.ecmascript.org/doku.php?id=harmony:modules_rationale)

> [ES Harmony Class Proposals](http://wiki.ecmascript.org/doku.php?id=harmony:classes)

### 结论与深入阅读（回顾）

在本文中我们审视了关于用现代的模块格式来编写模块化 JavaScript 的几个可选方案。这些格式相较于仅使用（传统的）模块模式有着许多优势，包括：让开发者们避免了为每个创建的模块建立全局变量、对静态与动态的依赖关系管理有着更好的支持、对脚本加载器有更高的兼容性、对服务器端模块也有着更好的（可选的）兼容性等等。

总之，我推荐你试试看今天建议的东西，因为这些格式提供了强大的功能以及灵活性，在基于可复用功能块构建应用程序时会很有帮助。

今天就到这里。如果你对于今天提到的话题还有更深入的问题，请随意来 [twitter](http://twitter.com/addyosmani) 骚扰我，我会尽力帮忙！

本文的技术审阅是通过 [Diigo](http://www.diigo.com/)（Google Chrome 版）进行的。Diigo 是一个让你能够在任意在线文档中加入评论与高亮的免费工具，如果你发现什么错误或是想建议什么扩展，请用 Diigo（或在 GitHub 上建个 [gist](http://gist.github.com/)），我会亲自做测试来处理任何你发过来的点子。
