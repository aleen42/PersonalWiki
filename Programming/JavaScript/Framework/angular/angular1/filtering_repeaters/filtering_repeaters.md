## Filtering Repeaters [Back](./../angular1.md)

This step of tutorial mainly discusses how to add a search box to filter results in the list of phones.

Firstly, we are going to change the template of the component:

```html
<!-- phone-list.template.html -->
<div class="container-fluid">
    <div class="row">
        <div class="col-md-2">
            <!--Sidebar content-->
            Search: <input ng-model="$ctrl.query" />
        </div>
        <div class="col-md-10">
            <!--Body content-->
            <ul class="phones">
                <li ng-repeat="phone in $ctrl.phones | filter:$ctrl.query">
                    <span>{{phone.name}}</span>
                    <p>{{phone.snippet}}</p>
                </li>
            </ul>
        </div>
    </div>
</div>
```

As we can see, the snippet above has imported an `input` element for inputting text to filter contents. The most important thing is that we have used the `filter` function of AngularJS. With using that core feature, we have two things to focus on:

- **Data binding**: by assigning the attribute `ng-model` with `ngModel` directive, AngularJS binds the value of the input box to the data model so that we can keep them in sync.

<p align="center">
    <img src="./tutorial_05.png" />
</p>

- **Filter function**: As we have bound the value of the input box to the variable `$ctrl.query`, the `filter` function can easily get this value to filter out a new array automatically whenever the value is changed.
