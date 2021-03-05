## ES3-Compatible Webpack Plugin [Back](./../webpack.md)

Sometimes, we may need to write a plugin to do something when building with Webpack, like optimizing chunks of code, or replacing code during compilation.

To learn about how to write a plugin, there was an example. Recently, I have met a case when I needed to write a plugin to support "keywords definition" and "trailing commas in arrays" in the developing environment for IE8. All I knew was that, if we coded with following snippets, and built them with Webpack without any uglifying or optimization, they should break down under IE8 with compatible problems:

```js
/** keyword definiton */
var obj = {
    extends: function () {},
};

obj.extends();
```

```js
/** trailing commas in arrays */
var arr = [
    'webpack',
    'patch',
];
```

### 1. Why

Why not using `Webpack.optmize.UglifyJSPlugin`? Too slow for me, especially when I am developing and debugging code. Overheads of uglifying after each modification should be a "Tar Pit" for me. You may say why not using `es3ify`? The answer is that I may prefer to learn to solve this situation myself (Actually I did not know this library before until I have completed my own one, :joy:).

### 2. Parsing

Source stream is the only thing we can get during building, and if we want to escape keyword definitions or remove trailing commas in arrays, we should need to know the expression of a JavaScript file. At that moment, I thought about using **Regular Expression** to process files, but it was hard to satisfy as what we face with is a **Language**. What we need is a more complicated compiler, which can help us to construct a tree-like structure, named **Abstract Syntax Tree** (AST) to analyse, including lexical, syntactic, and even semantic analysis. In brief, Regular expression is too weak to be our choice to process JavaScript.

After some researches, there were some parsing libraries like `jstransform`, `UglifyJS`, etc. `es3ify` has used `jstransform` to parse, while I chose `UglifyJS`. Why? Perhaps I was not really a member of Facebook, where `jstransform` was produced.

#### 2.1 AST

> AST_Node

**AST** is a tree-like structure defined inside `UglifyJS` to represent for syntax of JavaScript. The basic element is named with "node", defined as `AST_Node`. As the official document described, we should know that each `AST_Node` has two basic attributes: `start` and `end`, which are both used to represent the position of each `AST_Node`. This feature can be actually used by us to extract what we want from the source stream.

Certainly, the first step we should do is to know how to initialize the library and construct the AST. The following snippet has shown us how:

```js
const UglifyJS = require('uglify-js');

const AST = UglifyJS.parse(source);
```

#### 2.2 Object Properties and Dotted Access

Then, because we try to convert some illegal expression in JavaScript, we may have to understand two another types of AST nodes, `AST_ObjectProperty` and `AST_Dot`.

>> ...
>>> AST_ObjectProperty

>> ...
>>> AST_PropAccess
>>>> AST_Dot

From the literal value, we can easily grasp that `AST_ObjectProperty` is mainly used to stand for literal object properties like the `extends` word in `{ extends: '1' }`, while `AST_Dot` stands for dotted access expression, like `obj.extends`.

Since that we know these two kinds of AST nodes, we can start to walk through the whole AST tree right now, and handle all expressions we concern like this:

```js
AST.walk(new UglifyJS.TreeWalker(node => {
    if (node instanceof UglifyJS.AST_ObjectProperty) {
        /** all proerties defined in the file */
    } else if (node instanceof UglifyJS.AST_Dot) {
        /** all dotted access expressions in the file */
    }
}));
```

And as mentioned above, we can extract the word with position properties: `start` and `end` inside the condition. Take object properties as an example, the word `extends` can be extracted by `start`, in which `start.pos` has represented the start position of `extends` in the whole source stream, while `start.endpos` has specified the end one:

```js
snippets.push({
    type: 'object_property',
    key: node.key,
    start: node.start.pos,
    end: node.start.endpos,
});
```

When it comes to dotted access expressions, `end` object has the same meaning except the case of expressions wrapped with parentheses like `(obj.extends)`. In such case, `end` has been marked within a node which is also defined as `AST_Token`, standing for right parentheses. That's why `end.pos` and `end.endpos` are just the interval of ")". To workaround this special situation, we can easily extract like this:

```js
/**
 * node.start.pos
 *  \
 *   \       node.end.endpos
 *    \      /
 * if (a.b.c),
 * then both `start` and `end` are `AST_Token` representing parentheses
 */
const wholeString = source.substring(node.start.pos, node.end.endpos);
const start = node.start.pos + wholeString.lastIndexOf(snippetObject.key);
const end = start + node.key.length;

snippets.push({
    type: 'dot_access',
    key: node.key,
    start,
    end,
});
```

#### 2.3 Trailing Commas in Arrays

To handle the other illegal expression, we can use the defined node, `AST_Array`.

>> ...
>>> AST_Array

`AST_Array` is another class defined for arrays, which can be used to extracting trailing commas. How? Just check the interval between its last child (`elements[elements.length - 1].end.endpos`) and the end of this array (`end.endpos`).

```js
if (node instanceof UglifyJS.AST_Array
    && node.elements.length
    && source.substring(
        node.elements[node.elements.length - 1].end.endpos,
        node.end.endpos
    ).indexOf(',') > -1
) {
    /** trailing commas */
}
```

Oops, we have forgotten that the comma also can be placed in a comment. Therefore, we should limit the range of searching when there is parsed comments:

```js
if (node instanceof UglifyJS.AST_Array
    && node.elements.length
    && source.substring(
        node.elements[node.elements.length - 1].end.endpos,
        node.end.endpos
    ).indexOf(',') > -1
) {
    if (!node.end.comments_before.length) {
        /** trailing commas "[1, 2,]"*/
    } else {
        if (source.substring(
            node.elements[node.elements.length - 1].end.endpos,
            node.end.comments_before[0].pos
        ).indexOf(',') > -1) {
            /** trailing commas "[1, 2, // comments]" */
        } else if (source.substring(
            node.end.comments_before[0].endpos,
            node.end.endpos
        ).indexOf(',') > -1) {
            /**
            * trailing commas
            * "[
            *       1,
            *       2 // comments
            *       ,
            *  ]"
            */
        }
    }
}
```

### 3. Plugin

So far, the main function has been implemented, and what needed to do is only to integrate it into Webpack as a plugin. If you want to learn how to do this, more details can be checked into the published plugin, [**es3-compatible-webpack-plugin**](https://github.com/aleen42/es3-compatible-webpack-plugin).
