## Unit Tests [Back](./../JavaScript.md)

### 1. Introduction

Unit tests should be a large topic in the computer science when taking about tests during developing. However, this article is only focusing on how to do unit tests in JavaScript, and how we can use this tool to easily test our code. As there are so many tools for unit tests, here I want to document them, which can be seen in my developing work.

So, how to write unit tests, and run it?

### 2. Frameworks

When it comes to frameworks of unit tests, JavaScript developers usually make a decision among following:

- **QUnit**
- **Jasmine**
- **Mocha**

So what is the differences between them?

|QUnit|Jasmine|Mocha
:--|:---:|:-----:|:----:
Features|<ul><li>Similar to server-side frameworks(JUnit, Nunit)</li><li>Built by the jQuery team</li><li>Used to test jQuery's features</li><li>No dependencies</li><li>Can test server-side JavaScript</li></ul>|<ul><li>Open Source Framework</li><li>Behavior Driven Development framework</li><li>Supports both client-side and server-side testing</li></ul>|<ul><li>Open Source Framework</li><li>Started in Node</li><li>Supports both client-side and server-side testing</li><li>Supports both BDD and TDD style tests</li><li>Supports both command line and browser</li><li>Supports any JavaScript assertion library (YUI Port, expect.js, should.js, jshould.js, assert.js, chai.js)</li><li>Supports asynchronous testing 
</li><li>Requires an assertion library</li></ul>

### 3. Karma

When learning AngularJS (Angular 1.x), we may know that the official tutorial of AngularJS has adopted Karma to run unit tests. If we also want to use Karma, we may have to set up a configuration file firstly, named `karma.conf.js`.

```js
module.exports = function (config) {
    config.set({
        /** the root path of your application */
        basePath: '.',
    
        /** unit tests files */
        files: [
            '**/*.spec.js'
        ],
        
        frameworks: ['jasmine'],
        
        browsers: ['Chrome'],
        
        plugins: [
            'karma-chrome-launcher',
            'karma-jasmine'
        ]
        
        /** run a server to watch any change of unit tests files */
        autoWatch: false,
        
        /** only run tests once */
        singleRun: true,
        
        /** we need mocha to do unit tests */
        repoters: ['mocha']
    });
};
```
