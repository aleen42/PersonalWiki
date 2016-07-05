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
            <div class="commentBox">
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
var CommentBox = React.createClass({ 
    render: function () {
        return (
            <div class="commentBox">
                <h1>Comments</h1>
                <CommentList></CommentList>
            </div>
        );
    }
});

ReactDOM.render(
    <CommentBox />,
    document.getElementById('content')
);
```