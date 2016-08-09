## Type of the Children props [Back](./../react.md)

Usually, a component's children (`this.props.children`) is an array of components:

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var GenericWrapper = React.createClass({
    componentDidMount: function() {
        console.log(Array.isArray(this.props.children)); // => true
    },

    render: function() {
        return <div />;
    }
});

ReactDOM.render(
    <GenericWrapper><span/><span/><span/></GenericWrapper>,
    document.getElementById('content')
);
{%endace%}