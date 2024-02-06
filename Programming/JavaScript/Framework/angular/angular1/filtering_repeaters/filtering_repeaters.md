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
                    <span>{% raw %}{{phone.name}}{% endraw %}</span>
                    <p>{% raw %}{{phone.snippet}}{% endraw %}</p>
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

When it comes to testing, it's not easy to use unit tests to test templates, DOM manipulation or interoperability of components. Therefore, we need to write some E2E tests. As the search feature was fully implemented via templates and data binding, we will write the E2E test to ensure that the feature works.

```js
/** e2e-tests/scenarios.js */
describe('PhoneCat Application', function () {
    describe('phoneList', function () {
        beforeEach(function () {
            browser.get('index.html');
        });
        
        it('should filter the phone list as a user types into the search box', function () {
            var phoneList = element.all(by.repeater('phone in $ctrl.phones));
            var query = element(by.model('$ctrl.query'));
            
            expect(phoneList.count()).toBe(3);
            
            query.sendKeys('nexus');
            expect(phoneList.count()).toBe(1);
            
            query.sendKeys('motorola');
            expect(phoneList.count()).toBe(2);
        });
    });
});
```

Much like Karma is the test runner for unit tests, we use Protractor to run E2E tests with `npm run protractor`.
