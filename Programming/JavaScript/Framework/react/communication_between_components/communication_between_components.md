## Communicate Between Components [Back](./../react.md)

- **parent-child**: just pass props
- **child-parent**: use `bind(this, arguments)`

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var handleClick = function (i, props) {
    console.log('clicked: ' + props.items[i]);
};

function List(props) {
    return (
        <div>
            {
                props
            }
        </div>
    );
}

ReactDOM.render(
    <List item={['Apple', 'Banana', 'Cranberry']} />,
    document.getElementById('content')
);
{%endace%}