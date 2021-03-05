## Namepaths [Back](../jsdoc.md)

### 1. Basic Syntax

When referring to a JavaScript variable elsewhere in our documentation, we may need a way to maps such variables.

```js
// func
// Constructor
// Constructor#instanceMember
// Constructor.staticMember
// Constructor~innerMember
```

To use the basic syntax examples of Namepaths above:

```js
/**
 * Person
 * @constructor
 */
function Person() {
    /**
     * Person~say inner member
     * @function
     */
    function say() { console.log('innerMember'); }
    /**
     * Person#say instance member
     * @function
     */
    this.say = function () {
        /** @see Person~say */
        say();
        console.log('instanceMember');
    };
}

/**
 * Person.say static member 
 * @function 
 */
Person.say = function () { console.log('staticMember'); };

/** @see Person */
const p = new Person();
/** @see Person#say */
p.say();
/** @see Person.say */
Person.say();
```

Certainly, the declaration of Namepaths can also be chained together (this chaining can be used with any combination of the connecting symbols: `#`, `.`, and `~`):

```js
/**
 * Person
 * @constructor
 */
function Person() {
    /**
     * Idea
     * @constructor
     */
    this.Idea = function () {
        /**
         * Person#Idea#consider embed method
         * @function
         */
        this.consider = function () { console.log('considering'); };
    };
}

const p = new Person();
/** @see Person#Idea */
const i = new p.Idea();
/** @see Person#Idea#consider */
i.consider();
```

### 2. Special Cases

In addition, there are some special cases when using Namepaths: **modules**, **externals**, and **events**.

```js
/**
 * jQuery Object
 * @external $
 * @see {@link https://jquery.com/}
 */

/**
 * @module Module
 * a custom module
 */
class Module {}

/**
 * @event module:Module.myEvent
 * custom event
 */
Module.myEvent = function () {
    return 'event';
};

/** @see module:Module */
const module = new Module();
/** @see module:Module.event:myEvent */
console.log(Module.myEvent);
/** @see $ */
console.log($);
```

As shown in the example above, we need to prefix when using namepaths: `@module` and `@event`, except `@external`.

### 3. Escaped Character

Since we have used `#`, `.`, and `~` to construct Namepaths, we may need to escape them when there is conflicted characters.

```js
/** @namespace */
const chat = {
    "#channel": {
        /**
         * @type {boolean} open value
         */
        open: true,
        /**
         * @param msg
         */
        'say-"hello"': function (msg) {},
    },
};

/** @see {@link chat."#channel"} */
console.log(chat['#channel']);
/** @see {@link chat."#channel".open} */
console.log(chat['#channel'].open);
/** @see {@link chat."#channel"."say-\"hello\""} */
console.log(chat['#channnl']['say-"hello']('message'));
```
