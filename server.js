/***********************************************************************
 *                                                                   _
 *       _____  _                           ____  _                 |_|
 *      |  _  |/ \   ____  ____ __ ___     / ___\/ \   __   _  ____  _
 *      | |_| || |  / __ \/ __ \\ '_  \ _ / /    | |___\ \ | |/ __ \| |
 *      |  _  || |__. ___/. ___/| | | ||_|\ \___ |  _  | |_| |. ___/| |
 *      |_/ \_|\___/\____|\____||_| |_|    \____/|_| |_|_____|\____||_|
 *
 *      ================================================================
 *                 More than a coder, More than a designer
 *      ================================================================
 *
 *
 *      - Document: server.js
 *      - Author: aleen42
 *      - Description: a script for creating a local server.
 *      - Create Time: Jul 4th, 2019
 *      - Update Time: Jul 4th, 2019
 *
 *
 **********************************************************************/

const http = require('http');
const fs = require('fs');
const port = process.argv[2] || 8080;

http.createServer(function (request, response) {
    const url = request.url;
    let surl;
    if (url === '/') {
        surl = './gh-pages/index.html';
        response.writeHead(200, {'Content-Type': 'text/html'});

    } else {
        surl = `./gh-pages/${url.replace(/\?.*?$/, '')}`;
        const type = surl.substr(surl.lastIndexOf('.') + 1, surl.length);
        response.writeHead(200, {'Content-type': `text/${type}`});
    }

    fs.readFile(surl, function (err, data) {
        if (err) {
            console.error(err);
            return;
        }
        response.end(data);
    });
}).listen(parseInt(port, 10));

console.log('Listening at\n  => http://localhost:' + port + '/\nCTRL + C to shutdown');
