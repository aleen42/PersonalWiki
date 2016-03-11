## Some problems of releasing memory in C++ [Back](./qa.md)

1. remember to create deconstructor of each class.

```cpp
Class A {
private:
public:
    A() {}
    /* remember to create this as follow */
    ~A() {}
}
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
