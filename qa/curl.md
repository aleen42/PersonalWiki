## How to use curl in Linux [Back](./qa.md)

With the silence option `-s`, you can hide the status of curl process.

If you want to request as **POST** method, you can use like this:

```bash
curl -d "param1=value1&param2=value2" "http://www.example.com"
```

If you want to see the header info, you can add `-l` like this:

```bash
curl -l -d "param1=value1&param2=value2" "http://www.example.com"
```

`-i` option can show all information, while `-v` will show the whole process of a request.


