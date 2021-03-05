## Introduction [Back](./../react_router.md)

Think about a case that without refreshing, how can we keep the URL in sync with contents in a page?

React Router is used to help adding new screens and flows to our application, while keeping the URL in sync with what's being displayed on the page.

### Without React Router

If we don't use React Router, we are supposed to complete this requirement with `window.location.hash`.

```jsx
import React from 'react';
import ReactDOM from 'react-dom';

const About = React.createClass({/*...*/});
const Inbox = React.createClass({/*...*/});
const Home = React.createClass({/*...*/});

export class App extends React.Component {
    constructor(props) {
        super(props);
        
        this.state = { route: window.location.hash.substr(1) };
    }
    
    componentDidMount() {
        window.addEventListener('hashchange', () => {
            this.setState({
                route: window.location.hash.substr(1)
            });
        });
    }
    
    render() {
        let Child;
        
        switch (this.state.route) {
            case '/about':
                Child = About;
                break;
            case '/inbox':
                Child = Inbox;
                break;
            default:
                Child = Home;
                break;
        }
        
        return (
            <div>
                <h1>App</h1>
                <ul>
                    <li><a href="#/about">About</a></li>
                    <li><a href="#/inbox">Inbox</a></li>
                </ul>
                <Child />
            </div>
        );
    }
}

ReactDOM.render(
    <App />,
    document.getElementById('content')
);
```

Imagine now that `Inbox` component has some neted UI at different URLs, maybe something like this master detail view:

```
path: /inbox/messages/1234

+---------+------------+------------------------+
| About   |    Inbox   |                        |
+---------+            +------------------------+
| Compose    Reply    Reply All    Archive      |
+-----------------------------------------------+
|Movie tomorrow|                                |
+--------------+   Subject: TPS Report          |
|TPS Report        From:    boss@big.co         |
+--------------+                                |
|New Pull Reque|   So ...                       |
+--------------+                                |
|...           |                                |
+--------------+--------------------------------+
```

And maybe a stats page when not viewing a message:

```
path: /inbox

+---------+------------+------------------------+
| About   |    Inbox   |                        |
+---------+            +------------------------+
| Compose    Reply    Reply All    Archive      |
+-----------------------------------------------+
|Movie tomorrow|                                |
+--------------+   10 Unread Messages           |
|TPS Report    |   22 drafts                    |
+--------------+                                |
|New Pull Reque|                                |
+--------------+                                |
|...           |                                |
+--------------+--------------------------------+
```

That's why we use React Router to help us parsing URL in a smart way.

### With React Router

```jsx
import React from 'react';
import ReactDOM from 'react-dom';

/** First we import some modules... */
import { Router, Route, IndexRoute, Link, hashHistory } from 'react-router';

export class App extends React.Component {
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

/**
 * Finally, we render a <Router> with some <Route>s.
 * It does all the fancy routing stuff for us.
 */
ReactDOM.render(
    <Router history={hashHistory}>
        <Route path="/" component={App}>
            <IndexRoute component={Home}></IndexRoute>
            <Route path="about" component={About}></Route>
            <Route path="inbox" component={Inbox}></Route>
        </Route>
    </Router>,
    document.getElementById('content')
);
```
