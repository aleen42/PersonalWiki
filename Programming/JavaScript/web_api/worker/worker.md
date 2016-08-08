## Worker [Back](./../web_api.md)

**Web Worker (Dedicated Web Worker)** provides a way for running script in the background.

The worker context is represented by a [DedicatedWorkerGlobalScope](https://developer.mozilla.org/en-US/docs/Web/API/DedicatedWorkerGlobalScope) object in the case of dedicated workers (standard workers that are utilized by a single script; shared workers use [SharedWorkerGlobalScope](https://developer.mozilla.org/en-US/docs/Web/API/SharedWorkerGlobalScope)). A dedicated worker is only accessible from the script that first spawned it, whereas shared workers can be accessed from multiple scripts.

### 1. Threads Security

**Worker** API will really create a os thread, which will cause some security problems within concurrency, while **Web Worker** will strictly control this problem, because you have no chances to access DOM or any non-threadsafe component.

