## Worker [Back](./../web_api.md)

**Web Worker (Dedicated Web Worker)** provides a way for running script in the background.

### 1. Threads Security

**Worker** API will really create a os thread, which will cause some security problems within concurrency, while **Web Worker** will strictly control this problem.