## Resposive Interfaces [Back](./../high_performance.md)

In a case when we click something on a web page but nothing happen, it's a worse experience for users. Most users tend to repeat any action that does not result in an obvious change, and so ensuring responsiveness in a web application is an important performance problem.

Most browsers have a single process that is shared between JavaScript execution and user interface updates. What it means is that only one of these operations can be performed at a time, also meaning that the user interface cannot respond to input while JavaScript code is executed and vice versa. In brief, executing code will prevent users from interacting with your web page.

### 1. The Browser UI Thread

The so-called process shared by JavaScript and user interface updates is frequently referred to as the browser UI thread (though it's not accurate for all browsers). Once the process is idle, it will extract tasks, either JavaScript code to execute or UI updates to perform, to complete. The tasks of UI updating include redraws and reflows.

Consider the case where a button click results in a message being displayed on the screen:

```html
<html>
<head>
    <title>Browser UI Thread Example</title>
</head>
<body>
    <button onclick="handleClick()">Click me</button>
    <script type="text/javascript">
        function handleClick() {
            var div = document.createElement('div');
            div.innerHTML = 'Clicked!';
            document.body.appendChild(div);
        }
    </script>
</body>
</html>
```

Once the button is clicked, it will create and add two new tasks to a queue, waiting for being executed. The first task is to change the appearance of the button to indicate it was clicked, while second one is to execute the JavaScript code. After tasks are completed, the function `handleClick()` will also result in a new task to update UI. What if users tries to interact with the page while a task is being executed? In fact, most browsers stop creating tasks while JavaScript code is being executed.

#### 1.1 Browser Limits

Browsers place limits on the amount of time that JavaScript take to execute, so that it won't block the UI thread forever. There're two such limits: the **call stack size limit** and the **long-running script limit**. As we know before, the call stack size limitation limits executing code recursively at many times. The long-running script limit is sometimes called the long-running script timer or the runaway script timer, which will keep track of how long a script has been running and stop it once it hits the limitation. Besides checking time for executing, browsers will also shutdown a script by checking available memory and CPU resources. Of course, each browser has a slightly different approach to long-running script detection:

- Internet Explorer, as of version 4, sets a default limit of 5 million statements; this limit is stored in a Windows registry setting called *HKEY_CURRENT_USER\Software\Microsoft\InternetExplorer\Styles\MaxScriptStatements*.
- Firefox has a default limit of 10 seconds; this limit is stored in the browser's configuration settings (accessible by typing **about:config** in the address box) as the *dom.max_script_run_time key*.
- Safari has a default limit of 5 seconds; this setting cannot be altered, but you can disable the timer by enabling the *Develop* menu and selecting *Disable Runaway JavaScript Timer*.
- Chrome has no separate long-running script limit and instead relies on its generic crash detection system to handle such instances.
- Opera has no long-running script limit and will continue to execute JavaScript code until it has finished, though, due to Opera's architecture, this will not cause system instability while the execution is completed.

#### 1.2 How Long Is Too Long?

To create a good user experience, a script should be executed as fast as possible. Brendan Eich, creator of JavaScript, is quoted as having once said, "[JavaScript] that executes in whole seconds is probably doing something wrong...". So what is an appropriate amount of time to execute a script?

**100 milliseconds**, why?

This number comes from research conducted by Robert Miller in 1968, while a usability expert Jakob Nielson has also claimed that if the interface responses to user input within 100 milliseconds, the user fells that he is "directly manipulating the objects in the user interface".

### 2. Yielding with Timers

Despite best efforts, there will be times when a JavaScript tasks cannot be completed in 100 milliseconds or less because of its complexity. In these cases, it is a good choice to stop JavaScript execution and give the UI a chance to update itself before continuing to execute the rest of code. This is why JavaScript timers came out?

#### 2.1 Timer Basics

Timers are created in JavaScript using either `setTimeout()` or `setInterval()`, which both accept the same arguments: a function to execute and the amount of time to wait before executing it. The difference between them is that `setTimeout()` creates a timer that executes just once, whereas the `setInterval()` function creates a timer that repeats periodically.

What you should be aware of them is that they start to count at the time they're called.

```js
var button = document.getElementById('my-button');
button.onclick = function () {
    task();

    setTimeout(function() {
        /** do something */
    }, 250);
};
```

Like the snippet above, the timer should wait for the end of the function `task()` before starting to count.

Taking another code as an example:

```js
var button = document.getElementById('my-button');
button.onclick = function () {
    task();

    setTimeout(function() {
        /** do something */
        console.log('what');
    }, 50);

    anotherTask();
};
```

What if the function `anotherTask()` has taken more than 50 milliseconds to complete? Actually, the string 'what' should be printed out after the function `anotherTask()` completed. Why? That's because the function passed to the timer belongs to macrotasks, which should be executed in a next event loop. It means that it should wait for the function `anotherTask()` in the current event loop.

In either case, creating a timer creates a pause in the UI thread as it switches from one task to the next. Consequently, timer code resets all of the relevant browser limits, including the long-running script timer. Further, the call stack is reset to zero inside of the timer code. These characteristics make timers the ideal cross-browser solution for long-running JavaScript code.

> The `setInterval()` function is almost the same as `setTimeout()`, except that the former repeatedly adds JavaScript tasks into the UI queue. The main difference is that it will not add a JavaScript task into the UI queue if a task created by the same `setInterval()` call is already present in the UI queue.

#### 2.2 Timer Precision

JavaScript timers delays are often imprecise, which means that they are unreliable for measuring actual time passed.

Setting timer delays of less than 15 can cause browser locking in IE, so the smallest recommended delay is 25 milliseconds (which will end up as either 15 or 30) to ensure a delay of at least 15 milliseconds. This minimum timer delay also helps to avoid timer resolution issues in other browsers and on other systems.

#### 2.3 Array Processing with Timers

One common cause of long-running scripts is loops that takes too long to execute. If you have already tried all loop optimization techniques, then timers are alternatives that can be used to optimize. The basic approach is to split up the loop's work into a series of timers.

Typical loops follow a simple pattern, such as:

```js
for (var i = 0, len = items.length; i < len; i++) {
    process(item[i]);
}
```

There are two factors determining whether a loop can be done asynchronously using timers:

- Does the processing have to be done synchronously?
- Does the data have to be processed sequentially?

If the answer to both of these questions is "no", then it's a good candidate for using timers to slit up the work:

```js
var todo = items.concat();

setTimeout(function () {
    /** get next item in the array and process it */
    process(todo.shift());

    /** if there is more items to process, create another timer */
    if (todo.length > 0) {
        /** `arguments.callee` points to the function which the code is executing */
        setTimeout(arguments.callee, 25);
    } else {
        callback(items);
    }
}, 25);
```

> Generally speaking, it's best to use at least 25 milliseconds because smaller delays leave too little time for most UI updates.

Of course we can encapsulate this functionality:

```js
function processArray(items, process, callback) {
    /** create a clone */
    var todo = items.concat();

    setTimeout(function () {
        process(todo.shift());

        if (todo.length > 0) {
            setTimeout(arguments.callee, 25);
        } else {
            callback(items);
        }
    }, 25);
}
```

> One side effect of using timers to process arrays is that the total time to process the array increases. Nevertheless, it's a necessary trade-off to avoid a poor user experience by locking up the browser.

#### 2.4 Splitting Up Tasks

If a single function takes too long to execute, check to see whether it can be broken down into a series of smaller functions that complete in smaller amounts of time. This is often as simple as considering a single line of code as an atomic task, even though multiple lines of code typically can be grouped together into a single task.

Some functions are already easily broken down based on the other functions they call. For example:

```js
function saveDocument(id) {
    /** save the document */
    openDocument(id);
    writeText(id);
    closeDocument(id);

    /** update the UI to indicate success */
    updateUI(id);
}
```

If this function is taking too long, it can easily be split up into a series of smaller steps:

```js
function saveDocument(id) {
    var tasks = [openDocument, writeText, closeDocument, updateUI];

    setTimeout(function () {
        /** execute the next task */
        var task = tasks.shift();
        task(id);

        /** determine if there is more */
        if (tasks.length > 0) {
            setTimeout(arguments.callee, 25);
        }
    }, 25);
}
```

How about encapsulating it:

```js
function mutiStep(steps, args, callback) {
    var tasks = steps.concat();

    setTimeout(function () {
        /** execute the next task */
        var task = tasks.shift();
        task.apply(null, args || []);

        /** determine if there is more */
        if (tasks.length > 0) {
            setTimeout(arguments.callee, 25);
        } else {
            callback();
        }
    }, 25);
}
```

Therefore, we can use this function to complete the functionality above:

```js
function saveDocument(id) {
    var tasks = [openDocument, writeText, closeDocument, updateUI];

    /** remember to use an array to wrapper id */
    mutlStep(tasks, [id], function () {
        console.log('save done');
    });
}
```

#### 2.5 Timed Code

Sometimes executing one task at a time is inefficient. For example, a single task takes only 1 milliseconds, but there is a delay of 25 milliseconds between tasks. If there're 1000 tasks to be executed, it means that you will have to use 1000 x (25 + 1) = 26,000 milliseconds to complete the entire process. What if we process tasks in batches of 50, then it will only takes (1000 / 50) x (25 + 50) = 1,500 milliseconds to complete them. Apparently, we can use less time to complete the work without impacting user experience at the same time.

If keeping 100 milliseconds in mind as the absolute maximum amount of time for executing code, it's recommended o cut that number in half and never let any code execute for longer than 50 milliseconds continuously.

Therefore, based on this recommendation, we can use Date object to optimize our splitting:

```js
function timeProcessArray(items, process, callback) {
    /** create a clone */
    var todo = items.concat();

    setTimeout(function () {
        var start = +new Date();

        do {
            process(todo.shift());
        } while(todo.length > 0 && (+new Date() - start < 50));

        if (todo.length > 0) {
            setTimeout(arguments.callee, 25);
        } else {
            callback(items);
        }
    }, 25);
}
```

#### 2.6 Timers and Performance

Even though timers can make a huge difference in the performance of JavaScript code, abusing it can also have a negative effect reversely. Especially when multiple repeating timers are being created at the same time, all of these timers compete for time to execute. Neil Thomas of Google Mobile found that low-frequency repeating timers, occurring at intervals of one second or greater, had little effect to overall web application responsiveness.

Therefore, it's recommended to create a single repeating timer that performs multiple operations with each execution.

### 3. Web Workers

Since JavaScript was introduced, there has been no way to execute code outside of the browser UI thread. The web workers API had changed this when HTML5 arose.

Each new worker spawns its own thread to execute JavaScript code, which means that not only will code execute in a worker without affecting the UI thread, but it also won't affect code executing in other workers.

#### 3.1 Worker Environment

Part of the reason that JavaScript and UI updates share the same process is because one can affect the other quite frequently, and so executing these tasks out of order results in a bad user experience. Web workers could result in user interface errors by making changes to the DOM from an outside thread, but each worker has its own global environment that has only a subset of JavaScript features available.

The environment of a worker is made up of:

- A `navigator` object, which contains four properties: `appName`, `appVersion`, `userAgent`, and `platform`.
- A `location` object, which is same as `window`, except all properties are read-only.
- A `self` object, which points to the global worker object.
- An `importScripts()` method that is used to load external JavaScript for use in the worker.
- All ECMAScript objects, such as `Object`, `Array`, `Date`, etc..
- The `XMLHttpRequest` constructor.
- The `setTimeout()` and `setInterval()` timers.
- A `close()` method that stops the worker immediately.

To create a worker, you have to create an entirely separate JavaScript file, and use the following code to create your worker by providing a specific path of your JavaScript file:

```js
var worker = new Worker('./code.js');
```

#### 3.2 Worker Communication

Communication between different workers can be implemented by using `postMessage()` to post and a event handler `onmessage` to receive.

```js
var worker = new Worker('./code.js');

worker.onmessage = function (event) {
    console.log('Message: ' + event.data);
};

worker.postMessage('Aleen');
```

In the JavaScript file `code.js`:

```js
self.onmessage = function (event) {
    self.postMessage('Hello, ' + event.data);
};
```

With using `postMessage()`, you can only pass primitive values (like `null`, `undefined`, `Number`, `Boolean`, and `String`) as well as instances of `Object` and `Array`.

> Safari 4's implementation of workers only allows you to pass strings using `postMessage()`. The specification was updated after that point to allow serializable data to be passed through, which is how Firefox 3.5 implements workers.

#### 3.3 Loading External Files

If you want to load one or more external file into a worker, `importScripts()` is your choice to do so:

```js
/** ./code.js */
importScripts('file1.js', 'file2.js');
```

Since you imported, the context of these two files have been available in the context of this worker.

Web workers are suitable for any long-running scripts that work on pure data and that have no ties to the browser UI. For example, parsing a large JSON string will be a long-running task, which is difficult to break into small chunks with timers, so a worker is the ideal solution.

```js
var worker = new Worker('jsonparse.js');

/** when the data is available, then handle it */
worker.onmessage = function (event) {
    /** data */
    var jsonData = event.data;

    /** operation with the data */
    evaluteData(jsonData);
};

/** pass in the large JSON string to parse */
worker.postMessage(jsonText);
```

Then the parse should act like the following snippet:

```js
/** handle passed text */
self.onmessage = function (event) {
    /** extract the text */
    var jsonText = event.data;

    /** parse it */
    var jsonData = JSON.parse(jsonText);

    /** send back */
    self.postMessage(jsonData);
};
```

Note that it's not necessary to use timers to split up tasks any more, because it has been executed in a separated thread without affecting the UI thread.

>  Keep in mind that this presently works only in Firefox 3.5 and later, as Safari 4 and Chrome 3's implementations allow strings to be passed only between page and worker

Except parsing a large JSON text, workers are also beneficial for:

- Encoding/decoding a large string
- Complex mathematical calculations (like image or video processing)
- Sorting a large array

Any time a process takes longer than 100 milliseconds to complete, you should consider whether a worker solution is more appropriate than a timer-based one. This, of course, is based on browser capabilities.

### 4. Summary

JavaScript code executing and the UI updates have shared the same process, which means that they are restricted by each other. In order to keep a good user experience, we should consider approaches to execute code in a proper way:

- No JavaScript task should take longer than 100 milliseconds to execute.
- Timers is a alternative to split up long-running scripts into a series of smaller tasks to run.
- Web workers are a feature in newer browsers that allows us to execute JavaScript code outside the UI thread.

The more complex the web application, the more critical it is to manage the UI thread in a proactive (積極主動的) manner. No JavaScript code is so important that it should adversely affect the user’s experience.
