## conversion between **string**, **char***, **const char*** [Back](./../c.md)

#### string

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

const char* c_s = s.c_str();
```

#### const char*

- to char*

```cpp
char* c;
const char* c_s = "abc";

const int len = strlen(c_s) + 1;
strcpy(c, c_s);
```

- to string

```cpp
const char* c_s = "abc";
string s(c_s);
```

#### char*

- to const char*

```cpp
const char* c_s = "abc";
char* c = c_s
```

- to string

```cpp
char* c = "abc";
string s(c);
```

