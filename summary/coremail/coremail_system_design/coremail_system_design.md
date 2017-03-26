## The design of Coremail system	[Back](./../coremail.md)

### 1. Introduction

When it comes to an email system, it should be based on a file system. Take an email user as an example: the structure of such a user can be described as a file system tree.

- Aleen42
    - .Draft (草稿箱)
    - .Outbox (已發送)
    - .Span (已接收)
    - .Trash (垃圾箱)

The features of such a tree are that:

- All data is stored in an node, to maintain easily
- Difficult to extend

With more and more users using an email system, there should be some system bottlenecks arising:

- Disk
    - Space has been occupied
    - I/O Block
- CPU
- Network
- Memory

### 2. Normal Improvment

So how to work around those problems?

#### 2.1 Vertical

- To enhance hardware devices directly
- Optimize algorithms
- Optimize code

#### 2.2 Horizontal

- Load balance
- Functions decomposition
- Hot copy

The main thought of improving such a system is to use multiple devices to store data, and dividing data of users and emails at the same time.

### 3. Coremail System

There are 3 basic backend modules of Coremail System:

- **mssvr**
- **udsvr**
- **mdsvr**
