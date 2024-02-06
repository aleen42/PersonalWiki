## Components [Back](./../angular1.md)

The **template** (the part of the view containing the bindings and presentation logic) acts as a blueprint for how our data should be organized and presented to the user. The **controller** provides the context in which the bindings are evaluated and applies behavior and logic to our template.

However, there are still a couple of areas we can do better:

- What if we want to reuse the same functionality in a different part of the application?
- The scope is not isolated from other parts of the page, which means that unrelated change in a different part of the page could have unexpected side effects on views.

These two problems has led us to use **components**.

Since the combination (**template** + **controller**) is such a common pattern, AngularJS provides an easy way to combine them together into reusable and isolated entities, a.k.a **components**. To eliminate risk of effect from other parts of the application, AngularJS has also created a so-called **isolate scope** for each instance of components.

### 1. Creating Components

To create a component, we use the method `component()` of an AngularJS module, and we must provide the name of the component and the Component Definition Object (CDO).

The simplest way to create a component, like `greetUser`, is just to construct CDO with a template and a controller.

```js
var CDO = {
    template: 'Hello, {% raw %}{{$ctrl.user}}{% endraw %}!',
    controller: function GreetUserController() {
        this.user = 'world';
    }
};

angular.module('myApp')
    .component('greetUser', CDO);
```

Then we can use it in views whenever we want by including `<greet-user></greet-user>`. Where did that `$ctrl` come from and what does it refer to? As it's considered a good practice to avoid using the scope directly, `$ctrl` has been referred to the controller instance.

> Note: this simple way is extremely useful when creating "presentational" components, that do not attach any behavior to the template.

### 2. Using Components

Take the app `PhonecatApp` as an example, we can use components like this:

```html
<!-- app/index.html -->
<html ng-app="phonecatApp">
<head>
    <!-- ... -->
    <script src="bower_components/angular/angular.js"></script>
    <script src="app.js"></script>
    <script src="phone-list.component.js"></script>
</head>
<body>
    <!-- Use a custom component to render a list of phones -->
    <phone-list></phone-list>
</body>
</html>
```

```js
/** app.js */
angular.module('phonecatApp', []);
```

```js
/** phone-list.component.js */
angular.module('phonecatApp')
    .component('phoneList', {
        /** CDO */
        template:
            '<ul>'
                + '<li ng-repeat="phone in $ctrl.phones">'
                    + '<span>{% raw %}{{phone.name}}{% endraw %}</span>'
                    + '<p>{% raw %}{{phone.snippet}}{% endraw %}</p>'
                + '</li>'
            + '</ul>',
        controller: function PhoneListController() {
            this.phones = [
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
        }
    });
```

With using components, we have gained that:

- make phone list reusable
- make the main view (`app/index.html`) more cleaner
- make component safe by isolating it
- make component easier to test by isolating it

<p align="center">
    <img src="./tutorial_03.png" />
</p>

> Note: when naming a file, it's recommended to distinguish different types of entities by suffix, like `.component`. In other words, a `someComponent` is recommended to declared in the file named `some-component.component.js`.

### 3. Testing Components

With combining a controller with a template into a component, how can we process the unit test? Before that , we may code like the following snpipet:

```js
/** app.spec.js */
describe('PhoneListController', function () {
    beforeEach(module('phonecatApp'));

    it('should create a `phones` modle with 3 phones', inject(function ($controller) {
        var $scope = {};
        var $ctrl = $controller('PhoneListController', { $scope: $scpoe });

        expect($scope.phones.length).toBe(3);
    }));
});
```

And now you can change it like this:

```js
/** phone-list.component.spec.js */
describe('PhoneList', function () {
    /** Load the module that contains the `phoneList` component before each test */
    beforeEach(module('phonecatApp'));
    
    /** test the controller */
    describe('PoneListController', function () {
        it('should create a `phones` modle with 3 phones', inject(function ($controller) {
            var $ctrl = $controller('phoneList');
    
            expect($ctrl.phones.length).toBe(3);
        }));
    });
});
```

