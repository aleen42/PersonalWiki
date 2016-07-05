## Components [Back](./../react.md)

React is all about modular and composable components. Here we will start to write a structure of components like following:

> CommentBox
>> CommentList
>>> Comment

>> CommentForm

First, we will build up a component for CommonBox with the following jsx:

```js
var CommonBox = React.createClass({ 
    render: function () {
        return (
            <div class="CommonBox">
                
            </div>
        );
    }
});
```