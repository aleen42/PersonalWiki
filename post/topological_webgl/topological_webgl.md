## [轉載] HTML5的WebGL實現的3D和2D拓撲樹 [Back](./../post.md)

> - Author: Eric
- Origin: http://www.hightopo.com/blog/453.html
- Time: Feb, 24th, 2016

在[HT for Web](http://www.hightopo.com/)中2D和3D应用都支持树状结构数据的展示，展现效果各异，2D上的树状结构在展现层级关系明显，但是如果数据量大的话，看起来就没那么直观，找到指定的节点比较困难，而3D上的树状结构在展现上配合[HT for Web](http://www.hightopo.com/)的弹力布局组件会显得比较直观，一眼望去可以把整个树状结构数据看个大概，但是在弹力布局的作用下，其层次结构看得就不是那么清晰了。所以这时候结构清晰的[3D树](http://www.hightopo.com/)的需求就来了，那么这个3D树具体长成啥样呢，我们来一起目睹下~

![](./1.png)

要实现这样的效果，该从何下手呢？接下来我们就将这个问题拆解成若干个小问题来解决。

### 1. 创建一个树状结构

有了解过[HT for Web](http://www.hightopo.com/)的朋友，对树状结构数据的创建应该都不陌生，在这里我就不做深入的探讨了。树状结构数据的创建很简单，在这里为了让代码更简洁，我封装了三个方法来创建树状结构数据，具体代码如下：

```js
/**
 * 创建连线
 * @param {ht.DataModel} dataModel - 数据容器
 * @param {ht.Node} source - 起点
 * @param {ht.Node} target - 终点
 */
function createEdge(dataModel, source, target) {
    // 创建连线，链接父亲节点及孩子节点
    var edge = new ht.Edge();
    edge.setSource(source);
    edge.setTarget(target);
    dataModel.add(edge);
}

/**
 * 创建节点对象
 * @param {ht.DataModel} dataModel - 数据容器
 * @param {ht.Node} [parent] - 父亲节点
 * @returns {ht.Node} 节点对象
 */
function createNode(dataModel, parent) {
    var node = new ht.Node();
    if (parent) {
        // 设置父亲节点
        node.setParent(parent);

        createEdge(dataModel, parent, node);
    }
    // 添加到数据容器中
    dataModel.add(node);
    return node;
}

/**
 * 创建结构树
 * @param {ht.DataModel} dataModel - 数据容器
 * @param {ht.Node} parent - 父亲节点
 * @param {Number} level - 深度
 * @param {Array} count - 每层节点个数
 * @param {function(ht.Node, Number, Number)} callback - 回调函数(节点对象，节点对应的层级，节点在层级中的编号)
 */
function createTreeNodes(dataModel, parent, level, count, callback) {
    level--;
    var num = (typeof count === 'number' ? count : count[level]);

    while (num--) {
        var node = createNode(dataModel, parent);
        // 调用回调函数，用户可以在回调里面设置节点相关属性
        callback(node, level, num);
        if (level === 0) continue;
        // 递归调用创建孩子节点
        createTreeNodes(dataModel, node, level, count, callback);
    }
}
```
