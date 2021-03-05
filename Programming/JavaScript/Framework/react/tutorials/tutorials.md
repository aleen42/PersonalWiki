## Tutorials [Back](./../react.md)

React is all about modular and composable components. Here we will start to write a structure of components like following:

*Notice that: when creating components, you are recommended to follow following steps. Firstly, you should design the structure of your components. After that, use top-down view to build each components. It means that build components from parent nodes to children's. However, you should pay more attention to **scope problems**. There is a [example](./../think_in_react/think_in_react.md).*

> [CommentBox](#commentbox)
>> [CommentList](#commentlist---comment)
>>> Comment

>> [CommentForm](#commentform)

### CommentBox

First, we will build up a component for CommentBox with the following jsx:

```jsx
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
            )
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

```jsx
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

```jsx
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

```jsx
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

There is a way to do around it:

```jsx
var Comment = React.createClass({
    /** dangerouslySetInnerHTML must use __html to store what you want to set */
    rawMarkup: function () {
        var md = new Remarkable();
        return { __html: md.render(this.props.children.toString()) };
    },

    render: function () {
        return (
            <div className="comment">
                <h2 className="commentAuthor">{this.props.author}</h2>
                <span dangerouslySetInnerHTML={this.rawMarkup()}></span>
            </div>
        );
    }
});
```

### Data Model

As we can see, Comment elements within the CommentList can be extracted as a data model like following:

```jsx
var CommentList = React.createClass({
    render: function () {
        var commentNodes = this.props.data.map(function (comment) {
            return(
                <Comment author={comment.author} key={comment.id}>{comment.text}</Comment>
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

```jsx
var data = [
    { id: 1, author: 'aleen', text: 'comments for **aleen**'},
    { id: 2, author: 'alien', text: 'comments for **alien**'}
];
```

And of course, we should pass this array through CommentBox:

```jsx
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

If data is fetched from servers, and we can use `getInitialState` and `componentDidMount`:

```jsx
var CommentBox = React.createClass({
    /**
     * getInitialState() executes exactly once during the lifecycle of the component
     * and sets up the initial state of the component.
     */
    getInitialState: function () {
        return { data: [] };
    },

    /**
     * componentDidMount is a method called automatically by React
     * after a component is rendered for the first time.
     */
    componentDidMount: function () {
        /** ajax to get data from url */
        $.ajax({
            url: this.props.url,
            dataType: 'json',
            cache: false,
            success: function (data) {
                this.setState({ data: data });
            }.bind(this),
            error: function (xhr, status, err) {
                console.error(this.props.url, status, err.toString());
            }.bind(this)
        });
    },

    render: function () {
        return (
            <div className="comemntBox">
                <h1>Comments</h1>
                <CommentList data="{this.state.data}"></CommentList>
                <CommentForm></CommentForm>
            </div>
        );
    }
});

ReactDOM.render(
    <CommentBox url="/api/comments"></CommentBox>,
    document.getElementById('content')
);
```

With `componentDidMount`, we can automatically update data with other technology. For example we can use `setInterval`.

```jsx
var CommentBox = React.createClass({
    /** getInitialState function */
    /** ... */

    loadCommentsFromServer: function () {
        /** ajax to get data from url */
        $.ajax({
            url: this.props.url,
            dataType: 'JSON',
            cache: false,
            success: function (data) {
                this.setState({ data: data });
            }.bind(this),
            error: function (xhr, status, err) {
                console.error(this.props.url, status, err.toString());
            }.bind(this)
        });
    },

    componentDidMount: function () {
        this.loadCommentsFromServer();
        setInterval(this.loadCommentsFromServer, this.props.pollInterval);
    },

    /** render function */
    /** ... */
});

ReactDOM.render(
    <CommentBox url="/api/comments", pollInterval={2000}></CommentBox>,
    document.getElementById('content')
);
```

### CommentForm

CommentForm is the component used for sav comments, and users should provide their name and their text. Therefore:

```jsx
var CommentForm = React.createClass({
    render: function () {
        return (
            <form className="commentForm">
                <input type="text" placeholder="your name:" />
                <input type="text" placeholder="say something..." />
                <input type="submit" value="post" />
            </form>
        );
    }
});
```

With the traditional DOM, `input` elements are rendered and the browser manages the state (its rendered value). As a result, the state of the actual DOM will differ from that of the component. This is not ideal as the state of the view will differ from that of the component. **In React, components should always represent the state of the view and not only at the point of initialization**.

Hence, we will be using `this.state` to save the user's input as it is entered. We define an initial `state` with two properties `author` and `text` and set them to be empty strings. In our `<input>` elements, we set the `value` prop to reflect the state of the component and attach `onChange` handlers to them. These `<input>` elements with a value set are called **controlled components**. Read more about controlled components on the [Forms article](https://facebook.github.io/react/docs/forms.html#controlled-components).

```jsx
var CommentForm = React.createClass({
    getInitialState: function () {
        return {
            author: '',
            text: ''
        };
    },

    handleAuthorChange: function (e) {
        this.setState({ author: e.target.value });
    },

    handleTextChange: function (e) {
        this.setState({ text: e.target.value });
    },

    render: function () {
        return (
            <form className="commentForm">
                <input type="text" placeholder="your name:" value={this.state.author} onChange={this.handleAuthorChange} />
                <input type="text" placeholder="say something..." value={this.state.text} onChange={this.handleTextChange} />
                <input type="submit" value="post" />
            </form>
        );
    }
});
```

Now, we can just handle submit operation:

```jsx
var CommentForm = React.createClass({
    /** getInitialState */
    /** ... */

    /** handleAuthorChange function */
    /** ... */

    /** handleTextChange function */
    /** ... */

    handleSubmit: function () {
        /** Call preventDefault() on the event to prevent the browser's default action of submitting the form. */
        e.preventDefault();

        var author = this.state.author.trim();
        var text = this.state.text.trim();

        if (!text || !author) {
            return;
        }

        /** call api to store comments */
        this.props.onCommentSubmit({
            author: author,
            text: text
        });

        /** remember to reset states of elements */
        this.setState({
            author: '',
            text: ''
        });
    }

    render: function () {
        return (
            <form className="commentForm" onSubmit={this.handleSubmit}>
                <input type="text" placeholder="your name:" value={this.state.author} onChange={this.handleAuthorChange} />
                <input type="text" placeholder="say something..." value={this.state.text} onChange={this.handleTextChange} />
                <input type="submit" value="post" />
            </form>
        );
    }
});
```

And CommentBox should be:

```jsx
var CommentBox = React.createClass({
    /** loadCommentsFromServer function */
    /** ... */

    handleCommentSubmit: function (comment) {
        /** Optimization: show on the comments list without waiting request return */
        var comments = this.state.data;
        comment.id = Date.now();
        var newComments = comments.push(comment);
        this.setState({ data: newComments });

        $.ajax({
            url: this.props.url,
            dataType: 'json',
            type: 'POST',
            data: comment,
            success: function (data) {
                this.setState({ data: data });
            }.bind(this),
            error: function (xhr, status, err) {
                console.error(this.props.url, status, err.toString());
            }.bind(this)
        });
    },

    /** getInitialState function */
    /** ... */

    /** componentDidMount function */
    /** ... */

    render: function () {
        return (
            <div className="commentBox">
                <h1>Comments</h1>
                <CommentList data={this.state.data}></CommentList>
                <CommentForm onCommentSubmit={this.handleCommentSubmit}></CommentForm>
            </div>
        );
    }
});
```

### Whole JavaScript file

```jsx
/** Comment Component */
var Comment = React.createClass({
    /** dangerouslySetInnerHTML must use __html to store what you want to set */
    rawMarkup: function () {
        var md = new Remarkable();
        return { __html: md.render(this.props.children.toString()) };
    },

    render: function () {
        return (
            <div className="comment">
                <h2 className="commentAuthor">{this.props.author}</h2>
                <span dangerouslySetInnerHTML={this.rawMarkup()}></span>
            </div>
        );
    }
});

/** CommentList Component */
var CommentList = React.createClass({
    render: function () {
        var commentNodes = this.props.data.map(function (comment) {
            return(
                <Comment author={comment.author} key={comment.id}>{comment.text}</Comment>
            );
        });

        return (
            <div className="commentList">
                {commentNodes}
            </div>
        );
    }
});

/** CommentForm Component */
var CommentForm = React.createClass({
    getInitialState: function () {
        return {
            author: '',
            text: ''
        };
    },

    handleAuthorChange: function (e) {
        this.setState({ author: e.target.value });
    },

    handleTextChange: function (e) {
        this.setState({ text: e.target.value });
    },

    handleSubmit: function () {
        /** Call preventDefault() on the event to prevent the browser's default action of submitting the form. */
        e.preventDefault();

        var author = this.state.author.trim();
        var text = this.state.text.trim();

        if (!text || !author) {
            return;
        }

        /** call api to store comments */
        this.props.onCommentSubmit({
            author: author,
            text: text
        });

        /** remember to reset states of elements */
        this.setState({
            author: '',
            text: ''
        });
    },

    render: function () {
        return (
            <form className="commentForm" onSubmit={this.handleSubmit}>
                <input type="text" placeholder="your name:" value={this.state.author} onChange={this.handleAuthorChange} />
                <input type="text" placeholder="say something..." value={this.state.text} onChange={this.handleTextChange} />
                <input type="submit" value="post" />
            </form>
        );
    }
});

/** CommentBox Component */
var CommentBox = React.createClass({
    loadCommentsFromServer: function () {
        $.ajax({
            url: this.props.url,
            dataType: 'json',
            cache: false,
            success: function (data) {
                this.setState({ data: data });
            },
            error: function (xhr, status, err) {
                console.error(this.props.url, status, err.toString());
            }
        });
    },

    handleCommentSubmit: function (comment) {
        /** Optimization: show on the comments list without waiting request return */
        var comments = this.state.data;
        comment.id = Date.now();
        var newComments = comments.push(comment);
        this.setState({ data: newComments });

        $.ajax({
            url: this.props.url,
            dataType: 'json',
            type: 'POST',
            data: comment,
            success: function (data) {
                this.setState({ data: data });
            }.bind(this),
            error: function (xhr, status, err) {
                console.error(this.props.url, status, err.toString());
            }.bind(this)
        });
    },

    getInitialState: function () {
        return { data: [] };
    },

    componentDidMount: function () {
        this.loadCommentsFromServer();
        setInterval(this.loadCommentsFromServer, this.props.pollInterval);
    },

    render: function () {
        return (
            <div className="commentBox">
                <h1>Comments</h1>
                <CommentList data={this.state.data}></CommentList>
                <CommentForm onCommentSubmit={this.handleCommentSubmit}></CommentForm>
            </div>
        );
    }
});

/** render into the raw DOM */
ReactDOM.render(
    <CommentBox url="/api/comments" pollInterval={2000}></CommentBox>,
    document.getElementById('content')
);
```
