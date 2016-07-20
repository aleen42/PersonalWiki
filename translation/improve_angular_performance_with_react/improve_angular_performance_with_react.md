## Improve Angular Performance with React - 通过 React 来提高 Angular 的性能 [**Back**](./../translation.md)

> * 原文链接 : [Improve Angular Performance with React](https://daveceddia.com/improve-angular-performance-with-react/?utm_campaign=0712ngreact)
* 原文作者 : [DAVE CEDDIA](https://daveceddia.com/timeline-for-learning-react/)
* 译者 : [aleen42](https://github.com/aleen42) 
* 校对者 : 暂无
* 状态 : 翻译中

![](./angular_plus_react.png)

如果你遇上了由大量的访问或毫无预测的重复渲染（re-render）所产生 Angular 性能问题，那么，ngReact 可以帮到您。

如果你已有一个 Angular 应用程序，但你又不想重写整个程序来尝试一下 React 的话，ngReact 在这方面也可以帮到您。

### 什么是 ngReact？

[ngReact](https://github.com/ngReact/ngReact) 是一个针对 React 的小型打包工具。（整个工具[大概只含有260行代码](https://github.com/ngReact/ngReact/blob/master/ngReact.js)）

有了它的话，你只需要创建好你的 Angular 程序。而 ngReact 在背后实际上会以 React 组件的形式渲染你的程序。它在传递给指令（directives）的属性上设置了监控对象（watches），并在组件改变的时候，重新渲染该些组件。

### 它用于何处？

如果你有大量或嵌套的 `ng-repeat` 属性，那么，程序可能会因为页面上监控对象的数量拖慢了执行速度。

同样地，如果你在心底里采用着“把一切构造成组件（指令）”的思想，也有可能会导致同样的情况发生。就好比，一个表格若充满由自定义指令集所构成的单元，那么将会大幅增加页面上的监控对象。