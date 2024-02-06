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

/* clear func just clears the data but not the space it takes */
v.clear();

/* by calling this func, space will be really released */
std::vector<T>(v).swap(v);
```

- when using `new` to create instances, please remember to release memory by using `delete`

```cpp
A a = new A();

/* release */
delete a;
```

- some attention points about char*
    - normal situation:

    ```cpp
    /* allocate 30 bytes to house a string */
    char* str = new char [30];
    
    /* release */
    delete [] str;
    ```
    
    - remember to release when relocate a pointer to another one:
    
    ```cpp
    char* str = new char [30];
    
    str = new char [60];
    
    /* this will only release the next 60 bytes, but not the 30 bytes before */
    delete [] str;
    ```
    
    - notice about pointers assignments:
    
    ```cpp
    char* str1 = new char [30];
    char* str2 = new char [40];
    
    strcpy(str1, "memory leak");
    
    /* try not to do this, or you'll never free those 40 bytes of character */
    str2 = str1
    
    delete [] str2;
    /* a disater is comming, and access violation */
    delete [] str1;
    ```
    
    - block region will never collect memory after exiting the program:
    
    ```cpp
    void Leak(int x) {
        char* p = new cha [x];
        
        /* if you don't do show, oops, memory leak happens */
        delete [] p;
    }
    ```
    
    - `delete` by itself is just to delete a single object, and `delete []` can free the whole array:
    
    ```cpp
    char* one = new char;
    /* something wrong */
    delete [] one;
    
    char* many = new char [40];
    /* something wrong */
    delete many;
    ```

