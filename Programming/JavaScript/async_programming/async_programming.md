## Asynchronous Programming [Back](./../JavaScript.md)

### 1. Introduction

In the computer science, I have always grasped that "Asynchronous" is a word for describing working states between threads. If the job of one thread does not affect another one, it indicates to be asynchronous. In this chapter, this word is mostly used for representing a skill of programming.

You may ask why we should use such a asynchronous programming skill. As JavaScript is almost run in a thread, and its executing blocks the UI thread at the same time, resulting in a really "disastrous" user experience, asynchronous programming allows developers to write code in a asynchronous way to improve performance of JavaScript code. With making great use of CPU resources to prevent from wasting calculation units, the effect is always impressive. For example, a long time task will occupy CPU without calculating anymore, like parsing a large JSON, reading a file, or requesting something in a bad network status.

Certainly, asynchronous programming skill does not work in any cases. Before using such a skill to handle multitasking, be sure that tasks are non-preemptive (非優先級的), which also means that they're not related to each other. If one task relies on the result of another task, it's absolutely impossible to improve them by converting into in a asynchronous way. To explain it more apparently, I will take the following case as an example:

Assume that we have four variables `a`, `b`, `c`, and `d` respectively, and then considering a simple task, in which we want to add them together.

The first way is as shown in the following snippet (**a common way**):

```js
/**
 * 1. calculating the adding of `a` and `b`
 * 2. calculating the adding of `c` and the result of step 1
 * 3. calculating the adding of `d` and the result of step 2
 */
var result = d + (c + (a + b));
```

And the second way is (**a asynchronous way**):

```js
/**
 * 1. calculating the adding of `a` and `b`,
 *    and the adding of `c` and `d` at the same time
 * 2. calculating the adding of two results of step 1
 */
var result = (d + c) + (a + b);
```

With considering two ways of calculating above, it's obvious that the second way is faster. Why? That's because each adding of the first way has relied on the result of previous step, while tasking of adding `c` and `d` is completely isolated from adding `a` and `b`. Therefore, the second way has saved some time by executing them in parallel.


> Note: asynchronous programming does not mean to use multiple threads.

### 2. Continuation-Passing Style (CPS)

#### 2.1 Introduction

Before discussing how to code in JavaScript with asynchronous programming skills, it is recommended to know a style in functional programming firstly, named **Continuation-Passing Style**, a.k.a **CPS**. In this style, control flows are passed explicitly, contrasted with direct style.

Also take the adding task as an example:

```js
/** direct style */
function add(prev, next) {
    return prev + next;
}

/** continuation-passing style */
function add(prev, next, callback) {
    callback(prev + next);
}
```

What is the difference with using continuation-passing style in JavaScript? There is no doubt that we don't need to wait for the return of calling adding function any more, which is especially efficient in the case when the adding task costs too much.

```js
/** calculation of result have to wait for the return of adding `a` and `b` */
result = c + add(a, b);

/** if using continuation-passing style, no waiting anymore */
add(a, b, function (sum) {
    result = c + sum;
};
```

#### 2.2 How to convert into CPS?

For any code with direct style, we can convert it into corresponding CPS style mechanically, like applying a mathematical theory. In the following case, we will implement a task that loads the avatar image from a user. The main process is:

1. loading profile according to the user id and then 
2. loading avatar images according to the profile

```js
function loadProfile(id) {
    /** calculating ... */
    return profile;
}

function loadImage(url) {
    /** calculating ... */
    return image;
}

function loadAvatarImage(id) {
    var profile = loadProfile(id);
    return loadImage(profile.imageUrl);
}

var image = loadAvatarImage(1);
```

As we can see, this is a common way to do the task, which belongs to the direct style. To convert it into CPS, we should follow these several steps:

1. implement each function again with accepting a callback function as a last argument:
    ```js
    function loadProfile(id, callback) {
        /** calculating ... */
        callback(profile);
    }
    
    function loadImage(url, callback) {
        /** calculating ... */
        callback(image);
    }
    ```
2. changing the process of loading by passing callback functions and pass the final result to the accepted callback function:
    ```js
    function loadAvatarImage(id, callback) {
        loadProfile(id, function (profile) {
            loadImage(profile.imageUrl, function (image) {
                callback(image);
            });
        });
    }
    ```
3. call it by passing a callback function to handle the returned result:
    ```js
    var image;
    loadAvatarImage(1, function (img) {
        image = img;
    });
    ```

Now then, since we have used callback function to handle the result, we don't need to wait for the assignment anymore, and we can just continue to let the code to do anything else.

##### **2.2.1 CPS converting for loops**

In additional, what if we want to use a loop flow to load avatar images for two users, the common way to implement it is to use direct style like this:

```js
var ids = [1, 2];
var images = [];
for (var i = 0, len = ids.length; i < len; i++) {
    loadAvatarImage(i, function (img) {
        images[i] = img;
    });
    
    console.log('done');
}
```

In the case of such a loop flow, we can also convert them into CPS style by stepping as followed:

1. generate a recursive function for the loop flow:
    ```js
    function loopToLoad(i, arr) {
        if (i < arr.length) {
            loopToLoad(i + 1, arr);
        } else {
            console.log('done');
        }
        
        loadAvatarImage(i, function (img) {
            images[i] = img;
        });
    }
    ```
2. creating forEach-like function by extracting `visitor`, and `done`:
    ```js
    function forEachLoad(i, arr, visitor, done) {
        if (i < arr.length) {
            visitor(arr[i], i, function () {
                forEachLoad(i + 1, arr, next, done);
            });
        } else {
            done();
        }
    }
    ```
3. passing two types of callback functions:
    ```js
    forEachLoad(0, ids, function (item, index, next) {
        loadAvatarImage(index, function (img) {
            images[index] = img;
        });
        
        next();
    }, function () {
        console.log('done');
    });
    ```

Wow, awesome for loops without worriying about the large size of an array!

##### **2.2.1 CPS converting for try-catch blocks**


