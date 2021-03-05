## ReactiveX [Back](./../Framework.md)

<p align="center">
    <img src="./logo.png" />
</p>
<p align="center">
    ReactiveX
</p>

![reactivex](https://aleen42.github.io/badges/src/reactivex.svg)

[**ReactiveX**](http://reactivex.io/) is a library for composing asynchronous and event-based programs by using observable sequences.

It mainly extends [the observer pattern](http://en.wikipedia.org/wiki/Observer_pattern) to support composing sequences together without concerning about low-level threading, synchronization, thread-safety, concurrent data structures, and non-blocking I/O.

The author of Rx has claimed that Rx can not be called as "functional reactive programming", as it only operates on *isolated* values that are emitted over time, but not on values that change *continuously* over time.

When it comes to the topic why to use Rx, the most important reason in my opinion is that it can free us from tangled webs of callbacks, so that code can be more readable. With reading the article, "[2 minute introduction to Rx](2 minute introduction to Rx)", written by André Staltz, we can easily get that Rx is actually a functional tool for operating events in a event stream through an object named **Observables**.

### 1. As a data flow management tool

```js
/** initialized with initial value of 42 */
var subject = Rx.BehaviorSubject(42);

var subscription = subject.subscribe({
    /** handle data */
    onNext: x => console.log(`currentValue: ${subject.getValue()}`),
    onError: err => console.log(`Error: ${err}`),
    onCompleted: console.log.bind(null, 'Completed'),
});

subject.onNext(56); /** => currentValue: 56 */
subject.onCompleted();
subject.dispose();

try {
    subject.onNext(88);
} catch (e) {
    console.log(e.message); /** => Object has been disposed */
}
```

### 2. As an event listener and counter

```js
const counterDuration = 60; /** => 60 seconds */
const counterObservable = Rx.Observable
    .fromEvent('.btn', 'click')
    .interval(1000) /** => 1000 milliseconds */
    .take(counterDuration)
    .startWith(-1)
    .map(curTime => (counterDuration - curTime));

const counterObserver = counterObservable.subscribe({
    onNext: timeLeft => console.log(`time left: ${timeLeft}s`),
    onCompleted: () => console.log('timeout'),
});
```
