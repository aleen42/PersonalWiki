## Props in getInitialState Is an Anti-Pattern [Back](./../react.md)

Using props to generate state in `getInitialState` often leads to duplication of "source of truth", i.e. where the real data is. This is because `getInitialState` is only invoked when the component is first created.

**Bad example:**

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var MessageBox = React.createClass({
    getInitialState: function () {
        return { nameWithQualifier: 'Mr.' + this.props.name };
    },
    
    render: function () {
        return (
            <div>
                {this.state.nameWithQualifier}
            </div>
        );
    }
});

ReactDOM.render(
    <MessageBox name="aleen42" />,
    document.getElementById('content')
);
{%endace%}

**Better:**

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var MessageBox = React.createClass({
    render: function () {
        return (
            <div>
                {'Mr.' + this.props.name}
            </div>
        );
    }
});
{%endace%}
