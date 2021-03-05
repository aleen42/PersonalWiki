## How to hide input[file] in IE8 [Back](./qa.md)

```css
input[type="file"] {
    opacity: 0;
    
    /** IE8 supported */
    filter: alpha(opacity=0);
}
```