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
    /** Worker APIs is availabel
}
```

### Threads Security

**Worker** API will really create a os thread, which will cause some security problems within concurrency, while **Web Worker** will strictly control this problem, because you have no chances to access DOM or any non-threadsafe component.

