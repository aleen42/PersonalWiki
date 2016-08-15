## this.props.children undefined [Back](./../react.md)

You can't access the children of your component through `this.props.children`, which should only be the children being passed onto your component by the owner:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var MyComponent = React.createClass({
    componentDidMount: function () {
        console.log(this.props.children);   /** => undefined */
    },

    render: function () {
        return (
            <div>
                <span></span>
            </div>
        );
    }
});

ReactDOM.render(
    <MyComponent />,
    document.getElementById('content')
);
{%endace%}

Of course, if you want to access children of your own component, you can use `ref`:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var MyComponent = React.createClass({
    componentDidMount: function () {
        console.log(this.refs.child__elem);   /** => <span></span> */
    },

    render: function () {
        return (
            <div>
                <span ref="child__elem"></span>
            </div>
        );
    }
});

ReactDOM.render(
    <MyComponent />,
    document.getElementById('content')
);
{%endace%}
