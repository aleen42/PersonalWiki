## How to get current timestamp with JavaScript [Back](./qa.md)

### Accurate to Seconds

```js
console.log(Date.parse(new Date()));
```

### Accurate to Milliseconds

```js
console.log(new Date().getTime());
```
