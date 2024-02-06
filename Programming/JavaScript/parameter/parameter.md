## Parameters Passing [Back](./../JavaScript.md)

In the computer science, there are different types of ways to pass parameters to a function, like **calling by value**, **calling by reference**, etc.

Among of them, calling by value and calling by reference are the most common way in most programming language. In JavaScript, which one is the way to pass parameters? It depends.

When a primitive type of data is passed as parameters, it adopts the way of **calling by value**, and it means that the original data will not change if you assign another value to the passed parameter.

When an object or an array type of data is passed, it adopts a new way called **calling by sharing**. In this way, the internal environment of the function has shared the same object with the passing one. Therefore, you can change it in the function. Nevertheless, you can only change the members of this type of data like the following:

```js
function foo(o) {
    o.x = 100;
}

var obj = { x: 200 };
foo(obj);

console.log(obj.x); /** => 100  */
```

You cannot mutate the whole data:

```js
function foo(o) {
    o = 100;
}

var obj = { x: 200 };
foo(obj);

console.log(obj.x); /** => 200  */
```
