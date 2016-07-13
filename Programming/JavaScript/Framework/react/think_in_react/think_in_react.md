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
var PRODUCTS = [
    {category: 'Sporting Goods', price: '$49.99', stocked: true, name: 'Football'},
    {category: 'Sporting Goods', price: '$9.99', stocked: true, name: 'Baseball'},
    {category: 'Sporting Goods', price: '$29.99', stocked: false, name: 'Basketball'},
    {category: 'Electronics', price: '$99.99', stocked: true, name: 'iPod Touch'},
    {category: 'Electronics', price: '$399.99', stocked: false, name: 'iPhone 5'},
    {category: 'Electronics', price: '$199.99', stocked: true, name: 'Nexus 7'}
];

var ProductRow = React.createClass({
    render: function () {
        var name = this.props.stocked ? this.props.name : <span style={{color: 'red'}}>{this.props.name}</span>;
        
        return (
            <tr>
                <td>{name}</td>
                <td>{this.props.price}</td>
            <tr/>
        );
    }
});

var ProductCategoryRow = React.createClass({
    render: function () {
        return (
            <tr><th>{this.props.category}</th></tr>
        );
    }
});

var ProductTable = React.createClass({
    render: function () {
        var rows = [];
        var lastCategory = null;
        this.props.products.forEach(function(product) {
            if (product.categoy !== lastCategory) {
                
            }
        });
    
        return (
            <table>
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Price</th>
                    </tr>
                </thead>
                <tbody>
                    
                </tbody>
            </table>
        );
    }
});
```