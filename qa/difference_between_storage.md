## Differences between Cookie, localStorage, and sessionStorage [Back](./qa.md)

They are all used into storing data:

**Cookie** is always used to store data, which can identify a user, into local clients (like browsers) with encryption, and they will be cleared after a expired time. The most important thing you should know is that **Cookie** will be in HTTP requests head, which will be transferred between **Server** and **Client**. (**less than 4kb**)

**localStorage**: only store into local and won't be cleared after browsers close.

**sessionStorage**: only store into local and will be cleared after browsers close.