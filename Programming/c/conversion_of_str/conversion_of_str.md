## conversion between **string**, **char***, **const char*** [Back](./../c.md)

#### String

- to char*

```cpp
string s = "abc";

/* new a char pointer and point to a char instance with the size */
char* c;
const int len = s.length();
c = new char[len + 1];

/* use strcpy to copy string to the char instance */
strcpy(c, s.c_str());
```

- to const char*

```cpp
string s= "abc";
```


<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
