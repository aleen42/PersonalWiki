## Aspect-oriented Programming(AOP) [Back](../JavaScript.md)

In computer science, aspect-oriented programming, a.k.a AOP, is a programming paradigm that aims to use modules to describe crosscutting concern(横向切入点) of an object, a class, or even a function. In JavaScript, it can be powerful especially when developers want to inject some logical code, which is not related to data logic itself. In a case when we need to track defined event, like user input from a site, developers may not want to change the original logical methods as the tracking code may be temporary. I just define this part of code as a function, named with `business`:

```js
const business = () => {
    /** code related to the business itself */
};
```

At this moment, if we want to track some events before calling this methods, we can wrap this function with AOP paradigm rather than modify its business logic like that:

```js
const fn = business;
business = () => {
    /** tracking code */
    /** ... */
    fn();
};
```

Like injecting snippet, right? Similarly, we can extend two methods for each `Function` object, `Function.prototype.before`, and `Function.prototype.after`, so that we can easily inject snippet before, or after the function is called:

```js
Object.assign(Function.prototype, {
    before: function (func) {
        const self = this;
        return function () {
            func.apply(this, arguments);
            self.apply(this, arguments);
        };
    },
    after: function (func) {
        const self = this;
        return function () {
            self.apply(this, arguments);
            func.apply(this, arguments);
        };
    },
});
```

And then, `business` methods can be easily injected tracking code like the following snippet:

```js
business = business.before(() => {/** tracking code ... */});
```

In JavaScript, features of `get` and `set` for a JavaScript object are always used by developers, and this is also another kind of AOP, as you can inject aspect code into any process of accessing or modifying members of an object. However, abusing this feature will be a disaster as a project becomes larger and larger, especially when developers try to mix code of business part into such an aspect.
