## Six Months in a Leaky Boat [Back](./../goog.md)
###Problem
```js
/* from Google Closure 
 * from memoize.js, Line 39
 * 雖然Google Closure採用了Cache來緩存執行結果以提高執行效率. 但是, 並沒有提供任何
 * 方法來限制緩存的大小, 這在JavaScript將導致Memory Leak
*/
goog.memoize = function(f, opt_serializer) {
  var functionHash = goog.getHashCode(f);
  var serializer = opt_serializer || goog.memoize.simpleSerializer;
  
  return function() {
    // Maps the serialized list of args to the corresponding return value.
    var cache = this[goog.memoize.CACHE_PROPERTY_];
    if (!cache) {
      cache = this[goog.memoize.CACHE_PROPERTY_] = {};
    }
    var key = serializer(functionHash, arguments);
    if (!(key in cache)) {
      cache[key] = f.apply(this, arguments);
    }
    return cache[key];
  };
};
```
