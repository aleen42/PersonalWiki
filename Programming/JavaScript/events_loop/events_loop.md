## Events Loop [Back](./../JavaScript.md)

The multi-threading technology has given us a way to handle works that may take much more time to complete. However, Node.js and V8 has not provided us a way to create a new thread in our programming. Even so, the APIs of C++ have given a way to do this and what it means is that when you are doing some non-blocking tasks, Node.js has potentially created a thread to handle these tasks. Once the thread complete the task, the thread will automatically execute your callback functions which are given before.


