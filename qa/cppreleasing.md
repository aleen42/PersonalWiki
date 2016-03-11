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

- after using **std::vector**, `clear()` is just used to clear data, but the space of memory will still a problem for you. Therefore, remember to use `swap()` to release memory for each used vectors.

```cpp
std::vector<T> v;

v.clear();
/* clear func just clears the data but not the space it takes */

std::vector<T>(v).swap(v);
/* by calling this func, space will be really released */

```


<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
