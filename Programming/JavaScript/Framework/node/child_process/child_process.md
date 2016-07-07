## Differences between spawn and exec of child_process [Back](./../node.md)

The Node.js Child Processes module (**child_process**) has two functions **spawn** and **exec**, using which we can start a child process to execute other programs on the system. Those new to **child_process** may wonder why there are two functions to do the same thing, and which one they should use. I'll explain the differences between **spawn** and **exec** to help you decide when to use what.

The most significant difference between **child_process.spawn** and **child_process.exec** is in what they return - spawn returns a stream and exec returns a buffer.

**child_process.spawn** returns an object with **stdout** and **stderr** streams. You can tap on the **stdout** stream to read data that the child process sends back to Node. **stdout** being a stream has the "data", "end", and other events that streams have. **spawn** is best used to when you want the child process to return a large amount of data to Node - image processing, reading binary data etc.

**child_process.spawn** is "asynchronously asynchronous", meaning it starts sending back data from the child process in a stream as soon as the child process starts executing.

You can see an example [here](http://www.hacksparrow.com/using-node-js-to-download-files.html#nodejs-curl) where I used **spawn** to read the results of a curl request to Node.

**child_process.exec** returns the whole buffer output from the child process. By default the buffer size is set at 200k. If the child process returns anything more than that, you program will crash with the error message "Error: maxBuffer exceeded". You can fix that problem by setting a bigger buffer size in the **exec** options. But you should not do it because **exec** is not meant for processes that return HUGE buffers to Node. You should use **spawn** for that. So what do you use **exec** for? Use it to run programs that return result statuses, instead of data.

**child_process.exec** is "synchronously asynchronous", meaning although the **exec** is asynchronous, it waits for the child process to end and tries to return all the buffered data at once. If the buffer size of **exec** is not set big enough, it fails with a "maxBuffer exceeded" error.

See an example [here](http://www.hacksparrow.com/using-node-js-to-download-files.html#nodejs-wget) where I used **exec** to execute wget to download files and update Node with the status the execution.

So there it is - the differences between **span** and **exec** of Node's **child_process**. Use **spawn** when you want the child process to return huge binary data to Node, use **exec** when you want the child process to return simple status messages.