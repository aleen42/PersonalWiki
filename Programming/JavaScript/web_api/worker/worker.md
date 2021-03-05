## Worker [Back](./../web_api.md)

A worker is an object created using a constructor (e.g. `Worker()`) that runs a named JavaScript file — this file contains the code that will run in the worker thread; workers run in another global context that is different from the current `window`. Thus, using the `window` shortcut to get the current global scope (instead of `self`) within a Worker will return an error.

The worker context is represented by a [DedicatedWorkerGlobalScope](https://developer.mozilla.org/en-US/docs/Web/API/DedicatedWorkerGlobalScope) object in the case of dedicated workers (standard workers that are utilized by a single script; shared workers use [SharedWorkerGlobalScope](https://developer.mozilla.org/en-US/docs/Web/API/SharedWorkerGlobalScope)). A dedicated worker is only accessible from the script that first spawned it, whereas shared workers can be accessed from multiple scripts.

Data is sent between workers and the main thread via a system of messages — both sides send their messages using the `postMessage()` method, and respond to messages via the `onmessage` event handler (the message is contained within the [Message](https://developer.mozilla.org/en-US/docs/Web/Events/Message) event's data attribute.)

### Dedicated workers

#### 1. Worker feature detection

For slightly more controlled error handling and backwards compatibility, it is a good idea to wrap your worker accessing code in the following:

```js
/** detect worker feature */
if (window.Worker) {
    /**
     * Worker APIs is availabel
     * ...
     */
}
```

#### 2. Spawning a dedicated worker

```js
/** create a worker for running worker.js */
var myWorker = new Worker('worker.js');
```

#### 3. Sending messages to and from a dedicated worker

Use `postMessage` to send messages to worker

```js
first.onchange = function () {
    myWorker.postMessage([first.value, second.value]);
    console.log('Message posted to worker');
};

second.onchange = function () {
    myWorker.postMessage([first.value, second.value]);
    console.log('Message posted to worker');
};
```

In the worker, we should define a `onmessage` function to capture messages from the main thread, then handle it before sending back:

```js
onmessage = function (e) {
    console.log('Message received from main script');
    var workerResult = 'Result: ' + (e.data[0] * e.data[1]);
    console.log('Posting message back to main script');
    postMessage(workerResult);
};
```

After that, the main thread should also use onmessage to receive handled data:

```js
myWorker.onmessage = function (e) {
    result.textContext = e.data;
    console.log('Message received from worker');
};
```

#### 4. Terminating a worker

Stop the worker in the main thread:

```js
myWorker.terminate();
```

Stop the worker in the worker thread:

```js
close();
```

#### 5. Spawning subworkers

Workers may spawn more workers if they wish. So-called sub-workers must be hosted within the same origin as the parent page.

#### 6. Importing scripts and libraries

Use `importScript()` to import scripts in the same domain into their scope:

```js
importScript();                     /** import nothing          */
importScript('foo.js');             /** import just 'foo.js'    */
importScript('foo.js', 'bar.js');   /** import two scripts      */
```

*Note: Scripts may be downloaded in any order, but will be executed in the order in which you pass the filenames into `importScripts()`. This is done synchronously; `importScripts()` does not return until all the scripts have been loaded and executed.*

### Shared workers

A shared worker is accessible by multiple scripts — even if they are being accessed by different windows, iframes or even workers.

#### 1. Spawning a shared worker

```js
/** create a worker for running worker.js */
var myWorker = new SharedWorker('worker.js');
```

One big difference is that with a shared worker you have to communicate via a `port` object.

The port connection needs to be started either implicitly by use of the `onmessage` event handler or explicitly with the `start()` method before any messages can be posted.

```js
/** called in the main thread */
myWorker.port.start();
```

#### 2. Sending messages to and from a shared worker

```js
squareNumber.onchanged = function () {
    myWorker.port.postMessage([squareNumber.value, squareNumber.value]);
    console.log('Message posted to worker');
};
```

Then, on the worker thread, you have to create a event listner named `connect` to listen to the port:

```js
self.addEventListener('connect', function (e) {
    var port = e.ports[0];
    
    port.onmessage = function (e) {
        var workerResult = 'Result: ' + (e.data[0] * e.data[1]);
        port.postMessage(wokerResult);
    };
    
    /** not necessary to call start() explictly because onmessage event handler is being used */
    /** port.start(); */
});
```

Finnally, back in the main thread, we deal with message through `onmessage`:

```js
myWorker.port.onmessage = function (e) {
    result2.textContent = e.data;
    console.log('Message received from worker');
};
```

### About thread safety

**Worker** API will really create a OS thread, which will cause some security problems within concurrency, while **Web Worker** will strictly control this problem, because you have no chances to access DOM or any non-threadsafe component.

### More details about transferring data

Data passed between the main page and workers is **copied**, not shared. Objects are serialized as they're handed to the worker, and subsequently, de-serialized on the other end. The page and worker **do not share the same instance**, so the end result is that **a duplicate** is created on each end. 

```js
function transferData(message) {
    /** return eval('(' + JSON.stringify(message) + ')'); */
    return JSON.parse(JSON.stringify(message));
}
```
