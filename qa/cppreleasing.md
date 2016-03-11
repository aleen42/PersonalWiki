## Some problems of releasing memory in C++ [Back](./qa.md)

- remember to create deconstructor of each class.

```cpp
Class A {
private:
public:
    A() {}
    A(int b) {}
    
    /* remember to create this as follow */
    ~A() {}
}
```

- after using **std::vector**, `clear()` is just used to clear data, but the space of memory will still a problem for you.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
