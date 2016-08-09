## DOM Event Listeners in a Component [Back](./../react.md)

> **Note:**

> This entry shows how to attach DOM events not provided by React. This is good for integrations with other libraries such as jQuery.

Try to resize the window:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var Box = React.createClass({
    getInitialState: function () {
        return { windowWidth: window.innerWidth };
    },
    
    handleSize: function (e) {
        this.setState({ windowWidth: window.innerWidth });
    },
    
    componentDidMount: function () {
        window.addEventListener('resize', this.handleResize);  
    },
    
    componentWillUnmount: function () {
        window.removeEventListener('resize', this.handleResize);
    },

    render: function () {
        return (
            <div>Current window width: {this.state.windowWidth}</div>
        );
    }
});

ReactDOM.render(
    <Box />,
    document.getElementById('content')
);
{%endace%}
