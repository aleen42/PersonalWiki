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

```jsx
<html>
    <head>
        <!-- heads part -->
    </head>
    <body>
        <div id="content"></div>
    </body>
</html>
```

```jsx
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

```jsx
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
        var name = this.props.product.stocked ? this.props.product.name : <span style={ { color: 'red' } }>{this.props.product.name}</span>;
        
        return (
            <tr>
                <td>{name}</td>
                <td>{this.props.product.price}</td>
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
                rows.push(<ProductCategoryRow category={product.category} key={product.category}></ProductCategoryRow>);
            }
            
            rows.push(<ProductRow product={product} key={product.name}></ProductRow>);
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
                    {rows}
                </tbody>
            </table>
        );
    }
});

var SearchBar = React.createClass({
    render： function () {
        return (
            <form>
                <input type="text" placeholder="Search..." />
                <p>
                    <input type="checkbox" id="show-product" /> <label htmlFor="show-produt">Only show products in stock</label> 
                </p>
            </form>
        );
    }
});

var FilterableProductTable = React.createClass({
    render: function () {
        return (
            <div>
                <SearchBar />
                <ProductTable products={this.props.products}/>
            </div>
        );
    }
});

ReactDOM.render(
    <FilterableProductTable products={PRODUCTS} />,
    document.getElementById('container')
);
```

It's best to decouple these processes because building a static version requires a lot of typing and no thinking, and adding interactivity requires a lot of thinking and not a lot of typing.

If you're familiar with the concept of state, don't use state at all to build this static version. State is reserved only for interactivity, that is, data that changes over time.

In simpler examples, it's usually easier to go top-down, and on larger projects, it's easier to go bottom-up and write tests as you build.

#### A brief interlude : props vs state

There are two types of "model" data in React: props and state. It's important to understand the distinction between the two; skim [the official React docs](https://facebook.github.io/react/docs/interactivity-and-dynamic-uis.html) if you aren't sure what the difference is.

### Step3: Identify the minimal(but complete) representation of UI state

To make your UI interactive, you need to be able to trigger changes to your underlying data model. React makes this easy with **state**.

The key here is DRY: *Don't Repeat Yourself*.

Think of all of the pieces of data in our example application. We have:

- The original list of products
- The search text the user has entered
- The value of the checkbox
- The filtered list of products

Simply ask three questions about each piece of data:

1. Is it **passed in from a parent via props**? If so, it probably isn't state.
2. Does it **remain unchanged over time**? If so, it probably isn't state.
3. Can you **compute it based on any other state or props** in your component? If so, it isn't state.

The original list of products is passed in as props, so that's not state. The search text and the checkbox seem to be state since they change over time and can't be computed from anything .And finally, the filtered list of products isn't state because it can be computed by combining the original list of products with the search text and value of the checkbox.

So finally, our state is:

- The search text the user has entered
- The value of the checkbox

### Step 4: Identify where your state should live

Remember: React is all about one-way data flow down the component hierarchy. It may not be immediately clear which component should own what state. **This is often the most challenging part for newcomers to understand**, so follow these steps to figure it out:

For each piece of state in your application:

- Identify every component that renders something based on that state.
- Find a common owner component (a single component above all the components that need the state in the hierarchy).
- Either the common owner or another component higher up in the hierarchy should own the state.
- If you can't find a component where it makes sense to own the state, create a new component simply for holding the state and add it somewhere in the hierarchy above the common owner component.

Following this strategy, we can find that both SearchBar and ProductTable need the state. And their common components is FilterableProductTable. Therefore, the state should live in **FilterableProductTable**.

```jsx
/** use filterText and isStockOnly to filter data */
var ProductTable = React.createClass({
    render: function () {
        var rows = [];
        var lastCategory = null;
        this.props.products.forEach(function(product) {
            /** filter text and filter stock */
            if (product.name.indexOf(this.props.filterText) === -1 || (this.props.isStockOnly && !product.stocked)) {
                return;
            }
        
            if (product.categoy !== lastCategory) {
                rows.push(<ProductCategoryRow category={product.category} key={product.category}></ProductCategoryRow>);
            }
            
            rows.push(<ProductRow product={product} key={product.name}></ProductRow>);
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
                    {rows}
                </tbody>
            </table>
        );
    }
});

/** add filterText and isStockOnly to the corresponding input elements */
var SearchBar = React.createClass({
    render： function () {
        return (
            <form>
                <input type="text" placeholder="Search..." value={this.props.filterText} />
                <p>
                    <input type="checkbox" id="show-product" checked={this.props.isStockOnly} /> <label htmlFor="show-produt">Only show products in stock</label> 
                </p>
            </form>
        );
    }
});

var FilterableProductTable = React.createClass({
    getInitialState: function () {
        return {
            filterText: '',
            isStockOnly: false
        };
    },

    render: function () {
        return (
            <div>
                <SearchBar filterText={this.state.filterText} isStockOnly={this.state.isStockOnly} />
                <ProductTable products={this.props.products} filterText={this.state.filterText} isStockOnly={this.state.isStockOnly} />
            </div>
        );
    }
});
```

### Step5: Add inverse data flow

There should be a method to handle events of changements of both the text and the checkbox.

Therefore, we should add a handle event method for FilterableProductTable to setState, and pass this method to SearchBar via prop.

```jsx
/** call parent method */
var SearchBar = React.createClass({
    handleChange: function() {
        this.props.onUserInput(this.refs.filterTextInput.value, this.refs.isStockOnlyInput.value);
    }

    render： function () {
        return (
            <form>
                <input type="text" placeholder="Search..." value={this.props.filterText} ref="filterTextInput" />
                <p>
                    <input type="checkbox" id="show-product" checked={this.props.isStockOnly} ref="isStockOnlyInput" /> <label htmlFor="show-produt">Only show products in stock</label> 
                </p>
            </form>
        );
    }
});

/** add method for child */
var FilterableProductTable = React.createClass({
    getInitialState: function () {
        return {
            filterText: '',
            isStockOnly: false
        };
    },
    
    handleUserInput: function (filterText, isStockOnly) {
        this.setState({
            filterText: filterText,
            isStockOnly: isStockOnly
        });
    }

    render: function () {
        return (
            <div>
                <SearchBar filterText={this.state.filterText} isStockOnly={this.state.isStockOnly} onUserInput={this.handleUserInput}/>
                <ProductTable products={this.props.products} filterText={this.state.filterText} isStockOnly={this.state.isStockOnly} />
            </div>
        );
    }
});
```