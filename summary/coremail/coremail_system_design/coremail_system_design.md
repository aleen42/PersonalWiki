## The design of Coremail system	[Back](./../coremail.md)

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
- CPU
- Network
- Memory
