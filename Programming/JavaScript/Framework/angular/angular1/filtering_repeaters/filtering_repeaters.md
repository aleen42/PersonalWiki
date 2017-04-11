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
