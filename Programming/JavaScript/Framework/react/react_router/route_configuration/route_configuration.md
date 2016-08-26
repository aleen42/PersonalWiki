## Route Configuration [Back](./../react_router.md)

A route configuration is basically a set of instructions (指令) to tell a router how to **match the URL**, and what code to run when it does.

For example, here we will render different components with React Router to match different URLs.

**URL**|**Components**
:-:|:---------
`/`|`App`
`/about`|`App -> About`
`/inbox`|`App -> Inbox`
`/inbox/messages/:id`|`App -> Inbox -> Message`

{%ace edit=false, lang='jsx', theme='tomorrow' %}
import React from 'react';
import ReactDOM from 'react-dom';
import { Router, Route, Link } from 'react-router';

class App extends React.Component {
    render() {
        return (
            <div>
                <h1>App</h1>
                <ul>
                    <li><Link to="/about">About</Link></li>
                    <li><Link to="/inbox">Inbox</Link></li>
                </ul>
                {this.props.children}
            </div>
        );
    }
}

class About extends React.Component {
    render() {
        return (
            <div>
                <h3>About</h3>
            </div>
        );
    }
}

class Inbox extends React.Component {
    render() {
        return (
            <div>
                <h3>Inbox</h3>
                {this.props.children || 'Welecome to your Inbox'}
            </div>
        );
    }
}

class Message extends React.Component {
    render() {
        return (
            <div>
                <h4>Message: {this.props.params.id}</h4>
            </div>
        );
    }
}

ReactDOM.render(
    <Router>
        <Route path="/" component={App}>
            <Route path="/" component={App}></Route>
        </Route>
    </Router>
);
{%endace%}