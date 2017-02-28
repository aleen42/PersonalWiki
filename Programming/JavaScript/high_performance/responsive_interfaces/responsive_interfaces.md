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
