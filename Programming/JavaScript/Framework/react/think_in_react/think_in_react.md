## Think in React [Back](./../react.md)

Suppose that we have a requirements from our designer, and the design is shown as followed, what will we do with React?

![](thinking-in-react-mock.png)

### Step 1: Break the UI into a component hierarchy

Firstly, we are recommended that break the UIs into a component hierarchy.

![](thinking-in-react-components.png)

Then, we can name each component with our familiar naming style with this structure:

> FilterableProductTable(**orange**)
>> SearchBar(**blue**)

>> ProductTable(**green**)
>>> ProductCategoryRow(**turquoise**)

>>> ProductRow(**red**)

After that, the jsx should be written like the following structure:

```html
<html>
    <head>
        <!-- heads part -->
    </head>
    <body>
        <div id="content"></div>
    </body>
</html>
```

```js
var ProductRow = React.createClass({ /** ... */ });

var ProductCategoryRow = React.createClass({ /** ... */ });

var ProductTable = React.createClass({ /** ... */ });

var SearchBar = React.createClass({ /** ... */ });

var FilterableProductTable = React.createClass({ /** ... */ });

ReactDOM.render(
    <FilterableProductTable></FilterableProductTable>,
    document.getElementById('content')
);
```

### Step 2: Build a static version in React

```js
```