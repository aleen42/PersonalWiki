## Components [Back](./../react.md)

React is all about modular and composable components. Here we will start to write a structure of components like following:

> CommentBox
>> CommentList
>>> Comment

>> CommentForm

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
                'Hello, I am a comment box'
            );
        );
    }
});

ReactDOM.render(
    React.createElement(CommentBox, null),
    document.getElementById('content')
);
```