## Load Initial Data via AJAX [Back](./../react.md)

Fetch data in `componentDidMount`. When the response arrives, store the data in state, triggering a render to update your UI.

When fetching data asynchronously, use `componentWillUnmount` to cancel any outstanding requests before the component is unmounted.

{%ace edit=false, lang='jsx', theme='tomorrow'%}
var UserGist = React.createClass({
    getInitialState: function () {
        return {
            userName: '',
            lastGistUrl: ''
        };
    },
    
    render: function () {
        return (
            <div>
                {this.state.userName}'s last gist is
                <a href="{this.state.lastGistUrl}" target="_blank">here</a>
            </div>
        );
    }
});
{%endace%}