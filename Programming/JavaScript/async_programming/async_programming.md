## Asynchronous Programming [Back](./../JavaScript.md)

### 1. Introduction

In the computer science, I have always grasped that "Asynchronous" is a word for describing working states between threads. If the job of one thread does not affect another one, it indicates to be asynchronous. In this chapter, it's a skill for programming.

As JavaScript is almost run in a thread, and its executing blocks the UI thread at the same time, resulting in a really "disastrous" user experience, asynchronous programming allows developers to write code in a asynchronous way to improve performance of JavaScript code. With making great use of CPU resources to prevent from wasting calculation units, the effect is always impressive.

Before using such a skill to handle multitasking, be sure that tasks are non-preemptive (非優先級的), also means not related to each other. Similar to 

> It's asynchronous, but remember that it does not mean to use multiple threads.
