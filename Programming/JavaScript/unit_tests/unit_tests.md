## Unit Tests [Back](./../JavaScript.md)

### 1. Introduction

Unit tests should be a large topic in the computer science when taking about tests during developing. However, this article is only focusing on how to do unit tests in JavaScript, and how we can use this tool to easily test our code. As there are so many tools for unit tests, here I want to document them, which can be seen in my developing work.

So, how to write unit tests, and run it?

### 2. Test Cases Writing

Before running our cases for testing, we may need to write it at first. There're so many tools for writing such cases, among them I usually use **Jasmine** or **Chai**.

#### 2.1 

### 3. Test Cases Running

### 3.1. Mocha

[**Mocha**](https://mochajs.org/) is a funny test framework, which allows you run test cases with multiple features like leak detection, string difference supporting, etc.

### 2. Karma

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
