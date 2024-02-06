## Load Initial Data via AJAX [Back](./../react.md)

Fetch data in `componentDidMount`. When the response arrives, store the data in state, triggering a render to update your UI.

When fetching data asynchronously, use `componentWillUnmount` to cancel any outstanding requests before the component is unmounted.

```jsx
var UserGist = React.createClass({
    getInitialState: function () {
        return {
            userName: '',
            lastGistUrl: ''
        };
    },
    
    componentDidMount: function () {
        this.serverRequest = $.get(this.props.source, function (result) {
            var lastGist = result[0];
        
            this.setState({
                userName: lastGist.owner.login,
                lastGistUrl: lastGist.html_url
            });
        });  
    },
    
    componentWillUnmount: function () {
        this.serverRequest.abort();
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

ReactDOM.render(
    <UserGist source="https://api.github.com/users/octocat/gists" />,
    document.getElementById('content')
);
```