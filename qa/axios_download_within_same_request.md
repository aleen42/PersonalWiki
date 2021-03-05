## How to handle error message and binary response with Axios within a same request [Back](./qa.md)

When using [Axios](https://github.com/axios/axios), we may meet the requirement that we need to handle error response when downloading file within the same request. But how to, as Axios will convert responses according to your specific response type? The answer is specifying response type as  `ArrayBuffer` rather than `Blob`, and try to parse error responses when the response header `Content-Type` is `application/json`, but not `application/octet-stream`.

Why? When setting with `Blob`, we cannot synchronously read the content before return responses.

```js
const service = axios.create({
    baseURL: `${location.protocol}//${location.hostname}${window.location.port ? ':' + window.location.port : ''}/xxx/api`,
});

service.interceptors.response.use(
    response => {
        if (!/json$/gi.test(response.headers['content-type'])) {
            /** not json, like binary string */
            return response.data;
        }

        if (response.request.responseType === 'arraybuffer'
            && response.data.toString() === '[object ArrayBuffer]'
        ) {
            /** error response */
            const res = JSON.parse(Buffer.from(response.data).toString('utf8'));
        }
        
        /** handle res according to the JSON object */
        /** ... */
    },
    error => {/** handle error response status */}
);
```

When it comes to how to download a file with array buffer, we can learn from the library [`js-file-download`](https://github.com/kennethjiang/js-file-download).

```js
const downloader = require('js-file-download');
server.post(url, params, {
    responseType: 'arraybuffer',
}).then(data => {
    downloader(data, 'xxx.csv');    
});
```
