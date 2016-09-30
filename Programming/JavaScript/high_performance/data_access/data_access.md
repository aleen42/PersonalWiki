## Data Access [Back](./../high_performance.md)

Similar to other languages, though, where data is stored can greatly affect how quickly it can be accessed later in JavaScript. There are **4 basic places** which data can be accessed:

- **Literal values**
    
    Any value that represents just itself and is not stored in a particular location. **strings**, **numbers**, **Booleans**, **objects**, **arrays**, **functions**, **regular expressions**, and the special values **null** and **undefeind** can be represented as literal.

- **Variables**

    Any developer-defined location for storing data.
    
- **Array items**

    A numerically indexed location within a JavaScript **Array** object.
    
- **Object members**

    A string-indexed location within a JavaScript object.

A general trend has indicated that: **literal values and local variable access tend to be faster than array item and object member access**. So the advice is to use literal values and local variables whenever possible, and limit use of array items and object members, which speed of execution is a concern.

### Managing Scope

When dealing with scope, we must consider performance as well. That's why we should understand exactly how scope works before, and how speed relates to scope.

#### Scope Chains and Identifier Resolution

In JavaScript, any function is represented as an object, which will have accessible properties or not accessible like [[Scope]]. The internal [[Scope]] property contains a collection of objects, representing **the scope in which the function was created**. This collection is named the function's **Scope Chain**, which will determine the data that a function can access. Objects in the Scope chain are called **Variable Objects**, each of which will contains entries for variables in the form of key-value pairs.

```js
function add(num1, num2) {
    var sum = num1 + num2;
    return sum;
}
```

Like the function `add()`, its Scope Chain will contain an object, which is pointed to the Global object, which means that this function is created at the global scope:

![](./add_scope_chain.png)

Suppose that the following code is executed:

```js
var total = add(5, 10);
```

Executing the `add()` function will trigger the creation of an internal object called **Execution Context**, which defines the environment in which a function is being executed. After a function has been completely executed, the execution context will be destroyed.

An execution object will have its own scope chain, which will stores two objects: **Activation object** and **Global object**. The activation object will contain entries for all local variables, named arguments, the **arguments** collection, and **this**.

![](./activation_object.png)

What we can see above is that the activation object has been pushed to the front of the scope chain, and it will be destroyed as the execution context is destroyed.

Variable identifying will search the scope chain, and is deemed to be undefined when none is matched. It's this search process that affects performance.

> **Two variables with the same name may exist in different parts of the scope chain**. In that case, the identifier is bound to the variable that is found first in the scope chain traversal, and the first variable is said to shadow the second.

#### Identifier Resolution Performance

Consequently, **local variables are always the fastest to access inside of a function, whereas global variables will generally be the slowest**. As the depth grows, the time of this process will grow as well.

So, it's advisable to use local variables whenever possible to improve performance in browsers without optimizing JavaScript engines. Consider the following example:

```js
function initUI() {
    var bd = document.body;
    var links = document.getElementsByTagName('a');
    var i = 0; 
    var len = links.length;
    
    while (i < len) {
        update(links[i++]);
    }
    
    document.getElementById('go-btn').onclick = function () {
        start();
    };
    
    bd.className = 'active';
}
```

This function contains three referencs to `document`, which is a global object. In order to reduce the cost of accessing it, we are recommended to code like that:

```js
function initUI() {
    /** store a reference to `document` in the local `doc` variable */
    var doc = document;
    var bd = doc.body;
    var links = doc.getElementsByTagName('a');
    var i = 0; 
    var len = links.length;
    
    while (i < len) {
        update(links[i++]);
    }
    
    doc.getElementById('go-btn').onclick = function () {
        start();
    };
    
    bd.className = 'active';
}
```

#### Scope Chain Augmentation(擴大化)

Though we won't change an execution context's scope chain, we can also temporarily augment the scope chain while it's being executed with two statements. The first of these is `with`, which is usually seen as a convenience to avoid writing the same code repeatedly.

```js
function initUI() {
    with (document) {
        /** avoid! */
        var bd = doc.body;
        var links = doc.getElementsByTagName('a');
        var i = 0; 
        var len = links.length;
        
        while (i < len) {
            update(links[i++]);
        }
        
        doc.getElementById('go-btn').onclick = function () {
            start();
        };
        
        bd.className = 'active';   
    }
}
```

Though this may seem more efficient, it actually creates a performance problem. While executing the `with` statement, the execution context's scope chain is temporarily augmented. A new variable object is created containing all of the properties of the specified object, like `document` here, which will be pushed to the front of the scope chain. That means local variables are now in the second scope chain object, make it more expensive to access.

![](./scope_chain_augmentation.png)

Besides `with` statement, the `try-catch` statement also has the same effect:

```js
try {
    throwError();
} catch (e) {
    /** scope chain is augmented here */
    console.log(e.message);
}
```

However, since `try-catch` statement is still useful for us, we are recommended to use it when we have met some error we do not know. To minimize the performance impact by executing as little code as necessary within it, we can **use a method to handle this error**. Since there is just one statement executed and no local variables accessed, the temporary scope chain augmentation does not affect the performance of the code.

```js
try {
    throwError();
} catch (e) {
    /** delegate to a handler method */
    handleError(e);
}
```

#### Dynamic Scopes

Both the `with` statement and the `catch` clause of a `try-catch` statement, as well as a function containing `eval()`, are all considered to be **Dynamic Scopes**.