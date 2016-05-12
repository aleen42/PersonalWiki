## Differences between spawn and exec of child_process [Back](./../node.md)

The Node.js Child Processes module (**child_process**) has two functions **spawn** and **exec**, using which we can start a child process to execute other programs on the system. Those new to **child_process** may wonder why there are two functions to do the same thing, and which one they should use. I'll explain the differences between **spawn** and **exec** to help you decide when to use what.

The most significant difference between **child_process.spawn** and **child_process.exec** is in what they return - spawn returns a stream and exec returns a buffer.

**child_process.spawn** returns an object with **stdout** and **stderr** streams. You can tap on the **stdout** stream to read data that the child process sends back to Node. **stdout** being a stream has the "data", "end", and other events that streams have. spawn is best used to when you want the child process to return a large amount of data to Node - image processing, reading binary data etc.