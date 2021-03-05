## Event Loops [Back](./../JavaScript.md)

### Introduction

The multi-threading technology has given us a way to handle works that may take much more time to complete. However, Node.js and V8 has not provided us a way to create a new thread in our programming. Even so, the APIs of C++ have given a way to do this and what it means is that when you are doing some non-blocking tasks, Node.js has potentially created a thread to handle these tasks. Once the thread complete the task, the thread will automatically execute your callback functions which are given before.

In brief, when you calling `setTimeout`, `http.get`, or `fs.readFile`, Node.js will deliver these tasks to another potential thread to do so, so that it can continue to execute other codes. Generally, these functions will also accept a callback function to call after completing the tasks you set before. When tasks are set up, these tasks will be stored in a queue, named **task queues**, waiting for being executed. When the task has been completed, Node.js will use a loop to execute related callback functions, and the loop is called **event loops**.

When it comes to task queues, there're mainly two types of queues: **microtasks** and **macrotasks**.

**microtasks**:

- process.nextTick
- Promise
- Object.observe

**macrotasks**:

- setInterval
- setTimeout
- setImmediate
- I/O

### Advanced Analysis

According to [whatwg](https://html.spec.whatwg.org/multipage/webappapis.html#task-queue), an event loop will have one or more task queues, while a task queue is an ordered list of **tasks**, which are algorithms that are responsible for such works as:

- Events
- Parsing
- Callbacks
- Using a resource
- Relating to DOM manipulation

Each time an event loop takes a task from the macrotasks, and execute it until all tasks has been done. After that, all the available tasks from the microtasks will be executed in the end of this event loop. If there're still some new tasks registered during executing, these new tasks will be handled in a next event loop.