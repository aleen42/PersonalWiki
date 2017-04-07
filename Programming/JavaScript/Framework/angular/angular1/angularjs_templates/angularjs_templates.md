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
    <body ng-controller="PhoneListcontroller">
        <ul>
            <li ng-repeat="phone in phones">
                <span>{{phone.name}}</span>
                <p>{{phone.snippet}}</p>
            </li>
        </ul>
    </body>
</html>
```

As we can see in the snippet above, we have used two new directives: `ngRepeat`, and `ngController`.

With using `ngRepeat`:

- The repeater directive tells AngularJS to create a `<li>` element for each phone in the list.
- The expressions wrapped in curly braces `{{phone.name}}`, and `{{phone.snippet}}` will be replaced by the value of these expressions.

With using `ngController`:

- `PhoneListController` is in charge of the DOM sub-tree under (and including) the `<body>` element.
- The expressions above are set up in the controller `PhoneListController`.
 
> Note: we have also specified an AngularJS module `phonecatApp` for the directive `ngApp`, which contains the controller.