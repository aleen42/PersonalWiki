## How to get current timestamp with JavaScript [Back](./qa.md)

### Accurate to Seconds

```js
console.log(Date.parse(new Date()));    /** => 1280977330000 */
```

### Accurate to Milliseconds

```js
console.log(new Date().getTime());      /** => 1280977330748 */

console.log((new Date()).valueOf());    /** => 1280977330748 */
```

### Convert timestamp into a date


