## Create a static server with node.js [Back](./../node.md)

### Definition

create a JavaScript file name `server.js`:

```js
var http = require('http');
var url = require('url');
var path = require('path');
var fs = require('fs');
var port = process.argv[2] || 9000;

http.createServer(function(request, response) {
    var uri = decodeURI(url.parse(request.url).pathname);
    var filename = path.join(process.cwd(), uri);

    fs.exists(filename, function(exists) {
        if (!exists) {
            response.writeHead(404, { 'Content-Type': 'text/plain' });
            response.write("404 Not Found\n");
            response.end();
            return;
        }

        if (fs.statSync(filename).isDirectory()) filename += '/index.html';

        fs.readFile(filename, "binary", function(err, file) {
            if (err) {
                response.writeHead(500, { 'Content-Type': 'text/plain' });
                response.write(err + "\n");
                response.end();
                return;
            }

            response.writeHead(200);
            response.write(file, "binary");
            response.end();
        });
    });
}).listen(parseInt(port, 10));

console.log('Listening at\n  => http://localhost:' + port + '/\nCTRL + C to shutdown');
```

### Usage

```bash
node ./server.js
node ./server.js 8080
```
