## Base64 encode or decode in JavaScript [Back](./qa.md)

- Browse Context:

    ```js
    btoa('test'); // => "dGVzdA=="
    atob('dGVzdA=='); // => "test"  
    ```

- NodeJS Context:

    ```js
    Buffer.from('test').toString('base64'); // => "dGVzdA=="
    `${Buffer.from('dGVzdA==', 'base64')}`; // => "test"
    ```
