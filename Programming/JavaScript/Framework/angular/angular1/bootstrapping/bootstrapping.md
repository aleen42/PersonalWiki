## Bootstrapping [Back](./../angular1.md)

In this step, it's going to get familiar with the most important source code files of the AngularJS Phonecat App. Firstly, you may need to create a new branch for as a workspace to learn this project:

```bash
git checkout -f setp-0
```

> Note: when you learn other tutorials in the future, you can change the corresponding number.

Then set up the tutorial by running:

```bash
npm install
```

Then run it up at this step:

```bash
npm start
```

As you can see, an HTML page displays just a text "Nothing here yet!", which is actually constructed in `app/index.html`:

```html
<!doctype html>
<html lang="en" ng-app>
    <head>
        <meta charset="utf-8">
        <title>My HTML File</title>
        <link rel="stylesheet" href="bower_components/bootstrap/dist/css/bootstrap.css" />
        <script src="bower_components/angular/angular.js"></script>
    </head>
    <body>
        <p>Nothing here {{'yet' + '!'}}</p>
    </body>
</html>
```

### 1. Code Explaination

#### 1.1 The attribute `ng-app`

```html
<html ng-app>
```

The `ng-app` attribute represents an AngularJS directive, named `ngAPP`. In AngularJS, custom attributes are named with `kebab-case`, while the corresponding directives, which represents them, are named with `camelCase`. The `ngApp` directive is used to specify the root element of the application.

#### 1.2 The script `angular.js`

```html
<script src="bower_components/angular/angular.js"></script>
```

The script will register a callback and executed by the browser. After executed, AngularJS looks for the `ngApp` directive, and bootstrap the application once it's found.

#### 1.3 Double-curly binding with an expression

```
Nothing here {{'yet' + '!'}}
```

This line demonstrates two core features of AngularJS's templating capabilities:

- A binding, denoted by double-curlies: `{{ }}`
- A simple expression used in this binding: `'yet' + '!'`

The binding tells AngularJS that it should evaluate an expression and insert the result into the DOM in place of the binding. As we will see in the next step, rather than a one-time insert, a binding will result in efficient continuous updates whenever the result of the expression evaluation changes.

### 2. Bootstrapping AngularJS Applications

Despite of using `ngApp` directive to boostrap an AngularJS application, we can also use a script to bootstrap it in a manual way:

```html
<!doctype html>
<html>
<body>
    <div ng-controller="MyController">
        Hello {{greetMe}}!
    </div>
    <script src="http://code.angularjs.org/snapshot/angular.js"></script>
    
    <script>
        angular.module('myApp', [])
            .controller('MyController', ['$scope', function ($scope) {
                $scope.greetMe = 'World';
            }]);
        
        angular.element(function() {
            angular.bootstrap(document, ['myApp']);
        });
    </script>
</body>
</html>
```

> Note: should not use the `ngApp` directive when manually bootstrapping applicatons.
