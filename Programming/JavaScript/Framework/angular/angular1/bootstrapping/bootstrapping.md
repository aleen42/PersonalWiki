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