## Certain object functions like `pick()` and `create()` [Back](./../underscore.md)

`_.pick()` is used to pick up some specific key-value pairs from an object. For example:

```js
_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, 'name', 'age'); /** => {name: 'moe', age: 50} */

_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, ['name', 'age']); /** => {name: 'moe', age: 50} */

_.pick({
    name: 'moe',
    age: 50,
    userid: 'moe1'
}, function (value, key, object) {
    return _.isNumber(value);
}); /** => {age: 50} */
```

As we can see, `_.pick()` will receive an object as the first parameter, while the second one has three situations: **Function**, **Array** or **Separative Parameters**.

Let's see how underscore handle those three conditions smartly.

```js
_.pick = function(object, oiteratee, context) {
    /** result is the created copy to return */
    var result = {}, obj = object, iteratee, keys;

    /** if object is null then return an empty object */
    if (obj == null) return result;

    /** if the second parameter is a function */
    if (_.isFunction(oiteratee)) {
        keys = _.allKeys(obj);
        
        /**
         * optimizeCb is to redefine where `this` point to,
         * according to the paramter `context`
         */
        iteratee = optimizeCb(oiteratee, context);
    } else {
        /**
         * the second parameter may be an array or a list of separative keys,
         * so underscore has used _.flatten to convert them all into an array.
         */
        keys = flatten(arguments, false, false, 1);
        
        /** also create a function for iteration */
        iteratee = function(value, key, obj) { return key in obj; };
        obj = Object(obj);
    }

    for (var i = 0, length = keys.length; i < length; i++) {
        var key = keys[i];
        var value = obj[key];
        
        /** if the iterative function returns `true`, then push it into the copy */
        if (iteratee(value, key, obj)) result[key] = value;
    }
    
    return result;
};
```

As for `_.create()`, it's always used to create a new object, with given prototype and own properties:

```js
var Person = function() {};

Person.prototype = {
    show: function() {
        console.log(this.name);
    }
};

var me = _.create(Person.prototype, {
    name: 'hanzichi'
});

console.log(me.name); /** => "hanzichi" */
me.show(); /** => "hanzichi" */
```

The most complicated one of this function is to check whether browsers support ES5:

```js
var Person = function() {};

Person.prototype = {
    show: function() {
        console.log(this.name);
    }
};

var me = null;

if (Object.create) {
    me = Object.create(Person.prototype);
} else {
    var _Person = function() {};
    _Person.prototype = Person.prototype;
    
    me = new _Person();
}

_.extendOwn(me, { name: 'hanzichi' });

console.log(me.name); /** => "hanzichi" */
me.show(); /** => "hanzichi" */
```