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

Once the button is clicked, it will create and add two new tasks to a queue, waiting for being executed.
