## ReactiveX [Back](./../Framework.md)

<p align="center">
    <img src="./logo.png" />
</p>
<p align="center">
    ReactiveX
</p>

[**ReactiveX**](http://reactivex.io/) is a library for composing asynchronous and event-based programs by using observable sequences.

It mainly extends [the observer pattern](http://en.wikipedia.org/wiki/Observer_pattern) to support composing sequences together without concerning about low-level threading, synchronization, thread-safety, concurrent data structures, and non-blocking I/O.

The author of Rx has claimed that Rx can not be called as "functional reactive programming", as it only operates on *isolated* values that are emitted over time, but not on values that change *continuously* over time.

When it comes to the topic why to use Rx, the most important reason in my opinion is that it can free us from tangled webs of callbacks, so that code can be more readable.
