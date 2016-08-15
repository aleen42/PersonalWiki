## Dangersouly Set innerHTML [Back](./../react.md)

Improper use of the `innerHTML` can open you up to a [cross-site scripting (XSS)](https://en.wikipedia.org/wiki/Cross-site_scripting) attack. 

React's design philosophy is that it should be “easy” to make things safe, and developers should explicitly state their intent when performing “unsafe” operations. The prop name dangerouslySetInnerHTML is intentionally chosen to be frightening, and the prop value (an object instead of a string) can be used to indicate sanitized data.