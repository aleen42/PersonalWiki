## Two-way Data Binding [Back](./../angular1.md)

In this tutorial, we mainly discuss how to add a feature that allows users to control the order of items in the phone list.

Firstly, we may need to change the template:

```html
<!-- phone-list.template.html -->
<div class="container-fluid">
    <div class="row">
        <div class="col-md-2">
            <!--Sidebar content-->
            <p>
                Search: <input ng-model="$ctrl.query" />
            </p>
            
            <p>
                Sort by:
                <select ng-model="$ctrl.orderProp">
                    <option value="name">Alphabetical</option>
                    <option value="age">Newest</option>
                </select>
            </p>
        </div>
        <div class="col-md-10">
            <!--Body content-->
            <ul class="phones">
                <li ng-repeat="phone in $ctrl.phones
                    | filter:$ctrl.query
                    | orderBy:$ctrl.orderProp">
                    <span>{% raw %}{{phone.name}}{% endraw %}</span>
                    <p>{% raw %}{{phone.snippet}}{% endraw %}</p>
                </li>
            </ul>
        </div>
    </div>
</div>
```
