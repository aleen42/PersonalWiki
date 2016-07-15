## Multiple Components [Back](./../react.md)

The aim of building modular components is to reuse, to separate different concerns like divide and conquer.

Let's create a simple Avatar component which shows a Facebook page picture and name using the Facebook Graph API.

```js
var Avatar = React.createClass({
    render: function () {
        return (
            <div>
                <PagePic pagename={this.props.pagename} />
                <PageLink pagename={this.props.pagename} />
            </div>
        );
    }
});

var PagePic = React.createClass({
    render: function() {
        return (
            <img src={'https://graph.facebook.com/' + this.props.pagename + '/picture'} />
        );
    }
});

var PageLink = React.createClass({
    render: function() {
        return (
            <a href={'https://www.facebook.com/' + this.props.pagename}>
                {this.props.pagename}
            </a>
        );
    }
});

ReactDOM.render(
    <Avatar pagename="Engineering" />,
    document.getElementById('example')
);
```

### Ownership

In React, **an owner is the component that sets the `prop` of other components**.
