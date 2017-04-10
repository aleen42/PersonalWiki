## Directory and File Organization of AngularJS Applications [Back](./../angular1.md)

Despite of architecting applications to be modular and testable, we should also focus on how to organize our codebase in a way that makes it easy to locate quickly.

As applications grows, it becomes a burden to maintain if you put all things into file, like putting all components into a file. Therefore, remember to use a file to store one feature. **One feature per file**. With different features in a single file, we should also group them together so that we can locate them easily. Take `phoneList` as an example, we can put all related files into a folder named `app/phone-list/`. If we find out that certain features are used across different parts of the application, we can put them inside `app/core/`.

> app/
>> phone-list/
>>>phone-list.component.js
>>><br />phone-list.component.spec.js
>> app.js

