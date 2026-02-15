## AngularJS Templates [Back](./../angular1.md)

For AngularJS applications, we encourage the use of the [Model-View-Controller (MVC) design pattern](http://en.wikipedia.org/wiki/Model%E2%80%93View%E2%80%93Controller) to decouple the code and separate concerns. With that in mind, let's use a little AngularJS and JavaScript to add models, views, and controllers to our app.

### 1. View and Template

In AngularJS, the **view** is a projection of the model through the HTML template, which means that whenever the model changes, AngularJS refreshes the appropriate binding points, which updates the view.

The view should be constructed like this in the app:

```html
<!doctype html>
<html lang="en" ng-app="phonecatApp">
    <head>
        <!-- ... -->
        <script src="bower_components/angular/angular.js"></script>
        <script src="app.js"></script>
    </head>
    <body ng-controller="PhoneListController">
        <ul>
            <li ng-repeat="phone in phones">
                <span>{% raw %}{{phone.name}}{% endraw %}</span>
                <p>{% raw %}{{phone.snippet}}{% endraw %}</p>
            </li>
        </ul>
    </body>
</html>
```

As we can see in the snippet above, we have used two new directives: `ngRepeat`, and `ngController`.

With using `ngRepeat`:

- The repeater directive tells AngularJS to create a `<li>` element for each phone in the list.
- The expressions wrapped in curly braces `{% raw %}{{phone.name}}{% endraw %}`, and `{% raw %}{{phone.snippet}}{% endraw %}` will be replaced by the value of these expressions.

With using `ngController`:

- `PhoneListController` is in charge of the DOM sub-tree under (and including) the `<body>` element.
- The expressions above are set up in the controller `PhoneListController`.
 
> Note: we have also specified an AngularJS module `phonecatApp` for the directive `ngApp`, which contains the controller.

### 2. Model and Controller

The data **model** is now instantiated within the **controller**, which is simply a constructor function that takes a `$scope` parameter.

```js
/** app.js */
/** Define the `phonecatApp` module */
var phonecatApp = angular.module('phonecatApp', []);

/** Define the controller within the module */
phonecatApp.controller('PhoneListController', function PhoneListController ($scope) {
    $scope.phones = [
        {
            name: 'Nexus S',
            snippet: 'Fast just got faster with Nexus S.'
        }, {
            name: 'Motorola XOOM™ with Wi-Fi',
            snippet: 'The Next, Next Generation tablet.'
        }, {
            name: 'MOTOROLA XOOM™',
            snippet: 'The Next, Next Generation tablet.'
        }
    ];
});
```

By providing context for our data model, the controller allows us to establish data-binding between the model and the view.

The concept of a scope in AngularJS is very important, which allows the template, data model, and controller to work together. With scopes, AnglarJS has separated both models and views, but keep in sync. It means that any changes in models or views will be reflected in both of them.

<p align="center">
    <img src="./tutorial_02.png" />
</p>

### 3. Testing

#### 3.1 Testing Controllers

In tests, we use an AngularJS service, called `$controller`, which will retrieve a controller by name.

```js
/** app.spec.js */
describe('PhoneListController', function () {
    beforeEach(module('phonecatApp'));
    
    it('should create a `phones` modle with 3 phones', inject(function ($controller) {
        var scope = {};
        var ctrl = $controller('PhoneListController', { $scope: scpoe });
        
        expect(scope.phones.length).toBe(3);
    }));
});
```

Before each test, we have used the method `beforeEach` to tell AngularJS to load the module `phonecatApp`. Calling `inject` is to tell AngularJS to inject the `$controller` service into our test function. Then this service can be used to create an instance of the `PhoneListController`, with which we can do the test.

> Note: in this tutorial, we have used the `.spec` suffix, so that the test file `something.spec.js` can be called by a corresponding file `something.js`. (Another common convention is to use a `_spec` or `_test` suffix like `something_spec.js` or `something_test.js`)

#### 3.2 Writing and Running Tests

This tutorial project has been pre-configured to run unit tests using Karma, to run a watching for testing, you shoule execute: `npm test` 

> Note: Karma will start new instances of Chrome and Firefox browsers to test, and if you want to specify it yourself, you can just configure it in the file `karma.conf.js`.

```js
/** ... */
browsers: ['Chrome'],
/** ... */
```

> Note: make sure you do not minimize the brwoser that Karma opend, because on some OS, memory assigned to a minimized browser is limited, which results in a extremely slow testing running.
