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

#### 3.1 Main Moudles

There are 3 basic back-end modules of Coremail System:

- **mdsvr (Meta Data Servers)**
    - mainly used for indexing users (udid) to access which User Data Servers
    - only a database, which will be cached in memories and files (access first)
    - a user index information will be only stored in two devices (a loop principle, **n** and **(n + 1) % n**)
    - COS overlay
- **udsvr (User Data Servers)**
    - mainly used for storing user data and indexing emails (Mbox)
    - data are stored in databases and file systems
    - Mbox will store some information with files:
        - The basic info of an email
        - Indexing position (msid/mid)
        - Size
        - Time (Create, Sent, Modified)
        - Extend Info
        - Title
        - Sender
        - ...
- **mssvr (Message Servers)**
    - mainly used to store emails
    - a file will have multiple emails from a single user


As for the front-end, there are also some modules to server:

- **mtasvr**
    - mainly used to handle delivering operations and make **deliveragent** to do the real delivering.
    - 
- **pop3svr**
- **...**

As for the server side, there is also a server:

- **adminsvr**
