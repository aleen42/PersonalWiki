## Why does the shell script always break down when running for statement [Back](./qa.md)

- When running `for` statement in Ubuntu, you'll always find the command line will print out something as follow:

```
Syntax error: Bad for loop variable
```

- The reason is that Ubuntu has used **dash shell** instead of **bash shell** since Ubuntu 6.10, because it's lighter.
- Solution: just set back to **bash**:

```bash
sudo dpkg-reconfigure dash
# choose no
```
