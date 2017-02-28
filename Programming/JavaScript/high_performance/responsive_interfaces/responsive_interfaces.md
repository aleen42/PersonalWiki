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
- Does the data have to be processed

