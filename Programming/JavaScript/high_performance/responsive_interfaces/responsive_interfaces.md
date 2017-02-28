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
- Firefox has a default limit of 10 seconds; this limit is stored in the browser's configuration settings (accessible by typing about:config in the address box) as the dom.max_script_run_time key.
