## Idempotence (幂等性) between HTTP Request Methods [Back](../JavaScript.md)

What is idempotence? As the HTTP/1.1 protocol mentioned:

> Methods can also have the property of "idempotence" in that (aside from error or expiration issues) the side-effects of N > 0 identical requests is the same as for a single request.

Take it short, the result of a single request or multiple requests to specific resources should be same, when the request have the property of "idempotence". Actually, this is just a semantic definition, which means that any HTTP methods designed by developers can also not obey this. But in most cases, it is helpful when generating a common sense on "idempotence" of different HTTP request methods.

### 1. GET

GET methods should have the property of "idempotence", as it is not expected to get different results with one request or multiple ones.

### 2. DELETE

DELETE methods can be designed as idempotent, where the callers do not need to care about thrown errors when the specific resource is not existed.

### 3. POST

POST methods should not be designed as idempotent as we always hope that callers can create different resources via such a API.

### 4. PUT

If developers do care about the problem of creating multiple same resources, servers should also expose a PUT method, which has the property of "idempotence". It means that calling the same request with PUT methods, resources will only be modified with last request body, and developers do not need to worry about redundant resources.
