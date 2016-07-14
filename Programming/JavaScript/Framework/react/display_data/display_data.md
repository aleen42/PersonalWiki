## Displaying React [Back](./../react.md)

The most basic thing you can do with UI is displaying some data. React makes it easy to display data and automatically keeps it up-to-date when the data changes.

### Get Started

Firstly, we'll create a simple `hello-react.html`:

```js
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello React</title>
    <script src="https://fb.me/react-15.2.1.js"></script>
    <script src="https://fb.me/react-dom-15.2.1.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/babel-core/5.8.34/browser.min.js"></script>
  </head>
  <body>
    <div id="example"></div>
    <script type="text/babel">

      // ** Your code goes here! **

    </script>
  </body>
</html>
```

To replace the comments above with the following jsx:

```js
var Hello = React.createClass({
    render: function () {
        return (
            <p>
                Hello, <input type="text" placeholder="Your name here" />
                It's {this.props.date.toTimeString()}
            </p>
        );
    }
});

setInterval(function () {
    ReactDOM.render(
        <Hello date={new Date()} />,
        document.getElementById('example')
    )
}, 500);
```

### Reactive Updates

If you run the example above, you will find that UI only updates time string, without changing the input elements even though you have input something. That's because React has figured it out and manage this behaviours.

Rect does not manipulate the DOM unless it needs to. **It uses a fast, internal mock DOM to perform diffs and computes the most efficient DOM mutation for you.**



