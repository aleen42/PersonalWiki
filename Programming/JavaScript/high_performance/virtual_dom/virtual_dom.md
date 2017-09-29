## Virtual DOM [Back](./../high_performance.md)

### 1. Description

**Virtual DOM** is a new concept brought to me when I was learning React, which is one of the famous modern Front-end framework, built by Facebook. Before learning that concept, I have known that browsers will create two internal data structures when it has completed downloading all resources needed for accessing a site. One is **a DOM tree** (Document Object Model), and the other is **a render tree**. Both of them are constructed as a tree, with almost different duties. (To learn more about them, we can read the session of my note, "[Repaints and Reflows](./../dom_scripting/dom_scripting.md#3-repaints-and-reflows)")

In React, Virtual DOM is an algorithm, which can compare two different DOM trees fast, and calculate the difference between them. With the result, it can easily change contents of a site without accessing all nodes in the DOM tree, which means that even though you are accessing a large complicated site, the application itself still can refresh certain part of the page easily. 

To take it simple, we can conclude the Virtual DOM algorithm in three following steps:

1. Create a structure with JavaScript objects to represent the DOM tree, when data has been changed.
2. Make a comparison between the new structure created in step one, and the old structure before data changed.
3. Apply the differences into the render DOM tree by only accessing nodes in need.

### 2. Learning about implementation

Recently I have met a project, named [**Picodom**](https://github.com/picodom/picodom). It has implemented the Virtual DOM algorithm within only around two hundred lines of code. Under the `src` folder, you can find that there are total three JavaScript files, among them two are significant.

- `h.js`: Used for implementing the creating process of the structure, described at step 1. (Virtual DOM Structure)
- `patch.js`: Used for implementing the comparison between two different Virtual DOM structures, described at step 2.

#### 2.1 Virtual DOM Structures

In Picodom, nodes of the Virtual DOM structure is described as an object with two main attributes:

- **tag**: the name of the tag
- **data**: the data within the node

With knowing that, we can easily grasped that why Picodom implemented such an object with the following function:

```js
/**
 * the constructor of nodes
 * @param tag the name of the tag
 * @param data the data within the node
 * @return constructed nodes
 */
export function h(tag, data) {
    var node
    var stack = []
    var children = []
    for (var i = arguments.length; i-- > 2;) {
        /** 
         * push all arguments into a stack array for later using,
         * except for first two arguments
         */
        stack[stack.length] = arguments[i]
    }
    /** loop all arguments in the stack */ 
    while (stack.length) {
        node = stack.pop()
        
        if (Array.isArray(node)) {
            /** flatten the argument when it is an array */
            for (var i = node.length; i--;) {
                stack[stack.length] = node[i]
            }
        } else if (node != null && node !== true && node !== false) {
            /** do not handle null, true, or false */
            if (typeof node === "number") {
                /** convert the argument into a string, when it is a number */
                node = node + ""
            }
            
            /** push the argument into the children array of current node */
            children[children.length] = node
        }
    }
    
    /** if tag name belongs to a string type, then return an object */
    return typeof tag === "string" ?
        {
            tag: tag,
            data: data || {},
            children: children
        } :
        /** else then, assume that the tag parameter is a custom construct function for creating different kinds of objects */
        tag(data, children)
}
```

#### 2.2 Comparison of data changes and applying patches
 
The most core thing of a Virtual DOM algorithm is its implementation of step 2 and step 3. In Picodom, we can learn how to implement such a process by checking the method, `patch()`.

```js
/**
 * createElementFrom: create a DOM element with the virtual dom node object
 * updateElementData: update DOM with data of current virtual dom node
 */

/**
* getKeyFrom: get the key of a virtual dom node object
* @param node
* @returns String
*/
function getKeyFrom(node) {
    if (node & (node = node.data)) {
        return node.key;
    }
}


/**
 * Implementation of comparison
 * @param parent    parent node
 * @param element   current node
 * @param oldNode   the virtual dom node with old data
 * @param node      the virtual dom node with new data
 * @return the node which has been updated
 */
export function patch(parent, element, oldNode, node) {
    if (oldNode == null) {
        /** if there is no any stored nodes with old data, then create one */
        element = parent.insertBefore(createElementFrom(node), element)
    } else if (node.tag && node.tag === oldNode.tag) {
        /** if tag name has not changed */
        /** update current node with new data */
        updateElementData(element, oldNode.data, node.data)

        var len = node.children.length
        var oldLen = oldNode.children.length
        var reusableChildren = {}
        var oldElements = []
        var newKeys = {}

        /** calculate which node can be reused */
        for (var i = 0; i < oldLen; i++) {
            var oldElement = element.childNodes[i]
            oldElements[i] = oldElement
            var oldChild = oldNode.children[i]
            
            /** get key from children node of the old virtual dom node */
            var oldKey = getKeyFrom(oldChild)
            if (null != oldKey) {
                reusableChildren[oldKey] = [oldElement, oldChild]
            }
        }
        
        /** i index for pointing to old virtual DOM nodes and old elements */
        var i = 0
        /** j index for pointing to new virtual DOM nodes and new elements */
        var j = 0
        while (j < len) {
            var oldElement = oldElements[i]
            var oldChild = oldNode.children[i]
            var newChild = node.children[j]
            var oldKey = getKeyFrom(oldChild)
            if (newKeys[oldKey]) {
                /** the old key of the virtual dom node with old data has been marked as reused */
                i++
                continue
            }
            var newKey = getKeyFrom(newChild)
            var reusableChild = reusableChildren[newKey] || []
            if (null == newKey) {
                /** this is a new child */
                if (null == oldKey) {
                    patch(element, oldElement, oldChild, newChild)
                    j++
                }
                i++
            } else {
                if (oldKey === newKey) {
                    /** reuse the child of same index */
                    patch(element, reusableChild[0], reusableChild[1], newChild)
                    i++
                } else if (reusableChild[0]) {
                    /** reuse the child of other index */
                    element.insertBefore(reusableChild[0], oldElement)
                    patch(element, reusableChild[0], reusableChild[1], newChild)
                } else {
                    /** create one virtual DOM node */
                    patch(element, oldElement, null, newChild)
                }
                j++
                
                /** mark the child as reused */
                newKeys[newKey] = newChild
            }
        }
        
        /** remove remaining children which have no specified key */
        while (i < oldLen) {
            var oldChild = oldNode.children[i]
            var oldKey = getKeyFrom(oldChild)
            if (null == oldKey) {
                removeElement(element, oldElements[i], oldChild)
            }
            i++
        }
        
        /** if the virtual DOM node of reusable children is no need by the new element, then remove it */
        for (var i in reusableChildren) {
            var reusableChild = reusableChildren[i]
            var reusableNode = reusableChild[1]
            if (!newKeys[reusableNode.data.key]) {
                removeElement(element, reusableChild[0], reusableNode)
            }
        }
    } else if (node !== oldNode) {
        /** if old virtual DOM node is not same as the new one, then create an element with such new one to replace the old one */
        var i = element
        parent.replaceChild((element = createElementFrom(node)), i)
    }
    
    return element
}
```

As we can see, `patch()` has been implemented as a recursive way to access all children defined under the Virtual DOM node. To see how it runs clear, I would like to use the following case as an example. Assume that there is a list with three list items: 

```html
<ul>
    <li>text</li>
    <li><a href="#">link</a></li>
</ul>
```

And then, construct the Virtual DOM tree with the method `h()`:

```js
h('ul', null,
    h('li', null, 'text'),
    h('li', null, h('a', null, { href: '#' }, 'link'))
);
```

With calling the snippet above, it will create a tree like this:

```js
{
    tag: 'ul',
    data: null,
    children: [
        { tag: 'li', data: null, children: ['text'] },
        { 
            tag: 'li',
            data: null,
            children: [
                { tag: 'a', data: null, children: [{ href: '#' }, 'link'] }
            ]
        },
    ]
}
```

Assume that there are three changes happened on the unordered list:

1. The first list item has changed its content with "new text".
2. The second list item has changed its anchor child with setting its href as "javascript: void(0);"
3. A new list item has been inserted into this unordered list.

```js
h('ul', null,
    h('li', null, 'text'),
    h('li', null, h('a', null, { href: 'javascript: void (0)' }, 'link')),
    h('li', null, '')
);
```

Then, the tree should become as followed:

```js
{
    tag: 'ul',
    data: null,
    children: [
        { tag: 'li', data: null, children: ['new text'] },
        { 
            tag: 'li',
            data: null,
            children: [
                { tag: 'a', data: null, children: [{ href: 'javascript: void (0);' }, 'link'] },
            ]
        },
        { tag: 'li', data: null, children: [''] }
    ]
}
```

To have a deep learning in how `patch()` works, how about calling the following code:

```js
patch(document.body, document.querySelector('ul'), oldTree, newTree);
```

When `patch()` has been called firstly, the following snippet all value of different variables:

```js
function patch(parent, element, oldNode, node) {
    if (oldNode == null) {
        /** does not enter this condition */
        /** ... */
    } else if (node.tag && node.tag === oldNode.tag) {
        /** node.tag: ul */
        /** oldNode.tag: ul */
        updateElementData(element, oldNode.data, node.data)

        var len = node.children.length /** => 3 */
        var oldLen = oldNode.children.length /** => 2 */
        var reusableChildren = {} /** => {} */
        var oldElements = [] /** => [] */
        var newKeys = {} /** => {} */

        for (var i = 0; i < oldLen; i++) {
            var oldElement = element.childNodes[i] /** => <li>text</li> */
            oldElements[i] = oldElement
            var oldChild = oldNode.children[i] /** => { tag: 'li', data: null, children: ['text'] } */
            
            var oldKey = getKeyFrom(oldChild) /** => null */
            if (null != oldKey) {
                reusableChildren[oldKey] = [oldElement, oldChild]
            }
        }
        
        /**
         * => reusableChildren : {} 
         */
        
        var i = 0
        var j = 0
        while (j < len) {
            /** => j: 0, len: 3 */
            var oldElement = oldElements[i] /** => <li>text</li> */
            var oldChild = oldNode.children[i] /** => { tag: 'li', data: null, children: ['text'] } */
            var newChild = node.children[j] /** => { tag: 'li', data: null, children: ['new text'] } */
            var oldKey = getKeyFrom(oldChild) /** => null */
            if (newKeys[oldKey]) {
                i++
                continue
            }
            var newKey = getKeyFrom(newChild) /** => null */
            var reusableChild = reusableChildren[newKey] || [] /** => [] */
            if (null == newKey) {
                if (null == oldKey) {
                    /**
                     * element: ul,
                     * oldElement: li,
                     * oldChild: { tag: 'li', data: null, children: ['text'] },
                     * newChild: { tag: 'li', data: null, children: ['new text'] }
                     */
                    patch(element, oldElement, oldChild, newChild)
                    j++ /** => 1 */
                }
                i++ /** => 1 */
            } else {
                /** does not enter this condition */
                /** ... */
            }
        }
        
        /** ... */
    } else if (node !== oldNode) {
        /** ... */
    }
    
    return element
}
```

With calling `patch()` at the second time, it is going to run patch between the first list item of the unordered list:

```js
function patch(parent, element, oldNode, node) {
    if (oldNode == null) {
        /** does not enter this condition */
        /** ... */
    } else if (node.tag && node.tag === oldNode.tag) {
        /** node.tag: li */
        /** oldNode.tag: li */
        updateElementData(element, oldNode.data, node.data)

        var len = node.children.length /** => 1 */
        var oldLen = oldNode.children.length /** => 1 */
        var reusableChildren = {} /** => {} */
        var oldElements = [] /** => [] */
        var newKeys = {} /** => {} */

        for (var i = 0; i < oldLen; i++) {
            var oldElement = element.childNodes[i] /** => text */
            oldElements[i] = oldElement
            var oldChild = oldNode.children[i] /** => text */
            
            var oldKey = getKeyFrom(oldChild) /** => null */
            if (null != oldKey) {
                reusableChildren[oldKey] = [oldElement, oldChild]
            }
        }
        
        /**
         * => reusableChildren : {} 
         */
        
        var i = 0
        var j = 0
        while (j < len) {
            /** => j: 0, len: 1 */
            var oldElement = oldElements[i] /** => "text" */
            var oldChild = oldNode.children[i] /** => "text" */
            var newChild = node.children[j] /** => "new text" */
            var oldKey = getKeyFrom(oldChild) /** => null */
            if (newKeys[oldKey]) {
                i++
                continue
            }
            var newKey = getKeyFrom(newChild) /** => null */
            var reusableChild = reusableChildren[newKey] || [] /** => [] */
            if (null == newKey) {
                if (null == oldKey) {
                    /**
                     * element: li,
                     * oldElement: "text",
                     * oldChild: "text",
                     * newChild: "new text"
                     */
                    patch(element, oldElement, oldChild, newChild)
                    j++ /** => 1 */
                }
                i++ /** => 1 */
            } else {
                /** does not enter this condition */
                /** ... */
            }
        }
        
        /** ... */
    } else if (node !== oldNode) {
        /** ... */
    }
    
    return element
}
```

Then, when calling `patch()` at the third time:

```js
function patch(parent, element, oldNode, node) {
    if (oldNode == null) {
        /** does not enter this condition */
        /** ... */
    } else if (node.tag && node.tag === oldNode.tag) {
        /** node.tag: null */
        /** does not enter this condition */
        /** ... */
    } else if (node !== oldNode) {
        /** if old virtual DOM node is not same as the new one, then create an element with such new one to replace the old one */
        var i = element /** => "text" */
        parent.replaceChild((element = createElementFrom(node)), i) /** i: "text", node: "new text", element: "new text" */
    }
    
    return element
}
```

As we can see, by calling `patch()` recursively, the algorithm has easily found out the differences of the first list item. By replacing it, the list item has been updated with new content: "new text". Awesome, right? In fact, it's not a hard work to understand such a recursive way by assuming a specific occasion. According to the theory of computer science, the algorithm has been designed as a process in which each calling of `patch()` has made a deep access to the tree, constructed with Virtual DOM Nodes. To put it simple, it is just a **DFS** (Depth-First-Search) way to access all nodes of a tree.  

### 3. Summary

By accessing each node of the tree, programs can calculate all differences and apply them to update old data with new one. This process is always called a **patch**, like what the method is defined. Sometimes you may think that it is a complicated way to implement a process in which DOM can just be updated only after it is changed, but what if you construct all nodes into a tree, it should be a easier way.
