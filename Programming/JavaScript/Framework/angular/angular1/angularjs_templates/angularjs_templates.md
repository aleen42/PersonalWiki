## AngularJS Templates [Back](./../angular1.md)

For AngularJS applications, we encourage the use of the [Model-View-Controller (MVC) design pattern](http://en.wikipedia.org/wiki/Model%E2%80%93View%E2%80%93Controller) to decouple the code and separate concerns. With that in mind, let's use a little AngularJS and JavaScript to add models, views, and controllers to our app.

### 1. View and Template

In AngularJS, the **view** is a projection of the model through the HTML template, which means that whenever the model changes, AngularJS refreshes the appropriate binding points, which updates the view.

The view should be constructed like this in the app:


```html
<html ng-app="phonecatApp">
    
</html>
```