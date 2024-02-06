## A lock [Back](../Database.md)

A **lock** or **mutex**(互斥體) is a mechanism in software engineering to avoid accessing a DB resource in parallel when there are many threads of execution.

**Optimistic Lock** (乐观锁) means that the DB assumes any accessing won't modify the data, and it won't lock after your assessment, while **Pessimistic Lock** (悲观锁) means reversely. Many types of locks implemented in Java almost belong to a pessimistic one like a [**Spinlock**](https://en.wikipedia.org/wiki/Spinlock) (自旋锁), [**Mutual Exclusion**](https://en.wikipedia.org/wiki/Mutual_exclusion) (互斥锁), [**Reentrant mutex**](https://en.wikipedia.org/wiki/Reentrant_mutex) (可重入互斥锁), [**Readers-writer lock**](https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock) (读写锁).
