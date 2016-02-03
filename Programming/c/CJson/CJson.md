## cJSON [Back](./../c.md)

- cJSON is a c/c++ lib for **creating** json or **parsing** json.

#### Include lib

```c
#include "cJSON.h"
```

#### 1. Create Json Object/Array

```c
cJSON* jobj = cJSON_CreateObject();
cJSON* jarr = cJSON_CreateArray();
```

#### 2. Add items

```c
/**
 * Object
 */
 
/** add item to an obj */
cJSON_AddItemToObject(jobj, "arrName", jarr);

/** add string to an obj */
cJSON_AddStringToObject(jobj, "strName", "string");

/** add number to an obj */
cJSON_AddNumberToObject(jobj, "numName", 42);

/**
 * Array
 */
 
/** add obj to an array */
cJSON_AddItemToArray(jarr, jobj);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
