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

<table>
    <thead>
        <th></th>
        <th>QUnit <img src="https://aleen42.github.io/badges/src/qunit.svg" alt="qunit" title="qunit"/></th>
        <th>Jasmine <img src="https://aleen42.github.io/badges/src/jasmine.svg" alt="jasmine" title="jasmine"/></th>
        <th>Mocha <img src="https://aleen42.github.io/badges/src/mocha.svg" alt="mocha" title="mocha"/></th>
    </thead>
    <tbody>
        <tr>
            <td><strong>Features</strong></td>
            <td>
                <ul>
                    <li>Similar to server-side frameworks(JUnit, Nunit)</li>
                    <li>Built by the jQuery team</li>
                    <li>Used to test jQuery's features</li>
                    <li>No dependencies</li>
                    <li>Can test server-side JavaScript</li>
                </ul>
            </td>
            <td>
                <ul>
                    <li>Open Source Framework</li>
                    <li>Behavior Driven Development framework</li>
                    <li>Supports both client-side and server-side testing</li>
                </ul>
            </td>
            <td>
                <ul>
                    <li>Open Source Framework</li>
                    <li>Started in Node</li>
                    <li>Supports both client-side and server-side testing</li>
                    <li>Supports both BDD and TDD style tests</li>
                    <li>Supports both command line and browser</li>
                    <li>Supports any JavaScript assertion library (YUI Port, expect.js, should.js, jshould.js, assert.js, chai.js)</li>
                    <li>Supports asynchronous testing</li>
                    <li>Requires an assertion library</li>
                </ul>
            </td>
        </tr>
        <tr>
            <td><strong>Methods</strong></td>
            <td>
                <ul>
                    <li><code>ok(state, message)</code></li>
                    <li><code>equal(actual, expected, message)</code></li>
                    <li><code>notEqual(actual, expected, message)</code></li>
                    <li><code>deepEqual(actual, expected, message)</code></li>
                    <li><code>notDeepEqual(actual, expected, message)</code></li>
                    <li><code>strictEqual(actual, expected, message)</code></li>
                    <li><code>notStrictEqual(actual, expected, message)</code></li>
                    <li><code>raises(actual, expected, message)</code></li>
                </ul>
            </td>
            <td>
                <ul>
                    <li><code>expect(x).(not.)toEqual(y);</code></li>
                    <li><code>expect(x).(not.)toBe(y);</code></li> 
                    <li><code>expect(x ).(not.)toMatch(pattern);</code></li>
                    <li><code>expect(x ).(not.)toBeDefined();</code></li>
                    <li><code>Expect(x).(not.)toBeUndefined();</code></li>
                    <li><code>expect(x ).(not.)toBeNull();</code></li>
                    <li><code>expect(x ).(not.)toBeTruthy();</code></li>
                    <li><code>expect(x ).(not.)toBeFalsy();</code></li>
                    <li><code>expect(x ).(not.)toContain(y);</code></li>
                    <li><code>expect(x ).(not.)toBeLessThan(y);</code></li>
                    <li><code>expect(x ).(not.)toBeGreaterThan(y);</code></li>
                    <li><code>expect(function(){ fn ();}).(not.)toThrow(ex);</code></li>
                </ul>
            </td>
            <td>
                <ul>
                    <li>Assert: <code>var assert = chai.assert;</code></li>
                    <li>Expect: <code>var expect = chai.expect;</code></li>
                    <li>Should: <code>var should = chai.should(); /** notice should is a function */</code></li>
                </ul>
            </td>
        </tr>
        <tr>
            <td><strong>Summary</strong></td>
            <td>
                <p>It's easy to use, because you just need to include two files before running tests.</p>
            </td>
            <td>
                <p>It's easier to use, because all things has been wrapped in a package.</p>
            </td>
            <td>
                <p>It's flexible but not easy to use, as you have to choose assertion framework, like Chai, which is the most popular alternative.</p>
            </td>
        </tr>
    </tbody>
</table>

As shown in the table above, we can apparently know the main different features among theses three frameworks, and different methods we may use to create test cases. Then, how to create cases explicitly?

For **QUnit**, we can code like this snippet:

```js
/** test.spec.js */
test('case', function () {
    ok(1 == '1', 'Passed!');
});
```

As for **Jasmine**:

```js
/** test.spec.js */
describe('case1', function () {
    it('should not be equal', function () {
        expect(1).not.toEqual('1');
    });
});

/** ignore the following thest */
xdescribe('case2', function () {
    it('should be equal', function () {
        expect(1).toEqual('1');
    })
});
```

When it comes to **Mocha**, it's similar to Jasmine:

```js
/** test.spec.js */
describe('case', function () {
    it('should not be equal', function () {
        expect(1).to.equal(1);
    });
});
```

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
