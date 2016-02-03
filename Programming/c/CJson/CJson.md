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
cJSON_AddItemToObject(jobj, "arrName", jarr);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
