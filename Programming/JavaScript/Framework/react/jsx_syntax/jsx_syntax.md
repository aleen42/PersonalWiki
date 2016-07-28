## JSX Syntax [Back](./../react.md)

JSX is a Javascript syntax extension that look similar to XML. You can use a simple JSX syntactic transform with React.

#### Why JSX?

According to the official statement, JSX is concise and familiar syntax for defining tree structures with attributes.

#### HTML Tags vs. React Components

React can either render HTML tags (strings) or React Components(classes).

To render a HTML tags, just use camelCase tag name in JSX:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** camelCase Naming */
var divElement = <div className="foo" />;
ReactDOM.render(
    divElement,
    document.getElelementById('example')
);
{%endace%}

To render a React Component, just create a local variable that naming with PascalCase name:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var MyComponent = React.createClass({/** ... */});
var myElement = <MyComponent someProperty={true} />;
ReactDOM.render(
    myElement,
    document.getElementById('example')
);
{%endace%}

*Note: Since JSX is JavaScript, identifiers such as **class** and **for** are discouraged as XML attribute names. Instead, React DOM components expect DOM property names like **className** and **htmlFor**, respectively.*

#### JSX Transforms

React JSX transforms from an XML-like syntax into native JavaScript. XML **elements**, **attributes** and **children** will be transformed into arguments that are passed to the moethod `React.createElement`.

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var Nav;

/** input JSX syntx */
var app = <Nav color="blue">;
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
var Nav;

/** output JavaScript syntax */
var app = React.createElement(Nav, {color: 'blue'});
{%endace%}

JSX also allows specifying children using XML syntax:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var Nav;
var Profile;

/** input JSX syntx */
var app = <Nav color="blue"><Profile>click</Profile></Nav>;
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
var Nav;
var Profile;

/** output JavaScript syntax */
var app = React.creatElement(
    Nav,
    { color: 'blue' },
    React.createElement(
        Profile,
        null,
        'click'
    )
);
{%endace%}

JSX will infer(推斷出) the class's `displayName` from the variable assignment when the `displayName` is **undefined**:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** input JSX syntx */
var Nav = React.createClass({ });
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
/** output JavaScript syntax */
var Nav = React.createClass({ displayName: 'Nav' });
{%endace%}

**Some tutorials:**

- [**JSX to JavaScript with Babel REPL**](https://babeljs.io/repl/)
- [**HTML to JSX converter**](http://magic.reactjs.net/htmltojsx.htm)

#### Namespaced Components

If you are building a component that has many children, like a form, you might end up with something with a lot of variable declarations:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** Awkward block of variable declarations */
var Form = MyFormComponent;
var FormRow = Form.Row;
var FormLabel = Form.Label;
var FormInput = Form.Input;

var App = (
    <Form>
        <FormRow>
            <FormLabel />
            <FormInput />
        </FormRow>
    </Form>
);
{%endace%}

To make it simpler and easier, *namespaced components* let you use one component that has other components as attributes:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
var Form = MyFormComponent;

var App = (
    <Form>
        <Form.Row>
            <Form.Label />
            <Form.Input />
        </Form.Row>
    </Form>
);
{%endace%}

To do this, you just need to create your "sub-components" as attributes of the main component:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** input JSX syntx */
var MyFormComponent = React.createClass({ /** ... */ });

MyFormComponent.Row = React.createClass({ /** ... */ });
MyFormComponent.Label = React.createClass({ /** ... */ });
MyFormComponent.Input = React.createClass({ /** ... */ });
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
/** output JavaScript syntax */
var App = (
    React.createElement(Form, null, 
        React.createElement(Form.Row, null, 
            React.createElement(Form.Label, null),
            React.createElement(Form.Input, null)
        )
    )
);
{%endace%}

#### JavaScript Expressions

##### Attribute Expressions

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** input JSX syntx */
var person = <Person name={window.isLoggedIn ? window.name : ''} />;
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
/** output JavaScript syntax */
var person = React.createElement(
    Person,
    { name: window.isLoggedIn ? window.name : '' }
);
{%endace%}

##### Boolean Expressions

Omitting the value of an attribute causes JSX to treat it as `true`. To pass `false` an attribute expression must be used. This often comes up when using HTML form elements, with attributes like `disabled`, `required`, `checked` and `readOnly`.

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** two equivlent in jsx */
var buttonInput = <input type="button" disabled />;
var buttonInput = <input type="button" disabled={true} />;

var buttonInput = <input type="button" />;
var buttonInput = <input type="button" disabled={false} />;
{%endace%}

##### Child Expressions

Likewise, JavaScript expressions may be used to express children:

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** input JSX syntx */
var content = <Container>{window.isLoggedIn ? <Nav /> : <Login />}</Container>;
{%endace%}

{%ace edit=false, lang='javascript', theme='tomorrow' %}
/** output JavaScript syntax */
var content = React.createElemnt(
    Container,
    null,
    window.isLoggedIn ? React.createElement(Nav) : React.createElement(Login)
);
{%endace%}

##### Comments

It's easy to add comments within your JSX; they're just JS expressions. You just need to be careful to put `{}` around the comments when you are within the children section of a tag.

{%ace edit=false, lang='jsx', theme='tomorrow' %}
/** input JSX syntx */
var content = <Container>{/** comments here */}</Container>;
{%endace%}