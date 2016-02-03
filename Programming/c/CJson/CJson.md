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

#### 3. Convert Json Object to a string

```c
char* jsonStr = cJSON_Print(jobj);
```

#### 4. Parse a string to Json Object

```c
cJSON* proot = cJSON_Parse(jsonStr);
```

#### 5. Get items

```c
/**
 * Object
 */
 
/** get object item */
cJSON* pobj = cJSON_GetObjectItem(proot, "arrName");

/**
 * Array
 */
 
/** get array item i */
cJSON* parr = cJSON_GetArrayItem(jarr, i);

/** get array size */
int arrSize = cJSON_GetArraySize(jarr);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
