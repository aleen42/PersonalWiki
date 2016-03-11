## Why does the shell script always break down when running for statement [Back](./qa.md)

- When running `for` statement in Ubuntu, you'll always find the command line will print out something as follow:

```
Syntax error: Bad for loop variable
```

- The reason is that Ubuntu has used **dash shell** instead of **bash shell** since Ubuntu 6.10, because it's lighter.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
