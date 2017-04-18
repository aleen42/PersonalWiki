## Directory and File Organization of AngularJS Applications [Back](./../angular1.md)

Despite of architecting applications to be modular and testable, we should also focus on how to organize our codebase in a way that makes it easy to locate quickly.

As applications grows, it becomes a burden to maintain if you put all things into file, like putting all components into a file. Therefore, remember to use a file to store one feature. **One feature per file**. With different features in a single file, we should also group them together so that we can locate them easily. Take `phoneList` as an example, we can put all related files into a folder named `app/phone-list/`. If we find out that certain features are used across different parts of the application, we can put them inside `app/core/`.

> app/
>> phone-list/
>>> phone-list.component.js
>>> <br />phone-list.component.spec.js

>> app.js

### 1. Using Modules

What if another project wants to use the component `phoneList`? We can make it as a module, which can be used anywhere with just copying the directory `phone-list/`.

> app/
>> phone-list/
>>> phone-list.module.js
>>> <br />phone-list.component.js
>>> <br />phone-list.component.spec.js

>> app.module.js

```js
/** app/phone-list/phone-list.module.js */
angular.module('phoneList', []);
```

```js
/** app/phone-list/phone-list.component.js */
angular.module('phoneList')
    .component('phonList', {
        /** .s.. */
    });
```

```js
/** app/app.module.js */
app.module('phonecatApp', [
    'phoneList'
]);
```

By passing `phoneList` inside the dependencies array when defining the `phonecatApp` module, AngularJS will make all entities registered on `phoneList` available on `phonecatApp` as well.

### 2. External Templates

As we knew before, we can specify a template by passing a inline string to the property `template` in the CDO. However, we may also find that it's not ideal especially when we need to build a large template. For this case, AngularJS has provided us another property `templateUrl` to allow us writing HTML code in a single file and reference it in the CDO.

```js
/** app/phone-list/phone-list.component.js */
angular.module('phoneList')
    .component('phoneList', {
        /** Note: the URL can be relative */
        templateUrl: 'phone-list/phone-list.template.html',
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

```html
<ul>
    <li ng-repeat="phone in $ctrl.phones">
        <span>{% raw %}{{phone.name}}{% endraw %}</span>
        <p>{% raw %}{{phone.snippet}}{% endraw %}</p>
    </li>
</ul>
```

### 3. Final Structure

After all refactorings, the structure of applications should be:

> app/
>> phone-list/
>>> phone-list.module.js
>>> <br />phone-list.component.js
>>> <br />phone-list.component.spec.js
>>> <br />phone-list.template.html

>> app.css
>> <br />app.module.js
>> <br />index.html
