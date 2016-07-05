## Components [Back](./../react.md)

React is all about modular and composable components. Here we will start to write a structure of components like following:

> CommentBox
>> CommentList
>>> Comment

>> CommentForm

### CommentBox

First, we will build up a component for CommentBox with the following jsx:

```js
var CommentBox = React.createClass({ 
    render: function () {
        return (
            <div className="commentBox">
                Hello, I am a comment box.
            </div>
        );
    }
});

ReactDOM.render(
    <CommentBox />,
    document.getElementById('content')
);
```

Then, this jsx should be converted into a plain js like:

```js
var CommentBox = React.createClass({
    render: function () {
        return (
            React.createElement(
                'div', 
                { 'className': 'commentBox' }, 
                'Hello, I am a comment box.'
            );
        );
    }
});

ReactDOM.render(
    React.createElement(CommentBox, null),
    document.getElementById('content')
);
```

As we can see, we have just passed a object to `React.createClass`, and the main attribute of this object is a function which named **render**.

`ReactDOM.render()` instantiates(例證) the root component, starts the framework, and injects the markup into a raw DOM element, provided as the second argument. Noice that, `ReactDOM.render` should only be called after the composite components have been defined.

### CommentList <- Comment

CommentList is a child node of CommentBox, so we should have this following:

```js
var CommentList = React.createClass({ 
    render: function () {
        return (
            <div className="commentList">
                <Comment author="aleen">comments for **aleen**</Comment>
                <Comment author="alien">comments for **alien**</Comment>
            </div>
        );
    }
});
```

For each Comment, we will use `this.props.author` to get attributes `author` of the corresponding elements and `this.props.children` as nested elements:

```js
var Comment = React.createClass({
    render: function () {
        return (
            <div className="comment">
                <h2 className="commentAuthor">{this.props.author}</h2>
                {this.props.children}
            </div>
        );
    }
});
```

Markdown is one of awesome tools in React, and we can use `Remarkable` to convert Markdown into raw HTML.

```js
var Comment = React.createClass({
    render: function () {
        var md = new Remarkable();
        return (
            <div className="comment">
                <h2 className="commentAuthor">{this.props.author}</h2>
                {md.render(this.props.children.toString())}
            </div>
        );
    }
});
```

But there's a problem! Our rendered comments look like this in the browser: "**`&lt;p&gt;This is &lt;strong&gt;another&lt;/strong&gt; comment&lt;/p&gt;**". We want those tags to actually render as HTML.

That's React protecting you from an [XSS attack](https://en.wikipedia.org/wiki/Cross-site_scripting).

### Data Model

As we can see, Comment elements within the CommentList can be extracted as a data model like following:

```js
var CommentList = React.createClass({ 
    render: function () {
        var commentNodes = this.props.data.map(function (comment) {
            return(
                <Comment author="{comment.author}" key="{comment.id}">{comment.text}</Comment>
            );
        });
        
        return (
            <div className="commentList">
                {commentNodes}
            </div>
        );
    }
});
```

Then, the data can be a array like following:

```js
var data = [
    { id: 1, author: 'aleen', text: 'comments for **aleen**'},
    { id: 2, author: 'alien', text: 'comments for **alien**'}
];
```

And of course, we should pass this array through CommentBox:

```js
var CommentBox = React.createClass({
    render: function () {
        return (
            <div className="comemntBox">
                <h1>Comments</h1>
                <CommentList data="{this.props.data}"></CommentList>
                <CommentForm></CommentForm>
            </div>
        );
    }
});

ReactDOM.render(
    <CommentBox data={data}></CommentBox>,
    document.getElementById('content')
);
```

### Fetch Data from servers

If data is fetched from servers, and we can use `getInitiateState` and `componentDidMount`:


